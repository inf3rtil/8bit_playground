PROJECT=blinker
TARGET=main

# Assembler
AS = avra

# Programmer options
PROG_TOOL = usbasp
PROG_DEVICE = m328p

BINDIR = bin

.PHONY : all clean download

all: $(TARGET).hex

$(TARGET).hex: $(BINDIR)
	$(AS) -o $(BINDIR)/$@ main.asm

download: all
	avrdude -p $(PROG_DEVICE) -c $(PROG_TOOL) -U flash:w:$(BINDIR)/$(TARGET).hex

$(BINDIR):
	mkdir $(BINDIR)

.PHONY : clean
clean:
	rm -rf $(BINDIR) *.obj *.hex
