/*
 * main.c
 *
 * AUTHOR: Yagmur Yildiz
 *
 * DESCRIPTION: This code is an example how interrupt programming.
 * 				The LED (PB2) blink with 1s intervals.
 * 				When BUTTON (PB0) pressed, blink stop and LED turn on for 5s.
 * 				After blink continue.
 *
 * DATE: 30.11.2021
 */

#include "stm32g0xx.h"
#include "standart_function.h"

#define LEDDELAY    1600000


void EXTI0_1_IRQHandler (void)
{
	    if(pin_read('B', 0) == 1)
	    {
    		pin_write('B', 2, 'h');
    		delay(5*LEDDELAY);
	    }

	EXTI->RPR1 |= (1U << 0);
}


int main(void) {

	enable_clock('B');
	pin_mode('B', 2, 'o');			//LED
	pin_mode('B', 0, 'i');			//BUTTON
	GPIOB->PUPDR |= (2U << 2*0); 	// Pull-down mode

	EXTI->EXTICR[0] |= (1U << 0);
	EXTI->RTSR1     |= (1U << 0);
	EXTI->IMR1		|= (1U << 0);

	NVIC_SetPriority(EXTI0_1_IRQn, 0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);



    while(1) {

    	pin_write('B', 2, 'h');
    	delay(LEDDELAY);
    	pin_write('B', 2, 'l');
    	delay(LEDDELAY);
    }
    return 0;
}
