#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "mono.h"

typedef void (*palcallback_t)(void *arg);
typedef GPIO_TypeDef *ioportid_t;
/**
 * @brief   Type of digital I/O port sized unsigned integer.
 */
typedef uint32_t ioportmask_t;

/**
 * @brief   Type of digital I/O modes.
 */
typedef uint32_t iomode_t;

/**
 * @brief   Type of an I/O line.
 */
typedef uint32_t ioline_t;

#define PAL_MONO_MODE_MASK                     (0x00000000U)
#define PAL_MONO_MODE_INPUT                    (0x00000000U)
#define PAL_MONO_MODE_OUTPUT                   (0x10000000U)
#define PAL_MONO_MODE_ALTERNATE                (0x20000000U)
#define PAL_MONO_MODE_ANALOG                   (0x30000000U)

#define PAL_MONO_OTYPE_MASK                    (0x00000000U)
#define PAL_MONO_OTYPE_PUSHPULL                (0x00000000U)
#define PAL_MONO_OTYPE_OPENDRAIN               (0x01000000U)

#define PAL_MONO_OSPEED_MASK                   (0x00000000U)
#define PAL_MONO_OSPEED_LOW                    (0x00100000U)
#define PAL_MONO_OSPEED_HIGH                   (0x00000000U)

#define PAL_MONO_PUPDR_MASK                    (0x00000000U)
#define PAL_MONO_PUPDR_FLOATING                (0x00000000U)
#define PAL_MONO_PUPDR_PULLUP                  (0x00010000U)
#define PAL_MONO_PUPDR_PULLDOWN                (0x00020000U)

#define PAL_MONO_ALTERNATE_MASK                (15U << 7U)
#define PAL_MONO_ALTERNATE(n)                  ((n) << 7U)

#define PAL_MONO_CURRENT_MASK                  (3U << 11U)
#define PAL_MONO_CURRENT_LEVEL0                (0U << 11U)
#define PAL_MONO_CURRENT_LEVEL1                (1U << 11U)
#define PAL_MONO_CURRENT_LEVEL2                (2U << 11U)
#define PAL_MONO_CURRENT_LEVEL3                (3U << 11U)


/**
 * @brief   Alternate function.
 *
 * @param[in] n         alternate function selector
 */
#define PAL_MODE_ALTERNATE(n)                  (PAL_MONO_MODE_ALTERNATE |   \
                                                PAL_MONO_ALTERNATE(n))
/** @} */

/**
 * @name    Standard I/O mode flags
 * @{
 */
/**
 * @brief   Implemented as input.
 */
#define PAL_MODE_RESET                         PAL_MONO_MODE_INPUT

/**
 * @brief   Implemented as input with pull-up.
 */
#define PAL_MODE_UNCONNECTED                   PAL_MODE_INPUT_PULLUP

/**
 * @brief   Regular input high-Z pad.
 */
#define PAL_MODE_INPUT                         PAL_MONO_MODE_INPUT

/**
 * @brief   Input pad with weak pull up resistor.
 */
#define PAL_MODE_INPUT_PULLUP                  (PAL_MONO_MODE_INPUT |       \
                                                PAL_MONO_PUPDR_PULLUP)

/**
 * @brief   Input pad with weak pull down resistor.
 */
#define PAL_MODE_INPUT_PULLDOWN                (PAL_MONO_MODE_INPUT |       \
                                                PAL_MONO_PUPDR_PULLDOWN)

/**
 * @brief   Analog input mode.
 */
#define PAL_MODE_INPUT_ANALOG                  PAL_MONO_MODE_ANALOG

/**
 * @brief   Push-pull output pad.
 */
#define PAL_MODE_OUTPUT_PUSHPULL               (PAL_MONO_MODE_OUTPUT |      \
                                                PAL_MONO_OTYPE_PUSHPULL)

/**
 * @brief   Open-drain output pad.
 */
#define PAL_MODE_OUTPUT_OPENDRAIN              (PAL_MONO_MODE_OUTPUT |      \
                                                PAL_MONO_OTYPE_OPENDRAIN)
/** @} */

/**
 * @brief   Forms a line identifier.
 * @details A port/pad pair are encoded into an @p ioline_t type. The encoding
 *          of this type is platform-dependent.
 * @note    In this driver the pad number is encoded in the lower 4 bits of
 *          the GPIO address which are guaranteed to be zero.
 */
#define PAL_LINE(port, pad)                                                 \
  ((ioline_t)((uint32_t)(port)) | ((uint32_t)(pad)))

/**
 * @brief   Decodes a port identifier from a line identifier.
 */
#define PAL_PORT(line)                                                      \
  ((GPIO_TypeDef *)(((uint32_t)(line)) & 0xFFFFFFF0U))

/**
 * @brief   Decodes a pad identifier from a line identifier.
 */
