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
    $ make all flash
