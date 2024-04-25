#include "hal_pal_lld.h"

/**
 * @brief   Pads mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 * @note    @p PAL_MODE_UNCONNECTED is implemented as push pull at minimum
 *          speed.
 *
 * @param[in] port      the port identifier
 * @param[in] mask      the group mask
 * @param[in] mode      the mode
 *
 * @notapi
 */
void _pal_lld_setgroupmode(ioportid_t port, ioportmask_t mask, iomode_t mode) {
  
  
  uint32_t tmp, pinmask, pinmask2, afl_mask, afh_mask;

  pinmask = mask;
  pinmask2 = 0;
  afl_mask = 0;
  afh_mask = 0;
  for (tmp = 0 ; tmp < 0x10; tmp++)
  {
    if (pinmask & (0x1U << tmp))
    {
      pinmask2 |= 0x3U << (tmp << 1);
      if (tmp < 8) {
        afl_mask |= 0xFU << (tmp << 2);
      }
      else {
        afh_mask |= 0xFU << ((tmp-8) << 2);
      }
    }
  }

  port->OSPEEDR = (port->OSPEEDR & ~ pinmask) | ((((mode >> 20) & 0x1) * 0xFFFFFFFFU) & pinmask);
  port->OTYPER = (port->OTYPER & ~pinmask) | ((((mode >> 24) & 0x1) * 0xFFFFFFFFU) & pinmask);
  port->MODER = (port->MODER & ~pinmask2) | ((((mode >> 28) & 0x3) * 0x55555555U) & pinmask2);
  port->PUPDR = (port->PUPDR & ~pinmask2) | ((((mode >> 16) & 0x3) * 0x55555555U) & pinmask2);

  tmp = (mode & 0xF) * 0x11111111U;
  port->AFRL = (port->AFRL & ~afl_mask) | (tmp & afl_mask);
  port->AFRH = (port->AFRH & ~afh_mask) | (tmp & afh_mask);
  
}
