#include "spi.h"

#define SPI1EN       (1U<<12)
#define GPIOAEN     (1U<<0)
#define SR_TXE      (1U<<1)
#define SR_RXNE     (1U<<0)
#define SR_BSY      (1U<<7)

void spi_gpio_init(void)
{

    /*Enable Clock access to GPIOA*/
    RCC->AHB1ENR |= GPIOAEN;

    /*Set PA5, PA6, PA7 to Alternative function 10*/

    /*PA5 SPI1_SCLK*/
    GPIOA->MODER &=~(1U<<10);
    GPIOA->MODER |=(1U<<11);

    /*PA6 SPI1_MISO*/
    GPIOA->MODER &=~(1U<<12);
    GPIOA->MODER |=(1U<<13);

    /*PA7 SPI1_MOSI*/
    GPIOA->MODER &=~(1U<<14);
    GPIOA->MODER |=(1U<<15);

    /*PA9 as Output pin (Could be any pin) 01*/
    GPIOA->MODER |= (1U<<18);
    GPIOA->MODER &=~(1U<<19);


    /*Set PA5, PA6, PA7 alternative function type to SPI1 (AF5 - 0101)*/

    /*PA5*/
    GPIOA->AFR[0] |= (1U<<20);
    GPIOA->AFR[0] &= ~(1U<<21);
    GPIOA->AFR[0] |= (1U<<22);
    GPIOA->AFR[0] &= ~(1U<<23);

    /*PA6*/
    GPIOA->AFR[0] |= (1U<<24);
    GPIOA->AFR[0] &= ~(1U<<25);
    GPIOA->AFR[0] |= (1U<<26);
    GPIOA->AFR[0] &= ~(1U<<27);

    /*PA7*/
    GPIOA->AFR[0] |= (1U<<28);
    GPIOA->AFR[0] &= ~(1U<<29);
    GPIOA->AFR[0] |= (1U<<30);
    GPIOA->AFR[0] &= ~(1U<<31);
    
}

void spi1_config(void)
{
    /*Enable clock access to SPI1 module */
    RCC->APB2ENR |= SPI1EN;

    /*Set Baudrate to fpCLK/4 (001)*/
    SPI1->CR1 |= (1U<<3);
    SPI1->CR1 &= ~(1U<<4);
    SPI1->CR1 &= ~(1U<<5);

    /*Set clock phase and polarity*/
    SPI1->CR1 |= (1U<<0);   //Phase: Second clock transition is first data capture
    SPI1->CR1 |= (1U<<1);   //Polarity: When idle clock is high

    /*Enable full duplex*/
    SPI1->CR1 &= ~(1U<<10);

    /*Frame format, MSB first*/
    SPI1->CR1 &= ~(1U<<7);

    /*Set mode to master*/
    SPI1->CR1 |= (1U<<2);

    /*Set 8 bit data mode*/
    SPI1->CR1 &= ~(1U<<11);

    /*Select software slave management, SSM and SSI = 1*/
    SPI1->CR1 |= (1U<<8);
    SPI1->CR1 |= (1U<<9);

    /*Enable SPI Module*/
    SPI1->CR1 |= (1U<<6);

}

void spi1_transmit(uint8_t *data, uint32_t size)
{
    uint32_t i=0;
    uint8_t temp;
    while (i < size)
    {
        /*Wait until TXE is set*/
        while(!(SPI1->SR & (SR_TXE))){}

        /*Write data to DR*/
        SPI1->DR = data[i];
        i++;
    }

    /*Wait until TXE is set*/
    while(!(SPI1->SR & (SR_TXE))){}

    /*Wait until busy flag is reset*/
    while((SPI1->SR & (SR_BSY))){}

    /*After the master transmits data through the SPI Data Register, the same register captures the data received from the
    slave. To ensure incoming data is properly processed, we read the Data Register, even if we don’t need
    the value. This read operation automatically clears the OVR flag.*/
    temp = SPI1->DR;
    temp = SPI1->SR;

}

void spi1_receive(uint8_t *data, uint32_t size)
{
    while(size)
    {
        /*Send dummy data*/
        SPI1->DR = 0;
        /*Wait for RXNE to be set*/
        while(!(SPI1->SR & (SR_RXNE))){}
        /*Read data from data register*/
        *data++ = (SPI1->DR);
        size--;
    }
}

/*Active Low - Enable or disable slave device*/
void cs_enable(void)
{
    GPIOA->ODR &= ~(1U<<9);
}

void cs_disable(void)
{
    GPIOA->ODR |= (1U<<9);
}