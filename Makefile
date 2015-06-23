MCU=atmega328p
FREQ=16000000UL

CC=avr-gcc
PY=python3
AVRDUDE=avrdude
SOX=sox

CFLAGS=-O3 -Wl,-s -std=c11 -pedantic -mmcu=$(MCU) -DF_CPU=$(FREQ) -DPCM_FREQ=$(PCM_FREQ)
SOXFLAGS=-G
SOXFILTER=gain -e 24

PCM_FREQ=16000

OBJ=main.o dac.o spi.o

.SUFFIXES: .wav .h

.PHONY: all clean flash main

all: sound.h $(HDR) $(OBJ) main

clean:
	-rm -f *.o *.u8 sound.h main

flash:
	$(AVRDUDE) -c usbasp -p m328p -U flash:w:main

.wav.h:
	$(SOX) $(SOXFLAGS) $< -r $(PCM_FREQ) -c 1 sound.u8 $(SOXFILTER)
	$(PY) raw2h.py sound.u8 > $@

main:
	${CC} ${CFLAGS} -o $@ ${OBJ}
