/**
 * @file     system_mono.c
 * @brief    CMSIS Device System Source File for
 *           MONO Device Series
 * @version  V0.0.1
 * @date     15-June-2023
 */

#include "mono.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/




/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = HSI48_VALUE;       /*!< System Clock Frequency (Core Clock) */


/**
 * @brief  Setup the microcontroller system
 * @note   This function should be used only after reset.
 * @param  None
 * @return None
 */
void SystemInit (void)
{
  // Unlocks write to ANCTL registers
  PWR->ANAKEY1 = 0x03;
  PWR->ANAKEY2 = 0x0C;

  ANCTL->HSI48ENR = 0x00;
  ANCTL->HSI48ENR = 0x01;
  
  while((ANCTL->HSI48SR & 0x01) == 0);

  FLASH->ACR = FLASH_ACR_LATENCY;
  RCC->SYSCLKPRE1 = 0x00;
  RCC->SYSCLKSRC = RCC_SYSCLKSRC_HSI48;
  RCC->SYSCLKUEN = RCC_SYSCLKUEN_ENA;
  
//  /* Before flash erase or programming, FCUCLK must be configured to 8MHz */
//  // FCUCLK = HSI48 / 6 = 8MHz
//  RCC->FCUCLKSRC = RCC_FCUCLKSRC_NONE;
//  RCC->FCUCLKPRE2 = RCC_FCUCLKPRE2_SRCEN;
//  RCC->FCUCLKPRE1 = RCC_FCUCLKPRE1_DIVEN | RCC_FCUCLKPRE1_RATIO_6;
//  RCC->FCUCLKSRC = RCC_FCUCLKSRC_HSI48;

}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 *         The SystemCoreClock variable contains the core clock (HCLK), it can
 *         be used by the user application to setup the SysTick timer or configure
 *         other parameters.
 * @note   Each time the core clock (HCLK) changes, this function must be called
 *         to update SystemCoreClock variable value. Otherwise, any configuration
 *         based on this variable will be incorrect.   
 * @param  None
 * @return None
 */
void SystemCoreClockUpdate (void)
{
}

