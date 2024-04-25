#include "task_usb.h"


#include "usbd_core.h"
#include "usbd_user_hid.h"
#include "main.h"

extern volatile uint32_t reset_flag;
static volatile uint32_t ulUsbInterruptFlags = 0;

void USB_IRQHandler(void) {
  uint8_t IntrUSB;
  uint8_t IntrIn;
  uint8_t IntrOut;

  IntrUSB = USB->INTRUSB;
  IntrIn  = USB->INTRIN;
  IntrOut = USB->INTROUT;

  Handle_USBD_INT(IntrUSB, IntrIn, IntrOut);
}


///*
//  由于在RTOS环境中，有其它任务会通过USB发送或接收数据，所以为防止中断函数中的代码
//  破坏任务中的USB操作，所有的USB中断事件的处理都放在一个单独的TaskUsb任务中处理。
//  当发生USB中断时，在USB中断函数中需要调用FreeRTOS API通知TaskUsb任务去处理发生的USB事件。

//  在本例程中，由于需要通过USB SOF中断矫正内部时钟，所以USB的中断优先级必须是最高的！
//  且不能被RTOS内核屏蔽，不然USB中断的响应就有可能会被延迟，从而影响内部时钟的矫正。
//  但是在FreeRTOS中，不受RTOS内核屏蔽的中断优先级函数中不能调用FreeRTOS API，
//  所以在本例程中，用一个受RTOS内核屏蔽的EXTI中断来通知TaskUsb任务，
//  在USB中断函数中矫正内部时钟，然后软件触发对应的EXTI中断以此达到通知TaskUsb任务处理USB事件的目的。

//  参考文档：
//  https://www.freertos.org/RTOS-Cortex-M3-M4.html
//  https://www.freertos.org/a00110.html#kernel_priority
//*/
void USBTask(void *pvParameters) {
//  uint32_t ulNotifiedValue;

//  USBD_Init();
//  USBD_Connect();

//  // 任务主循环
                        while (1) {
//    xTaskNotifyWait(0x00,
//                    0xFFFFFFFF,
//                    &ulNotifiedValue,
//                    portMAX_DELAY);

//    if (ulNotifiedValue & 0x01) {
//      xSemaphoreTake(xMutexUsb, portMAX_DELAY);

//      Handle_USBD_INT((uint8_t)(ulUsbInterruptFlags),
//                      (uint8_t)(ulUsbInterruptFlags >> 8),
//                      (uint8_t)(ulUsbInterruptFlags >> 16));
//      NVIC_EnableIRQ(USB_IRQn);


//      xSemaphoreGive(xMutexUsb);
//    }
  }
}
