#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"
#include "uart.h"
#include "gpio_exti.h"
#include "gpio.h"




//Variables for storing accelerometer data
int16_t accel_x, accel_y, accel_z;
double accel_x_g, accel_y_g, accel_z_g;

extern uint8_t data_buffer[6];

int main(void)
{

	uart_init();

	led_init();

	pc13_exti_init();

    while (1)
    {


    }

    return 0;
}

static void exti_callback(void)
{
	printf("Button pressed...\n");
	led_toggle();
}


void EXTI15_10_IRQHandler(void)
{
	/*If Pending bit is set (if interrupt occurred*/
	if((EXTI->PR & LINE13) != 0)
	{
		EXTI->PR |= LINE13;

		/*Interrupt Routine*/
		exti_callback();
	}

}
