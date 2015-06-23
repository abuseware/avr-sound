#include "spi.h"

void spi_start(void) {
  SPI_DDR |= _BV(SPI_PIN_SCK) | _BV(SPI_PIN_MOSI) | _BV(SPI_PIN_CS);

  SPCR |= _BV(SPE) | _BV(MSTR);
  SPSR |= _BV(SPI2X);
}

void spi_stop(void) {
  SPCR &= _BV(SPE) | _BV(MSTR);

  SPI_DDR &= _BV(SPI_PIN_SCK) | _BV(SPI_PIN_MOSI) | _BV(SPI_PIN_CS);
}

void spi_send(const uint8_t data) {
  SPDR = data;
  loop_until_bit_is_set(SPSR, SPIF);
}

uint8_t spi_receive(void) {
  return SPDR;
}
