#ifndef __UART__
#define __UART__

#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(uint16_t speed);

void uart_sendchar(uint8_t data);

#endif
