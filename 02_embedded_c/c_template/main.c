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

	set_on_board_led();
	set_on_board_button();

	while(1) {
		if(read_on_board_button() == 1)
			on_board_led(1);
		else if (read_on_board_button() == 0)
			on_board_led(0);

    }
    return 0;
}
