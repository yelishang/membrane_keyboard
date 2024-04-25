#pragma once

#include "mono.h"

void KeyLed_Init(void);
void KeyLed_Start(void);
void rgb_matrix_set_color(uint8_t row, uint8_t col, uint8_t num);

/**
 * @brief   Decodes a port identifier from a line identifier.
 */
#define PCT_PORT(line)                                                      \
  ((PCT_TypeDef *)(((uint32_t)(line)) & 0xFFFFFF00U))

/**
 * @brief   Decodes a pad identifier from a line identifier.
 */
#define PCT_PAD(line)                                                       \
  ((uint32_t)((uint32_t)(line) & 0x000000FFU))
  
