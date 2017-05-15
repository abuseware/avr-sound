MCU=atmega328p
FREQ=20000000UL

CC=avr-gcc
LD=avr-ld
PY=python3
AVRDUDE=avrdude
SOX=sox

CFLAGS=-O3 -Wl,-s -std=c11 -pedantic -mmcu=$(MCU) -DF_CPU=$(FREQ) -DPCM_FREQ=$(PCM_FREQ)
LDFLAGS=-Wl,-O1,--strip-all,--sort-common,--as-needed

SOXFLAGS=-G
SOXFILTER=gain -e 24

PCM_FREQ=8000

.SUFFIXES: .wav .h

.PHONY: clean flash

all: sound.h main

clean:
	-rm -f *.o *.u8 sound.h main

flash:
	$(AVRDUDE) -c usbasp -p m328p -U flash:w:main

.wav.h:
	$(SOX) $(SOXFLAGS) $< -r $(PCM_FREQ) -c 1 $<.u8 $(SOXFILTER)
	$(PY) raw2h.py $<.u8 > $@

main: main.o dac.o spi.o
	$(CC) $(LDFLAGS) -o $@ $^