#define PAL_PAD(line)                                                       \
  ((uint32_t)((uint32_t)(line) & 0x0000000FU))


/**
 * @brief   Port bit helper macro.
 * @details This macro calculates the mask of a bit within a port.
 *
 * @param[in] n         bit position within the port
 * @return              The bit mask.
 */
#define PAL_PORT_BIT(n) ((ioportmask_t)(1U << (n)))

/**
 * @brief   Reads an I/O port.
 * @details This function is implemented by reading the GPIO IDR register, the
 *          implementation has no side effects.
 * @note    This function is not meant to be invoked directly by the application
 *          code.
 *
 * @param[in] port      port identifier
 * @return              The port bits.
 *
 * @notapi
 */
#define pal_lld_readport(port) ((ioportmask_t)((port)->IDR))
#define palReadLine(line) ((pal_lld_readport(PAL_PORT(line)) >> (PAL_PAD(line))) & 1U)

/**
 * @brief   Reads the output latch.
 * @details This function is implemented by reading the GPIO ODR register, the
 *          implementation has no side effects.
 * @note    This function is not meant to be invoked directly by the application
 *          code.
 *
 * @param[in] port      port identifier
 * @return              The latched logical states.
 *
 * @notapi
 */
#define pal_lld_readlatch(port) ((ioportmask_t)((port)->ODR))

/**
 * @brief   Writes on a I/O port.
 * @details This function is implemented by writing the GPIO ODR register, the
 *          implementation has no side effects.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be written on the specified port
 *
 * @notapi
 */
#define pal_lld_writeport(port, bits) ((port)->ODR = (ioportmask_t)(bits))
#define palToggleLine(line) palTogglePort(PAL_PORT(line), pal_lld_readlatch(port) ^ PAL_PORT_BIT(PAL_PAD(line)))

/**
 * @brief   Sets a bits mask on a I/O port.
 * @details This function is implemented by writing the GPIO BSRR register, the
 *          implementation has no side effects.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be ORed on the specified port
 *
 * @notapi
 */
#define pal_lld_setport(port, bits) ((port)->BSRR = (ioportmask_t)(bits))
#define palSetLine(line) pal_lld_setport(PAL_PORT(line), PAL_PORT_BIT(PAL_PAD(line)))

/**
 * @brief   Clears a bits mask on a I/O port.
 * @details This function is implemented by writing the GPIO BSRR register, the
 *          implementation has no side effects.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be cleared on the specified port
 *
 * @notapi
 */
#define pal_lld_clearport(port, bits) ((port)->BSRR = (ioportmask_t)((bits)<<16))
#define palClearLine(line) pal_lld_clearport(PAL_PORT(line), PAL_PORT_BIT(PAL_PAD(line)))

/**
 * @brief   Toggles a bits mask on a I/O port.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be XORed on the specified port
 *
 * @notapi
 */
#define pal_lld_toggleport(port, bits) ((port)->ODR ^= (ioportmask_t)(bits))

/**
 * @brief   Reads a group of bits.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @return              The group logical states.
 *
 * @notapi
 */
#define pal_lld_readgroup(port, mask, offset)                               \
  (((port)->IDR & !(mask << offset)) >> offset)

/**
 * @brief   Writes a group of bits.
 * @details This function is implemented by writing the GPIO BSRR register, the
 *          implementation has no side effects.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    the group bit offset within the port
 * @param[in] bits      bits to be written. Values exceeding the group
 *                      width are masked.
 *
 * @notapi
 */
#define pal_lld_writegroup(port, mask, offset, bits) {                      \
  uint32_t w ;                                                              \
  w = ((~(ioportmask_t)(bits) & (ioportmask_t)(mask)) << (16U + (offset))) |\
      ((ioportmask_t)(bits) & (ioportmask_t)(mask)) << (offset);            \
  (port)->BSRR = w;                                                         \
}

/**
 * @brief   Pads group mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @param[in] mode      group mode
 *
 * @notapi
 */
#define pal_lld_setgroupmode(port, mask, offset, mode)                      \
  _pal_lld_setgroupmode(port, mask << offset, mode)
#define palSetLineMode(line, mode)                                          \
  pal_lld_setgroupmode(PAL_PORT(line), PAL_PORT_BIT(PAL_PAD(line)), 0U, mode)

/**
 * @brief   Writes a logical state on an output pad.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @param[in] bit       logical value, the value must be @p PAL_LOW or
 *                      @p PAL_HIGH
 *
 * @notapi
 */
#define pal_lld_writepad(port, pad, bit) pal_lld_writegroup(port, 1, pad, bit)

#ifdef __cplusplus
extern "C" {
#endif
  void _pal_lld_setgroupmode(ioportid_t port,
                             ioportmask_t mask,
                             iomode_t mode);
#ifdef __cplusplus
}
#endif
