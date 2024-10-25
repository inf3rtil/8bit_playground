#include "wavetracer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#define FOSC 16000000
#define BAUD FOSC/16/9600-1

uint8_t buffer[1024];

void initMcu(void)
{
    DDRB = 0xFF;
    SREG |= 0x80 ;
}
    
void initSerial(unsigned char baud)
{
    UBRR0L = (unsigned char) (baud);
    UBRR0H = (unsigned char) (baud >> 8);
    UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
} 

void serialWrite(const uint8_t *data, const uint8_t size)
{
    for(uint8_t i = 0; i < size; i++)
	{
	    while ( !( UCSR0A & (1<<UDRE0)) );
	    UDR0 = data[i];
	}
}

void output(const uint8_t data)
{
    return;
    
}

int main(void)
{
    initMcu();
    initSerial(BAUD);
    WaveConfig waveConfig;
    waveConfig.bufferSize = 1024;
    waveConfig.buffer = buffer;
    waveConfig.useBufferWrapper = 0;
    waveConfig.serialWrite = &serialWrite;
    waveConfig.output = &output;
    configWaveTracer(&waveConfig);
    const char *hello = "Te Amo tarsila\n";
    serialWrite((uint8_t*) hello, strlen(hello));
    while(1)
	{
	    ;
	}
}

ISR(USART_RX_vect)
{
    cmdWaveTracer((uint8_t)(UDR0));    
}


