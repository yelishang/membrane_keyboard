#ifndef __BSP_UART1_H
#define __BSP_UART1_H
#include "mono.h"


void uart1_init(uint32_t apbclk, uint32_t baud);
void uart1_send(const uint8_t* buffer, uint32_t length);



#endif

