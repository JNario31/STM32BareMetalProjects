#include "gpio_exti.h"

#define GPIOCEN		(1U<<2)
#define SYSCFGEN	(1U<<14)

void pc13_exti_init(void){

	/*Disable Global Interrupts*/
	__disable_irq();

	/*Enable Clock for port C*/
	RCC->AHB1ENR |= GPIOCEN;

	/*Set PC13 as Input*/
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	/*Enable clock for system configuration to configure EXTI lines*/
	RCC->APB2ENR |= SYSCFGEN;

	/*Select Port C for EXTI13 0010*/
	SYSCFG->EXTICR[3] |= (1U<<5);

	/*Unmask EXTI13*/
	EXTI->IMR |= (1U<<13);

	/*Falling Edge Trigger*/
	EXTI->FTSR |= (1U<<13);

	NVIC_EnableIRQ(EXTI15_10_IRQn);

	__enable_irq();

}
