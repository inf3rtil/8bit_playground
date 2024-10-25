#ifndef _WAVE_TRACER_H
#define _WAVE_TRACER_H
#include <stdint.h>

typedef struct{
    uint16_t bufferSize;
    uint8_t *buffer;
    uint8_t useBufferWrapper;
    void (*serialWrite) (const uint8_t *data, const uint8_t size);
    uint8_t (*serialRead) (uint8_t *data);
    uint8_t (*bufferRead) (const uint8_t address);
    void (*bufferWrite) (const uint8_t address, const uint8_t data);
    void (*output) (const uint8_t data);
}WaveConfig;

uint8_t configWaveTracer(const WaveConfig *cfg);
uint8_t cmdWaveTracer(const uint8_t cmd);


#endif
