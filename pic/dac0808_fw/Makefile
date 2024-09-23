PROJECT=DAC0808
TARGET=main

# Compiler options
CC="/opt/microchip/xc8/v2.50/bin/xc8-cc"
LD="/opt/microchip/xc8/v2.50/bin/xc8-cc"
MCU=16F648A
CFLAGS = -mcpu=$(MCU)

# sources
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.p1)

.PHONY : all clean download

all: $(TARGET).hex

$(OBJS): $(OBJDIR)/%.p1: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).hex: $(OBJS) | $(BINDIR)
	$(LD) $(CFLAGS) $(OBJS) -o $(BINDIR)/$@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

.PHONY : clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
