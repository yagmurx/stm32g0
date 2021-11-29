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

    while(1) {
    	set_on_board_led();

    	on_board_led(1);
    	delay(LEDDELAY);
    	delay(LEDDELAY);
    	on_board_led(0);
    	delay(LEDDELAY);
    	delay(LEDDELAY);

    	for(int i=0; i < 5; i++)
    		on_board_led(LEDDELAY);
    }
    return 0;
}
