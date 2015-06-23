#pragma once
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

#define DAC_PORT PORTB
#define DAC_PIN  PB2

#define DAC_A 0
#define DAC_B 1<<15

#define DAC_ON 1<<12
#define DAC_OFF 0

#define DAC_GAIN 0
#define DAC_NOGAIN 1<<13

#define dac_start() DAC_PORT &= ~_BV(DAC_PIN)
#define dac_stop() DAC_PORT |= _BV(DAC_PIN)

void dac_set(uint16_t value);
