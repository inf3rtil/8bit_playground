/*
 * File:   newmain.c
 * Author: infertil
 *
 * Created on September 17, 2024, 4:15 PM
 */

// PIC16F648A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 11059200
#include <xc.h>

enum serialState{
    START_MSG = 'B',
    END_MSG
};

enum serialCommand{
    SET_WAVE = 'S',
    GET_WAVE,
    SET_TIME,
    GET_TIME,
    START_WAVE,
    STORE_WAVE
};
/*
unsigned char v0[30] = {
    129, 131, 134, 136, 138, 140, 142, 145, 147, 149,
    151, 153, 156, 158, 160, 162, 164, 166, 168, 170,
    173, 175, 177, 179, 181, 183, 185, 187, 189, 191
};

unsigned char v1[30] = {
    192, 194, 196, 198, 200, 202, 203, 205, 207, 209,
    210, 212, 214, 215, 217, 218, 220, 221, 223, 224,
    226, 227, 228, 230, 231, 232, 234, 235, 236, 237
};

unsigned char v2[30] = {
    238, 239, 240, 241, 242, 243, 244, 245, 246, 246,
    247, 248, 248, 249, 250, 250, 251, 251, 252, 252,
    252, 253, 253, 253, 254, 254, 254, 254, 254, 254
};

unsigned char v3[30] = {
    254, 254, 254, 254, 254, 253, 253, 253, 252, 252,
    252, 251, 251, 250, 250, 249, 248, 248, 247, 246,
    246, 245, 244, 243, 242, 241, 240, 239, 238, 237
};

unsigned char v4[30] = {
    236, 235, 234, 232, 231, 230, 228, 227, 226, 224,
    223, 221, 220, 218, 217, 215, 214, 212, 210, 209,
    207, 205, 203, 202, 200, 198, 196, 194, 192, 191
};

unsigned char v5[30] = {
    189, 187, 185, 183, 181, 179, 177, 175, 173, 170,
    168, 166, 164, 162, 160, 158, 156, 153, 151, 149,
    147, 145, 142, 140, 138, 136, 134, 131, 129, 127
};
 */
unsigned char v0[30] = {0};
unsigned char v1[30] = {0};
unsigned char v2[30] = {0};
unsigned char v3[30] = {0};
unsigned char v4[30] = {0};
unsigned char v5[30] = {0};
unsigned char *data[6] = {v0, v1, v2, v3, v4, v5};

unsigned char getValue(unsigned char pos)
{
    if(pos<30){
        return data[0][pos];
    }
    else if(pos<60){
        pos = pos - 30;
        return data[1][pos];
    }
    else if(pos<90){
        pos = pos - 60;
        return data[2][pos];
    }
    else if(pos<120){
        pos = pos - 90;
        return data[3][pos];
    }
    else if(pos<150){
        pos = pos - 120;
        return data[4][pos];
    }
    else if(pos<180){
        pos = pos - 150;
        return data[5][pos];
    }
    return 0;
}


void writeWaveToRam(char pos, const unsigned char value){
    if(pos<30){
        data[0][pos] = value;
    }
    else if(pos<60){
        pos = pos - 30;
        data[1][pos] = value;
    }
    else if(pos<90){
        pos = pos - 60;
        data[2][pos] = value;
    }
    else if(pos<120){
        pos = pos - 90;
        data[3][pos] = value;
    }
    else if(pos<150){
        pos = pos - 120;
        data[4][pos] = value;
    }
    else if(pos<180){
        pos = pos - 150;
        data[5][pos] = value;
    }
}


void config_usart(){
    TRISB1 = 1;
    TRISB2 = 0;
    SYNC = 0; //modo assincrono
    SPBRG = 5; //baud rate de 115200
    BRGH = 1;
    TX9 = 0; //desabilita bit 9 (TX9D) de ser transmitido
    RX9 = 0; //desabilita bit 9 (RX9D) de ser recebido
    TXEN = 1; //habilita transmissão serial (TX)
    SPEN = 1; //habilita toda a porta serial
    CREN = 1;
    TXIE = 0;
    RCIE = 1; // interrupt receive enable
}

void print(const char *data)
{
    char asciiByte;
    do{
        while(!TRMT);
        TXREG = *data;
        data++;
    }
    while(*data != '\0');
}


void delay(unsigned int time){
    for(unsigned int x = 0; x < time; x++){
        NOP();
    }
}

void (*serialHandle) (unsigned char) = NULL;

void sendAck(){
    print("OK\r\n");
}

void waitStart(unsigned char data);

void setWave(unsigned char data){
    static unsigned char address = 0xFF;
    if(address == 0xFF){
        address = data;
    }
    else{
        writeWaveToRam(address, data);
        address = 0xFF;
        sendAck();
        serialHandle = &waitStart;
    }
}

void getCmd(unsigned char data){
    if(data == SET_WAVE){
        serialHandle = &setWave;
    }
}

void waitStart(unsigned char data){
    if(data == START_MSG){
        serialHandle = &getCmd;
    }
}

void main(void) {
    CMCON = 0x07;
    TRISA = 0x00;
    TRISB = 0x00;
    delay(1000);
    config_usart();
    
    GIE = 1;
    PEIE = 1;
    const char * msg = "Hello DAC World\n";
    print(msg);
    unsigned char value;
    serialHandle = &waitStart;
    while(1)
    {
        for(unsigned char x = 0; x < 180; x++)
        {
            value = getValue(x);
            PORTA = value;
            PORTB = value;
            delay(10);
            //print(x);
        }
        /*for(unsigned char x = 0; x < 180; x++ )
        {
            value = 255 - getValue(x);
            PORTA = value;
            PORTB = value;
            delay(10);
            //print(x);
        }*/
    }
}

void __interrupt() serial()
{
    if(RCIE && RCIF){
        RCIF = 0;
        serialHandle(RCREG);
    }
    return;
}