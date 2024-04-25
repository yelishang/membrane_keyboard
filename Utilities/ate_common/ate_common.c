#include "ate_common.h"


__ASM void ate_delay_n(uint32_t n)
{
LB_LOOP
  SUBS  r0, r0, #1
  BCS   LB_LOOP
  BX    LR
}


void ate_copy_words(uint32_t *dst, const uint32_t *src, uint32_t n)
{
  uint32_t i;
  for (i = 0; i < n; i++)
  {
    dst[i] = src[i];
  }
}

uint32_t ate_cmp_words(const uint32_t *w1, const uint32_t *w2, uint32_t n)
{
  uint32_t i;
  for (i = 0; i < n; i++)
  {
    if (w1[i] != w2[i])
    {
      return 1;
    }
  }
  return 0;
}

