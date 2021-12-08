/*
 * main.c
 *
 * author: Yagmur Yildiz
 *
 * DATE: 16.11.2021
 * Last Update: 30.11.2021
 */

#include "stm32g0xx.h"
#include "standart_function.h"
#include "BSP.h"

#define LEDDELAY    1600000

int main(void) {

	enable_clock('A');
	pin_mode('A', 4, 'o');

	while(1) {
		pin_write('A', 4, 'h');
		delay(LEDDELAY);
		pin_write('A', 4, 'l');
		delay(LEDDELAY);
    }
    return 0;
}
