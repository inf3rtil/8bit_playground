#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


void main(void)
{
    DDRB = 0b00100000;
    while(1)
	{
	    PORTB = 0b00100000;
	    _delay_ms(500);
	    PORTB = 0b00000000;
	    _delay_ms(100);
	}
}


