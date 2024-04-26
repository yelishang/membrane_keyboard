#include "task_usb.h"
#include "usbd_core.h"
#include "usbd_user_hid.h"
#include "main.h"

static volatile uint32_t ulUsbInterruptFlags = 0;

void USB_IRQHandler(void)
{
  BaseType_t xHigherPriorityTaskWoken;

  ulUsbInterruptFlags = (USB->INTROUT << 16) | (USB->INTRIN << 8) | (USB->INTRUSB);
  NVIC_DisableIRQ(USB_IRQn);

  xHigherPriorityTaskWoken = pdFALSE;
  xTaskNotifyFromISR(USBTask_Handler,
                     0x01,
                     eSetBits,
                     &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

extern volatile uint32_t reset_req;

void USBTask(void *pvParameters)
{
  uint32_t  ulNotifiedValue;

  USBD_Init();
  USBD_Connect();

  while (1)
  {
    xTaskNotifyWait(0x00,
                    0xFFFFFFFF,
                    &ulNotifiedValue,
                    portMAX_DELAY);

    if (ulNotifiedValue & (0x01 ))
    {
      xSemaphoreTake(xMutexUsb, portMAX_DELAY);

      Handle_USBD_INT((uint8_t)(ulUsbInterruptFlags),
                      (uint8_t)(ulUsbInterruptFlags >> 8),
                      (uint8_t)(ulUsbInterruptFlags >> 16));
      NVIC_EnableIRQ(USB_IRQn);

      if (reset_req == 0x5AA5A5A5)
      {
        /* Delay 100ms to ensure the control transfer has been completed */
        vTaskDelay(100);
        USBD_DeInit();
        USBD_Disconnect();
        /* Delay 2000ms to ensure the device is disconnected */
        vTaskDelay(2000);
        RCC->GPREG0 = 0x4A379CEB;
        reset_req = 0;
        NVIC_SystemReset();
        while (1);
      }

      xSemaphoreGive(xMutexUsb);
    }
  }
}

