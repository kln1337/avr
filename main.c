#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"

#define BAUD(s) (uint16_t)(F_CPU/16/s - 1)

static inline void invert_output(void)
{
    PORTB ^= 1 << PORTB5;
}

static inline void print_led(uint8_t val)
{
    if (val == 0)
        PORTB &= ~(1 << PORTB5);
    else
        PORTB |= 1 << PORTB5;
}

void timer_init (void)
{
    TCCR1A &= ~(1 << WGM10 | 1 << WGM11);
    TCCR1B |= (1 << WGM12 | 1 << CS12);
    OCR1AH = 0xF4;
    OCR1AL = 0x24;
    TIMSK1 |= 1 << OCIE1A | 1 << TOIE1;
}

ISR (TIMER1_COMPA_vect)
{
    invert_output();
}

ISR (TIMER1_OVF_vect)
{
    PORTB &= ~(1 << PORTB5);
}

// DDR* - direction 1-output; 0-input
void main ()
{
    timer_init();
    uart_init(BAUD(19200));
    // PORTB5 output  
    DDRB = 1 << PORTB5;
    
    // enable interrupts
    sei();
    
    PORTB |= 1 << PORTB5;
    uart_sendchar(OCR1AH);
    uart_sendchar(OCR1AL);
    while (1) {
        /* PORTB |= (1 << PORTB5); // High level */
        /* _delay_ms(1000); */
        /* PORTB &= ~(1 << PORTB5); // Low level */
        /* _delay_ms(1000); */
        uart_sendchar(OCR1AH);
        uart_sendchar(OCR1AL);
        _delay_ms(5000);
    }
}
