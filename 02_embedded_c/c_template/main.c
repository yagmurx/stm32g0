/*
 * main.c
 *
 * author: Yagmur Yildiz
 *
 * DATE: 16.11.2021
 */

#include "stm32g0xx.h"
#include "standart_function.h"

#define LEDDELAY    1600000
void delay(volatile uint32_t);
void pin_mode(char type, int gpio_pin, char reg_io);
void pin_write(char type, int gpio_pin, char status);

int main(void) {

	/*pin_write function example */
	pin_mode('A', 7, 'o');

    while(1) {
        pin_write('A', 7, 'h');
        delay(LEDDELAY);
		pin_write('A', 7, 'l');
		delay(LEDDELAY);
    }
    return 0;
}
