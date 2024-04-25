/**
  * @file    Project/Template/mono_it.h
  * @author  WestberryTech Application Team
  * @version V0.0.1
  * @date    10-October-2018
  * @brief   This file contains the headers of the interrupt handlers.
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MONO_IT_H
#define __MONO_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "mono.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MONO_IT_H */
