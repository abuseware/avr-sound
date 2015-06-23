#pragma once
#include <stdint.h>
#include <avr/io.h>

#define SPI_DDR        DDRB
#define SPI_PIN_SCK    PB5
#define SPI_PIN_MISO   PB4
#define SPI_PIN_MOSI   PB3
#define SPI_PIN_CS     PB2

void spi_start(void);
void spi_stop(void);
void spi_send(const uint8_t data);
uint8_t spi_receive(void);
