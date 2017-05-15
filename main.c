#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#define BAUD 9600
#include <util/setbaud.h>

#include "dac.h"
#include "sound.h"
#include "spi.h"
//#include "wifi.h"

#define pcm_start() TCCR1B |= _BV(CS10)
#define pcm_stop()                                                             \
  TCCR1B &= ~_BV(CS10);                                                        \
  TCNT1 = 0

volatile uint8_t action = 1;

ISR(TIMER1_COMPA_vect) {
  static uint32_t pcm_sample_no;
  uint8_t pcm_sample;

  if (pcm_sample_no == 0) {
    dac_start();
  } else if (pcm_sample_no > pcm_length) {
    pcm_stop();
    pcm_sample_no = 0;

    dac_set(DAC_A | DAC_OFF);
    dac_set(DAC_B | DAC_OFF);
    dac_stop();
  }

  pcm_sample = pgm_read_byte(&pcm_samples[pcm_sample_no++]);
  dac_set(DAC_A | DAC_ON | DAC_NOGAIN | (pcm_sample << 4));
  dac_set(DAC_B | DAC_ON | DAC_NOGAIN | (pcm_sample << 4));
}

ISR(USART_RX_vect) {
  switch (UDR0) {
  case '0':
  case 0:
    action = 0;
    UDR0 = '#';
    break;
  case '1':
  case 1:
    action = 1;
    UDR0 = '>';
    break;
  }
}

int main(void) {

  // Set USART parameters (from setbaud.h)
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif

  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);

  spi_start();

  // Timer1 - sampler
  TCCR1B |= _BV(WGM12);       // CTC with OCR1A
  OCR1A = (F_CPU / PCM_FREQ); // PCM_FREQ samples per second
  TIMSK1 |= _BV(OCIE1A);      // Interrupt on CTC

  // DAC
  dac_stop();

  sei();

  while (1) {
    if (action) {
      pcm_start();
      _delay_ms((pcm_length / PCM_FREQ) + 250);
    }
  }
}
