#include "adc.h"

#define GPIOAEN         (1U<<0)
#define ADC1EN         (1U<<8)
#define ADC_CH1         (1U<<0)
#define ADC_SEQ_LEN1    0x00
#define CR2_ADCON       (1U<<0)
#define CR2_CONT        (1U<<1)
#define CR2_SWSTART     (1U<<30)
#define SR_EOC          (1U<<1)

void pal_adc_init(void)
{
    /***Configure ADC GPIO Pin***/

    /*Enable Clock Access*/
    RCC->AHB1ENR |= GPIOAEN;

    /*Set PA1 mode to analog mode*/
    GPIOA->MODER |= (1U<<2);
    GPIOA->MODER |= (1U<<3);

    /***Configure ADC Module ***/

    /*Enable Clock Access*/
    RCC->APB2ENR |= ADC1EN;

    /*Set conversion sequence start*/
    ADC1->SQR3 = ADC_CH1;

    /*Set conversion sequence length*/
    ADC1->SQR1 = ADC_SEQ_LEN1;

    /*Enable ADC Module*/
    ADC1->CR2 |= CR2_ADCON;

}

void start_conversion(void)
{
    /*Enable continuous conversion*/
    ADC1->CR2 |= CR2_CONT;

    /*Start ADC conversion*/
    ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
    /*Wait for conversion to be complete*/
    while(!(ADC1->SR & SR_EOC)){}

    /*Reac converted value*/
    return (ADC1->DR);
}