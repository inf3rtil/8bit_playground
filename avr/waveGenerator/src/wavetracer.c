#include "wavetracer.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/cpufunc.h>

static WaveConfig _cfg;
static uint16_t address;
static uint16_t delay=0;

enum serialCommand{
    START_MSG = 'B',
    END_MSG = 'E',
    SET_WAVE = 'S',
    GET_WAVE = 'G',
    SET_TIME = 'T',
    GET_TIME = 'P',
    START_WAVE = 'G',
    RESET_WAVE = 'R', 
    INVERT_WAVE = 'I',
    SET_SYMMETRY = 'Y'
};

static void writeWaveToRam(const uint16_t pos, const uint8_t value)
{
    if(pos < _cfg.bufferSize)
	{
	    _cfg.buffer[pos] = value;
	}
}

static void waitStart(const uint8_t data);
static void getCmd(const uint8_t data);
static void setAddressH(const uint8_t data);
static void setAddressL(const uint8_t data);
static void setValue(const uint8_t data); 

static void (*serialHandle) (const uint8_t) = &waitStart;

void sendAck(void)
{
    _cfg.serialWrite((uint8_t *)("ACK"), 3);
}

void sendNak(void)
{
    _cfg.serialWrite((uint8_t *)("NOK"), 3);
}

void setAddressH(uint8_t data){
    address = (data << 8);
    serialHandle = &setAddressL;
}

void setAddressL(uint8_t data)
{
    address += data;
    serialHandle = &setValue;
}

void setValue(uint8_t data)
{
    sendAck();
    writeWaveToRam(address, data);
    serialHandle = &waitStart;
}

void setTime(unsigned char data)
{
    delay = data;
    sendAck();
    serialHandle = &waitStart;
}

void getCmd(unsigned char data){
    if(data == SET_WAVE){
        serialHandle = &setAddressH;
    }
    else if(data == SET_TIME)
	{
	    serialHandle = &setTime;
	}
    else
	{
	    serialHandle = &waitStart;
	}
}

void waitStart(unsigned char data){
    if(data == START_MSG)
	{
	    serialHandle = &getCmd;
	}
    else
	{
	    serialHandle = &waitStart;
	}
}

uint8_t configWaveTracer(const WaveConfig *cfg)
{
    _cfg = *cfg;
}

uint8_t cmdWaveTracer(const uint8_t cmd)
{
    serialHandle(cmd);
}

inline static void delayWave(void)
{
    for (uint16_t i = 0; i < delay; i++)
	{
	    _NOP();
	}
}

void updateWave(void)
{
    PORTC= ~PORTC;
    for(uint16_t i = 0; i < 1024; i++)
	{
	    PORTB = _cfg.buffer[i];
	    PORTD = _cfg.buffer[i];
	    if((i%5)) delayWave();
	}
}
