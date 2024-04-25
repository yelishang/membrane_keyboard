/**
 * @file    mono_flash.h
 * @author  Westberry Application Team
 * @version V0.0.1
 * @date    15-June-2023
 * @brief   This file contains all the functions prototypes for the FLASH firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MONO_FLASH_H
#define __MONO_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mono.h"

/** @addtogroup MONO_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void FLASH_Unlock(void);
void FLASH_Lock(void);
uint32_t FLASH_ErasePage(uint32_t Page_Address);
uint32_t FLASH_EraseBulk(void);
uint32_t FLASH_ProgramWord(uint32_t Address, uint32_t Data);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __MONO_FLASH_H */
