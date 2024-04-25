#include "legacy_flash_ops.h"
#include "main.h"
#include <string.h>

#define MEMORY_1_ADDR  (0x08007C00)
#define MEMORY_2_ADDR  (0x08007E00)

#define MEMORY_FLAG_ADDR  (0x08007C00)

typedef union {
  uint8_t  data8[4];
  uint16_t date16[2];
  uint32_t date32;
} _MQ;

typedef union {
    uint32_t raw;
    struct {
        uint8_t memory_flag: 1;
    } memory_struct;
} memory;

static void EraseChip(void)
{
  FLASH->SR |= (FLASH_SR_EOP | FLASH_SR_PGERR);
  FLASH->CR = FLASH_CR_CMD_MER;
  FLASH->AR = 0x08000000;
  FLASH->CR |= FLASH_CR_START;
  while (FLASH->SR  & FLASH_SR_BSY);
  FLASH->CR &= ~FLASH_CR_CMD_Msk;
  FLASH->SR |= FLASH_SR_EOP;
}

static void ErasePage(uint32_t addr)
{
  FLASH->SR |= (FLASH_SR_EOP | FLASH_SR_PGERR);
  FLASH->CR = FLASH_CR_CMD_PER;
  FLASH->AR = addr;
  FLASH->CR |= FLASH_CR_START;
  while (FLASH->SR  & FLASH_SR_BSY);
  FLASH->CR &= ~FLASH_CR_CMD_Msk;
  FLASH->SR |= FLASH_SR_EOP;
}

static void ProgramWord(uint32_t addr, uint32_t data)
{
  FLASH->SR |= (FLASH_SR_EOP | FLASH_SR_PGERR);
  FLASH->CR = FLASH_CR_CMD_PG;
  FLASH->AR = addr;
  FLASH->DR = data;
  FLASH->CR |= FLASH_CR_START;
  while (FLASH->SR  & FLASH_SR_BSY);
  FLASH->CR &= ~FLASH_CR_CMD_Msk;
  FLASH->SR |= FLASH_SR_EOP;
}

FLASH_Status FLASH_Program_Optimize(uint32_t Address, uint32_t Data){
  FLASH_Status status = FLASH_BAD_ADDRESS;
  static memory memory_optimize;
  memory_optimize.raw =  M32(MEMORY_FLAG_ADDR);
  if (memory_optimize.memory_struct.memory_flag & 0x1){
    ErasePage(MEMORY_1_ADDR);
    for (int i=4; i < 512; i+=4)
    {
      if (i != Address)
        ProgramWord(MEMORY_1_ADDR + i, M32(MEMORY_2_ADDR + i));
    }
    
    for (int i=4; i < 512; i+=4)
    {
      if ((i != Address) && (M32(MEMORY_1_ADDR + i) == M32(MEMORY_2_ADDR + i))) {
        status = FLASH_ERROR_OPT;
      }
    }
    
    memory_optimize.memory_struct.memory_flag = 1;
    ProgramWord(MEMORY_1_ADDR, memory_optimize.raw);
    ProgramWord((MEMORY_1_ADDR + Address), Data);
    ErasePage(MEMORY_2_ADDR);
    status = FLASH_COMPLETE;
  } else {
    ErasePage(MEMORY_2_ADDR);
    for (int i=4; i < 512; i+=4)
    {
      if (i != Address)
        ProgramWord(MEMORY_1_ADDR + i, M32(MEMORY_2_ADDR + i));
    }
    
    for (int i=4; i < 512; i+=4)
    {
      if ((i != Address) && (M32(MEMORY_2_ADDR + i) == M32(MEMORY_1_ADDR + i))) {
        status = FLASH_COMPLETE;
      }
    }
    
    memory_optimize.memory_struct.memory_flag = 1;
    ProgramWord(MEMORY_2_ADDR, memory_optimize.raw);
    ProgramWord((MEMORY_2_ADDR + Address), Data);
    ErasePage(MEMORY_1_ADDR);
    status = FLASH_COMPLETE;
  }
  return status;
}

FLASH_Status FLASH_Program_Word(uint32_t Address, uint32_t Data){
  FLASH_Status status = FLASH_BAD_ADDRESS;
  static memory memory_optimize;
  memory_optimize.raw =  M32(MEMORY_FLAG_ADDR);
  uint32_t date_buff = 0;
  uint32_t     WriteAddr;
  
  if (memory_optimize.memory_struct.memory_flag & 0x1){
    WriteAddr = Address + MEMORY_2_ADDR;
  } else {
    WriteAddr = Address + MEMORY_1_ADDR;
  }
  
  if (IS_FLASH_ADDRESS(Address)) {
    FLASH_Unlock();
    if (M32(WriteAddr) == 0xFFFFFFFF) {
      memcpy(&date_buff, (void *)(WriteAddr), sizeof(date_buff));
      ProgramWord(WriteAddr, Data);
      
      if (memcmp(&Data, (void *)(WriteAddr), sizeof(date_buff)) != 0) {
        status =  FLASH_ERROR_OPT;
      }
    } else {
      status =  FLASH_Program_Optimize(Address, Data);
    }
    FLASH_Lock();
  }
  return status;
}


FLASH_Status FLASH_Program_HalfWord(uint32_t Address, uint16_t Data){

  FLASH_Status status = FLASH_BAD_ADDRESS;
  
  _MQ          pageBuffer;
  uint32_t     WriteAddr;
  uint16_t     PageOff;

  /* calculate which page is affected (Pagenum1/Pagenum2...PagenumN).*/
  PageOff      = Address % 4;
  WriteAddr    = Address - PageOff;

  if (IS_FLASH_ADDRESS(Address)) {
    if (PageOff < 2) {
      pageBuffer.date16[0] = Data;
    } else {
      pageBuffer.date16[1] = Data;
    }
    status = FLASH_Program_Word(WriteAddr, pageBuffer.date32);
  }
  return status;
}

