#ifndef __ATE_COMMON_H
#define __ATE_COMMON_H

#include "mono.h"



#define ATE_TEST_STAGE_1    0x00070000
#define ATE_TEST_STAGE_2    0x00500000
#define ATE_TEST_STAGE_3    0x03000000
#define ATE_TEST_STAGE_4    0x10000000


void ate_delay_n(uint32_t n);
void ate_copy_words(uint32_t *dst, const uint32_t *src, uint32_t n);
uint32_t ate_cmp_words(const uint32_t *w1, const uint32_t *w2, uint32_t n);

#endif /* __ATE_COMMON_H */
