/*
 * lab4_prob2.c
 *
 * AUTHOR: Yagmur Yildiz
 *
 * DESCRIPTION: you will work on creating an accurate delay function using the SysTick exception.
 * 				Create a SysTick exception with 1 millisecond interrupt intervals. Then create a delay_ms(..)
 * 				function that will accurately wait for (blocking) a given number of milliseconds.
 *
 * DATE: 30.11.2021
 */

#include "stm32g0xx.h"
#include "standart_function.h"
#include "BSP.h"

#define LEDDELAY    1600000

uint32_t TIME = 0, STOP_TIME = 500000;

void delay_ms(uint32_t t)
{

	for(; t > 0; t--);
}

	void SysTick_Handler(void)
	{
		pin_write('B', 4, 'h');

		if(TIME == STOP_TIME)
		{
			pin_write('B', 4, 'l');
			delay_ms(TIME);
			SysTick->VAL = 0;
			TIME = 0;
		}

		TIME++;
	}

int main(void) {

	enable_clock('B');
	pin_mode('B', 4, 'o'); 	// LED at PB2

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

	pin_write('B', 4, 'l');

	while(1) {

		STOP_TIME = 500000;
/*
		pin_write('B', 4, 'h');
		delay(LEDDELAY);
		pin_write('B', 4, 'l');
		delay(LEDDELAY);
*/

    }
    return 0;
}
