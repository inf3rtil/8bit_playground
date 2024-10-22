#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

unsigned char wave[7000] = {0};
unsigned char wave1[7000] = {0};
unsigned char wave2[7000] = {0};
unsigned char wave3[7000] = {0};

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


