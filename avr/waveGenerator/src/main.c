#define F_CPU 16000000
#include "wavetracer.h"
#include <avr/io.h>
#include <util/delay.h>

uint8_t buffer[1024];

void serialWrite(const uint8_t *data, const uint8_t *size)
{
    return;
}

uint8_t serialRead(uint8_t *data)
{
    return 0;
}

void output(const uint8_t data)
{
    return;
}

void main(void)
{
    WaveConfig waveConfig;
    waveConfig.bufferSize = 1024;
    waveConfig.buffer = buffer;
    waveConfig.useBufferWrapper = 0;
    waveConfig.serialWrite = serialWrite;
    waveConfig.serialRead = serialRead;
    waveConfig.output = output;
    
    configWaveTracer(&waveConfig);
    
}


