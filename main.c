#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "spi.h"
#include "dac.h"
#include "sound.h"

#define pcm_start() TCCR1B |= _BV(CS10)
#define pcm_stop()  TCCR1B &= ~_BV(CS10); TCNT1 = 0

ISR(TIMER1_COMPA_vect) {
  static uint32_t pcm_sample_no;

  if(pcm_sample_no > pcm_length) {
    pcm_stop();
    pcm_sample_no = 0;

    dac_set(DAC_A | DAC_OFF);
  }

  dac_set(DAC_A | DAC_ON | DAC_NOGAIN | ((pgm_read_byte(&pcm_samples[pcm_sample_no++])) << 4));
}

int main(void) {
  spi_start();

  // Timer1 - sampler
  TCCR1B |= _BV(WGM12); // CTC with OCR1A
  OCR1A = (F_CPU / PCM_FREQ); // PCM_FREQ samples per second
  TIMSK1 |= _BV(OCIE1A); // Interrupt on CTC

  // DAC
  dac_stop();

  sei();

  while(1){
    pcm_start();
    _delay_ms((pcm_length / PCM_FREQ) + 1000);
  }
}
