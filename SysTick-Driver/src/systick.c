#include "systick.h"

#define CTRL_ENABLE     (1U<<0)
#define CTRL_CLCKSRC    (1U<<2)
#define CTRL_COUNTFLAG  (1U<<16)  

#define ONE_MSEC_LOAD 16000

void systick_msec_delay(uint32_t delay)
{
    /*Load # of clock cycles per millisecond*/
    SysTick->LOAD = ONE_MSEC_LOAD - 1;

    /*Clear SysTick current value*/
    SysTick->VAL = 0;

    /*Select Internal clock source*/
    SysTick->CTRL = CTRL_CLCKSRC;

    /*Enable SysTick*/
    SysTick->CTRL |= CTRL_ENABLE;

    /*This loop runs for the specified delay duration. Inside each iteration, it waits for the COUNTFLAG bit to be set, which indicates the timer has counted down to zero.*/
    for (int i = 0; i < delay; i++)
    {
        while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
    }

    /*Disable SysTick*/
    SysTick->CTRL = 0;
}