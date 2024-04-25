/**
 * @file    mono_flash.c
 * @author  Westberry Application Team
 * @version V0.0.1
 * @date    15-June-2023
 * @brief   This file provides all the FLASH firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "mono_flash.h"

/** @addtogroup MONO_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH
  * @brief FLASH driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup FLASH_Private_Functions
  * @{
  */

/**
 * @brief  Unlocks the FLASH controller.
 * @return None
 */
void FLASH_Unlock(void)
{
  FLASH->KEYR = 0x45670123;
  FLASH->KEYR = 0xCDEF89AB;
}

/**
 * @brief  Locks the FLASH controller.
 * @return None
 */
void FLASH_Lock(void)
{
  FLASH->CR |= FLASH_CR_LOCK;
}

/**
 * @brief  Erase a specified FLASH page.
 * @param  Page_Address: The page address to be erased.
 * @return 0 - OK,  1 - Failed
 */
uint32_t FLASH_ErasePage(uint32_t Page_Address)
{
  int state, prftbe;
  state = __get_PRIMASK();
  __disable_irq();
  prftbe = 0;
  if (FLASH->ACR & FLASH_ACR_PRFTBE) {
    prftbe = 1;
    FLASH->ACR &= ~FLASH_ACR_PRFTBE;
  }

  FLASH->SR |= (FLASH_SR_EOP | FLASH_SR_PGERR);
  FLASH->CR = FLASH_CR_CMD_PER;
  FLASH->AR = Page_Address;
  FLASH->CR |= FLASH_CR_START;
  while (FLASH->SR  & FLASH_SR_BSY);
  FLASH->CR &= ~FLASH_CR_CMD_Msk;
  FLASH->SR |= FLASH_SR_EOP;

  if (prftbe) {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  if (!state) {
    __enable_irq();
  }

  if (FLASH->SR & FLASH_SR_PGERR) {
    return 1;
  }
  return 0;
}

/**
 * @brief  Erase main flash memory.
 * @return 0 - OK,  1 - Failed
 */
uint32_t FLASH_EraseBulk(void)
{
  int state, prftbe;
  state = __get_PRIMASK();
  __disable_irq();
  prftbe = 0;
  if (FLASH->ACR & FLASH_ACR_PRFTBE) {
    prftbe = 1;
    FLASH->ACR &= ~FLASH_ACR_PRFTBE;
  }

  FLASH->SR |= (FLASH_SR_EOP | FLASH_SR_PGERR);
  FLASH->CR = FLASH_CR_CMD_MER;
  FLASH->AR = 0x08000000;
  FLASH->CR |= FLASH_CR_START;
  while (FLASH->SR  & FLASH_SR_BSY);
  FLASH->CR &= ~FLASH_CR_CMD_Msk;
  FLASH->SR |= FLASH_SR_EOP;

  if (prftbe) {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  if (!state) {
    __enable_irq();
  }

  if (FLASH->SR & FLASH_SR_PGERR) {
    return 1;
  }
  return 0;
}

/**
 * @brief  Programs the data to the specified address.
 * @param  Address: The address to be programmed.
 * @param  Data: The data to be programmed.
 * @return 0 - OK,  1 - Failed
 */
uint32_t FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  int state, prftbe;
  state = __get_PRIMASK();
  __disable_irq();
  prftbe = 0;
  if (FLASH->ACR & FLASH_ACR_PRFTBE) {
    prftbe = 1;
    FLASH->ACR &= ~FLASH_ACR_PRFTBE;
  }

  FLASH->SR |= (FLASH_SR_EOP | FLASH_SR_PGERR);
  FLASH->CR = FLASH_CR_CMD_PG;
  FLASH->AR = Address;
  FLASH->DR = Data;
  FLASH->CR |= FLASH_CR_START;
  while (FLASH->SR  & FLASH_SR_BSY);
  FLASH->CR &= ~FLASH_CR_CMD_Msk;
  FLASH->SR |= FLASH_SR_EOP;

  if (prftbe) {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  if (!state) {
    __enable_irq();
  }

  if (FLASH->SR & FLASH_SR_PGERR) {
    return 1;
  }
  return 0;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
