/* Includes ------------------------------------------------------------------*/
#include "mono.h"
#include <stdio.h>
#include <string.h>
#include "rgb_matrix.h"
#include "main.h"
#include "legacy_flash_ops.h"

//#include "SEGGER_RTT.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#define MatrixTask_STACK_SIZE 90
#define USBTask_STACK_SIZE 32
#define APPTask_STACK_SIZE 64
TaskHandle_t MatrixTask_Handler;
TaskHandle_t USBTask_Handler;
TaskHandle_t APPTask_Handler;
static void MatrixTask(void *pvParameters);


/* Private functions ---------------------------------------------------------*/


//static uint8_t keyboard_report_buf[USBD_HID_KEYBOARD_IN_REPORT_SIZE] = {0};
//static uint8_t last_report_keyboard_report_buf[USBD_HID_KEYBOARD_IN_REPORT_SIZE] = {0};

volatile QueueHandle_t xQueueAppEventMsg = NULL;
volatile SemaphoreHandle_t xMutexUsb = NULL;

void bspInit()
{

  SystemCoreClock = 48000000;
  
  USBD_Init();
  USBD_Connect();
}

void delay(volatile uint32_t n)
{
  while (n--);
}

int main(void)
{
  
  bspInit();
  
//  SEGGER_RTT_Init();
  
  xQueueAppEventMsg = xQueueCreate(10, 8);
  xMutexUsb = xSemaphoreCreateMutex();
  xTaskCreate(MatrixTask, "Matrix", MatrixTask_STACK_SIZE, NULL, 1, &MatrixTask_Handler);
  xTaskCreate(APPTask, "APP", APPTask_STACK_SIZE, NULL, 3, &APPTask_Handler);
//  xTaskCreate(USBTask, "USB", USBTask_STACK_SIZE, NULL, 1, &USBTask_Handler);
  /* Start the scheduler. */
  vTaskStartScheduler();

  /* Infinite loop */
  while (1)
  {
  }
}

extern void dengxiao(void);
static void MatrixTask(void *pvParameters)
{
//  KeyLed_Init();
//  KeyLed_Start();
  matrix_init();
  while (1)
  {
    #ifdef LED_MATRIX 
      rgb_matrix_task();
    #endif 
    matrix_task();
    
//    FLASH_Program_HalfWord(5, 0x1234);
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
