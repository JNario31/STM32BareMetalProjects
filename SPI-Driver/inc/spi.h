#ifndef SPI_H__
#define SPI_H__
#include "stm32f4xx.h"
#include "stm32f446xx.h"

void spi_gpio_init(void);
void spi1_config(void);
void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_receive(uint8_t *data, uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif