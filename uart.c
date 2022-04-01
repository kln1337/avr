#include "uart.h"

void uart_init(uint16_t speed)
{
    UBRR0H = (uint8_t) speed >> 8;
    UBRR0L = (uint8_t) speed;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (3 << UCSZ00);
}

void uart_sendchar(uint8_t data)
{
    while (!(UCSR0A) & (1 << UDRE0));
    UDR0 = data;
}
