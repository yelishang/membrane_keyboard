#include "main.h"
#include "legacy_flash_ops.h"

#define WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS (8 * 1000) // +48k


#ifndef BACKING_STORE_WRITE_SIZE
#    define BACKING_STORE_WRITE_SIZE 2
#endif



#if BACKING_STORE_WRITE_SIZE == 2
typedef uint16_t backing_store_int_t;
#elif BACKING_STORE_WRITE_SIZE == 4
typedef uint32_t backing_store_int_t;
#elif BACKING_STORE_WRITE_SIZE == 8
typedef uint64_t backing_store_int_t;
#else
#    error Invalid BACKING_STORE_WRITE_SIZE, needs to be 2/4/8.
#endif


bool backing_store_write(uint32_t address, backing_store_int_t value) {
    uint32_t offset = ((WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS) + address);
    return FLASH_ProgramHalfWord(offset, ~value) == FLASH_COMPLETE;
}


bool backing_store_read(uint32_t address, backing_store_int_t* value) {
    uint32_t             offset = ((WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS) + address);
    backing_store_int_t* loc    = (backing_store_int_t*)offset;
    *value                      = ~(*loc);
  
    return true;
}
