PROJECT=blinker
TARGET=main

# Compiler options
CC = avr-gcc
MCU = atmega328p
CFLAGS = -time -I include -g -O3 -save-temps -mmcu=$(MCU)

# Programmer options
PROG_TOOL = usbasp
PROG_DEVICE = m328p

# sources
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY : all clean download

all: $(TARGET).hex

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(BINDIR)/$@

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -v -j .text -j .data -O ihex $(BINDIR)/$< $(BINDIR)/$@
	avr-size -C -x -t --mcu=$(MCU) $(BINDIR)/$<
download: all
	avrdude -p $(PROG_DEVICE) -c $(PROG_TOOL) -U flash:w:$(BINDIR)/$(TARGET).hex

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

.PHONY : clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
