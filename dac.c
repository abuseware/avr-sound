#include "dac.h"

void dac_set(uint16_t value) {
  dac_start();
  spi_send((value >> 8) & 0xff);
  spi_send(value & 0xff);
  dac_stop();
}
