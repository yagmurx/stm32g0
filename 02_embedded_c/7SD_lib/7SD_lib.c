/*
 * 7SD_lib.c
 *
 * AUTHOR: Yagmur Yildiz
 *
 * DESCRIPTION:  4x 7-segment-display library for STM32G0.
 * 				This file includes an example, count forward 0 to 99.
 *
 * 				PIN OUTS:
 * 				A->PA0, B->PA1, C->PA4, D->PA5, E->PA12, F->PA11, G->PA6
 * 				D1->PB6, D2->PB7
 *
 * DATE: 29.11.2021
 */

#include "stm32g0xx.h"
#include "standart_function.h"
#include "7-segment-display.h"

#define LEDDELAY    1600000 // 1s

int main(void)
{
	int pins[7] = {0, 1, 4, 5, 12, 11, 6}; // 7SD pins out
	int decimal_pins[4] = {6, 7, 0,  0};   // 7SD, decimal pins out

	set_7SD(pins);						// Set 7SD pins as OUTPUT
	set_4x_7SD(decimal_pins);			// Set common cathode as OUTPUT
	OFF_7SD(pins);						//Clear display


    while(1)
    {

    	for (int i=0; i < 100; i++)
    	{
    		int led_delay = LEDDELAY / 16000;
    		for(int j=0; j < led_delay; j++)
    			print_7SD(i, pins, decimal_pins);
    	}
    }
    return 0;
}
