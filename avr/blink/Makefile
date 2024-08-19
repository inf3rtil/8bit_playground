PROJECT=blink

# Compiler options
CC = avr-gcc
MCU = atmega328p
CFLAGS = -mmcu=$(MCU)

# Programmer options
PROG_TOOL = usbasp
PROG_DEVICE = m328p

vpath %.c src

all: $(PROJECT).hex

%.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

%.elf: %.o
	$(CC) $(CFLAGS) -o $@ $<

download: all
	avrdude -p $(PROG_DEVICE) -c $(PROG_TOOL) -U flash:w:$(PROJECT).hex 

clean:
	rm -rf *.o  *.hex *.elf
