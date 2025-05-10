#include "adc.h"
#include "uart.h"
#include "print.h"

int sensor_value;
int main(void)
{
    
    /*Initialize debug UART*/
    uart_init();

    /*Initialize ADC*/
    pal_adc_init();
    /*Start conversion*/
    start_conversion();

    
    while(1)
    {
        int sensor_value = adc_read();
        printf_uart("Sensor Value: %d\r\n", sensor_value);
    }
}


