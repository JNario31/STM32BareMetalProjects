#include "gpio.h"
#include "tim.h"

int main(void)
{
    /*Initialize LED*/
    led_init();

    /*Initialize Timer*/
    tim2_1hz_init();

    while(1){
        led_toggle();
        /*Wait for UIF */
        while(!(TIM2->SR & SR_UIF)){} //While status register is and UIF is low
        /*Clear UIF*/
        TIM2->SR &=~SR_UIF;
    }
}