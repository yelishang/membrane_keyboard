/* Includes ------------------------------------------------------------------*/
#include "mono.h"
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "task_app.h"
#include "task_usb.h"
#include "usbd_core.h"
#include "usbd_user_hid.h"

//#include "SEGGER_RTT.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#define MatrixTask_STACK_SIZE 90
#define APPTask_STACK_SIZE 64
#define USBTask_STACK_SIZE 32

TaskHandle_t MatrixTask_Handler;
TaskHandle_t APPTask_Handler;
TaskHandle_t USBTask_Handler;

static void MatrixTask(void *pvParameters);

/* Private functions ---------------------------------------------------------*/

volatile QueueHandle_t xQueueAppEventMsg = NULL;
volatile SemaphoreHandle_t xMutexUsb = NULL;

void bspInit()
{

  SystemCoreClock = 48000000;
  
  USBD_Init();
  USBD_Connect();
}

static bool usbd_resume_flag = false;
static uint8_t bsp_usbd_resume_signal_flag = 0;
void bsp_usbd_resume(void) {

    usbd_resume_flag = false;

    PWR->ANAKEY1 = 0x03;
    PWR->ANAKEY2 = 0x0C;

    ANCTL->HSI48ENR = 0x01;
    while ((ANCTL->HSI48SR & 0x01) == 0);
    for (uint32_t i = 0; i < 10000; i++);

    PWR->ANAKEY1 = 0x00;
    PWR->ANAKEY2 = 0x00;

    FLASH->ACR      = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
    RCC->SYSCLKPRE1 = 0x00;
    RCC->SYSCLKSRC  = RCC_SYSCLKSRC_HSI48;
    RCC->SYSCLKUEN  = RCC_SYSCLKUEN_ENA;

    SystemCoreClock = 48000000;
}

void bsp_usbd_suspend(void) {

    RCC->SYSCLKPRE1 = 0x00;
    RCC->SYSCLKSRC  = RCC_SYSCLKSRC_HSI2;
    RCC->SYSCLKUEN  = RCC_SYSCLKUEN_ENA;
    SystemCoreClock = 2000000;

    EXTI_InitTypeDef EXTI_InitStructure;

    PWR->ANAKEY1 = 0x03;
    PWR->ANAKEY2 = 0x0C;

    ANCTL->HSI48ENR = 0x00;
    while ((ANCTL->HSI48SR & 0x01) != 0);
    for (uint32_t i = 0; i < 10000; i++);

    ANCTL->USBPDCR = 0x0F;

    PWR->ANAKEY1 = 0x00;
    PWR->ANAKEY2 = 0x00;

    RCC->APBENR |= RCC_APBENR_EXTIEN;

    EXTI_InitStructure.EXTI_Line    = EXTI_Line20;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    bsp_usbd_resume_signal_flag = 0;

    EXTI_ClearITPendingBit(EXTI_Line20);
    NVIC_EnableIRQ(USBP_WKUP_IRQn);
}

void USBP_WKUP_IRQHandler(void) {
    EXTI_ClearITPendingBit(EXTI_Line20);

    if ((bsp_usbd_resume_signal_flag == 0) && (ANCTL->USBPDSR & ANCTL_USBPDSR_KSTAT)) {
        bsp_usbd_resume_signal_flag = 1;
    }
    if ((bsp_usbd_resume_signal_flag == 1) && (ANCTL->USBPDSR & ANCTL_USBPDSR_SE0)) {
        bsp_usbd_resume_signal_flag = 2;
    }
    if ((bsp_usbd_resume_signal_flag == 2) && (ANCTL->USBPDSR & ANCTL_USBPDSR_JSTAT)) {
        bsp_usbd_resume_signal_flag = 3;
        NVIC_DisableIRQ(USBP_WKUP_IRQn);

        usbd_resume_flag = true;
    }

    if ((bsp_usbd_resume_signal_flag == 0) && (ANCTL->USBPDSR & ANCTL_USBPDSR_SE0)) {
        NVIC_DisableIRQ(USBP_WKUP_IRQn);

        usbd_resume_flag = true;
    }
}

int main(void)
{
  bspInit();
//  SEGGER_RTT_Init();
  
  xQueueAppEventMsg = xQueueCreate(10, 8);
  xMutexUsb = xSemaphoreCreateMutex();
  xTaskCreate(MatrixTask, "Matrix", MatrixTask_STACK_SIZE, NULL, 1, &MatrixTask_Handler);
  xTaskCreate(APPTask, "APP", APPTask_STACK_SIZE, NULL, 3, &APPTask_Handler);
  xTaskCreate(USBTask, "USB", USBTask_STACK_SIZE, NULL, 4, &USBTask_Handler);
  /* Start the scheduler. */
  vTaskStartScheduler();

  /* Infinite loop */
  while (1)
  {
  }
}

static void MatrixTask(void *pvParameters)
{
  matrix_init();
  while (1)
  {
    matrix_task();
    if (usbd_resume_flag) {
      xSemaphoreTake(xMutexUsb, portMAX_DELAY);
      bsp_usbd_resume();
      xSemaphoreGive(xMutexUsb);
    }
  }
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
