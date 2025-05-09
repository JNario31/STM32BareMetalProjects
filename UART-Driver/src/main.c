#include "uart.h"
#include "tim.h"
#include "print.h"

int main(void) {
    uart_init();
    tim2_1hz_init();
    const char msg[] = "Hello from STM32...\r\n";
    while (1) {

        puts_uart("Hello from STM32...");
       
        while(!(TIM2->SR & SR_UIF)){} 
        TIM2->SR &=~SR_UIF;
    }
}

