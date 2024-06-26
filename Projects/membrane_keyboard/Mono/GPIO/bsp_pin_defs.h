/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PIN_DEFS_H__
#define __PIN_DEFS_H__

/* Includes ------------------------------------------------------------------*/
#include "mono.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

// useful for direct pin mapping
#define NO_PIN (pin_t)(~0)

#define A0     PAL_LINE(GPIOA, 0)
#define A1     PAL_LINE(GPIOA, 1)
#define A2     PAL_LINE(GPIOA, 2)
#define A3     PAL_LINE(GPIOA, 3)
#define A4     PAL_LINE(GPIOA, 4)
#define A5     PAL_LINE(GPIOA, 5)
#define A6     PAL_LINE(GPIOA, 6)
#define A7     PAL_LINE(GPIOA, 7)
#define A8     PAL_LINE(GPIOA, 8)
#define A9     PAL_LINE(GPIOA, 9)
#define A10    PAL_LINE(GPIOA, 10)
#define A11    PAL_LINE(GPIOA, 11)
#define A12    PAL_LINE(GPIOA, 12)
#define A13    PAL_LINE(GPIOA, 13)
#define A14    PAL_LINE(GPIOA, 14)
#define A15    PAL_LINE(GPIOA, 15)
#define B0     PAL_LINE(GPIOB, 0)
#define B1     PAL_LINE(GPIOB, 1)
#define B2     PAL_LINE(GPIOB, 2)
#define B3     PAL_LINE(GPIOB, 3)
#define B4     PAL_LINE(GPIOB, 4)
#define B5     PAL_LINE(GPIOB, 5)
#define B6     PAL_LINE(GPIOB, 6)
#define B7     PAL_LINE(GPIOB, 7)
#define B8     PAL_LINE(GPIOB, 8)
#define B9     PAL_LINE(GPIOB, 9)
#define B10    PAL_LINE(GPIOB, 10)
#define B11    PAL_LINE(GPIOB, 11)
#define B12    PAL_LINE(GPIOB, 12)
#define B13    PAL_LINE(GPIOB, 13)
#define B14    PAL_LINE(GPIOB, 14)
#define B15    PAL_LINE(GPIOB, 15)
#define C0     PAL_LINE(GPIOC, 0)
#define C1     PAL_LINE(GPIOC, 1)
#define C2     PAL_LINE(GPIOC, 2)
#define C3     PAL_LINE(GPIOC, 3)
#define C4     PAL_LINE(GPIOC, 4)
#define C5     PAL_LINE(GPIOC, 5)
#define C6     PAL_LINE(GPIOC, 6)
#define C7     PAL_LINE(GPIOC, 7)
#define C8     PAL_LINE(GPIOC, 8)
#define C9     PAL_LINE(GPIOC, 9)
#define C10    PAL_LINE(GPIOC, 10)
#define C11    PAL_LINE(GPIOC, 11)
#define C12    PAL_LINE(GPIOC, 12)
#define C13    PAL_LINE(GPIOC, 13)
#define C14    PAL_LINE(GPIOC, 14)
#define C15    PAL_LINE(GPIOC, 15)
#define C16    PAL_LINE(GPIOC, 16)
#define C17    PAL_LINE(GPIOC, 17)
#define C18    PAL_LINE(GPIOC, 18)
#define C19    PAL_LINE(GPIOC, 19)
#define C20    PAL_LINE(GPIOC, 20)
#define C21    PAL_LINE(GPIOC, 21)
#define C22    PAL_LINE(GPIOC, 22)
#define C23    PAL_LINE(GPIOC, 23)
#define C24    PAL_LINE(GPIOC, 24)
#define C25    PAL_LINE(GPIOC, 25)
#define C26    PAL_LINE(GPIOC, 26)
#define C27    PAL_LINE(GPIOC, 27)
#define C28    PAL_LINE(GPIOC, 28)
#define C29    PAL_LINE(GPIOC, 29)
#define C30    PAL_LINE(GPIOC, 30)
#define C31    PAL_LINE(GPIOC, 31)
#define C32    PAL_LINE(GPIOC, 32)
#define D0     PAL_LINE(GPIOD, 0)
#define D1     PAL_LINE(GPIOD, 1)
#define D2     PAL_LINE(GPIOD, 2)
#define D3     PAL_LINE(GPIOD, 3)
#define D4     PAL_LINE(GPIOD, 4)
#define D5     PAL_LINE(GPIOD, 5)
#define D6     PAL_LINE(GPIOD, 6)
#define D7     PAL_LINE(GPIOD, 7)
#define D8     PAL_LINE(GPIOD, 8)
#define D9     PAL_LINE(GPIOD, 9)
#define D10    PAL_LINE(GPIOD, 10)
#define D11    PAL_LINE(GPIOD, 11)
#define D12    PAL_LINE(GPIOD, 12)
#define D13    PAL_LINE(GPIOD, 13)
#define D14    PAL_LINE(GPIOD, 14)
#define D15    PAL_LINE(GPIOD, 15)

/* Suppress warning messages */
#if defined(__CC_ARM)
// Suppress warning message: extended constant initialiser used
#  pragma diag_suppress 1296
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#endif

#endif /* __PIN_DEFS_H__ */
