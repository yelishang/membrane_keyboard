#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum { FLASH_BUSY = 1, FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_ERROR_OPT, FLASH_COMPLETE, FLASH_TIMEOUT, FLASH_BAD_ADDRESS } FLASH_Status;

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x4) && ((ADDRESS) < 0x7FFF))

FLASH_Status FLASH_Program_Word(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_Program_HalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramPage(uint32_t PageAddr, uint8_t *Data);

void FLASH_Unlock(void);
void FLASH_Lock(void);

#ifdef __cplusplus
}
#endif
