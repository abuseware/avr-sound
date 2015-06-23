##Description
Simple sound player using ATmega328p and MCP4822.

##Requirements
###Build
 * GNU or BSD make
 * GCC for AVR
 * AVRdude with ELF format support
 * SOX audio converter (wav → raw)
 * Python v3.x (raw audio → C header)

###Run
 * ATmega328p 8-16MHz
 * MCP4822 DAC
 * LM358 OpAmp (DACs is useless)
 * Speaker

##How to?
1. Copy your sound file as *sound.wav*, but remember - samples are stored in internal flash, use short files (<4s 8kHz, <2s 16kHz, <1.5s 22.05kHz, …)!
2. Apply desired samplerate in Makefile
3. $ make all flash
