/*
 * blink.c
 *
 * Author: Yagmur Yildiz
 *
 * DESCRIPTION: Blink on-board LED at roughly 1 second intervals.
 *
 */

#include "stm32g0xx.h"

#define LEDDELAY    1600000

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

int main(void) {
	RCC->IOPENR |= (1U << 2); //ENABLE GPIOC Clock
	RCC->IOPENR |= (1U << 0); //ENABLE GPIOA Clock

    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);
    GPIOA->MODER &= ~(3U << 2*4);
    GPIOA->MODER |= (1U << 2*4);

    while(1) {
		GPIOC->ODR ^= (1U << 6); // TOGGLE LED
		GPIOA->ODR ^= (1U << 4); // TOGGLE LED
		delay(LEDDELAY);

    }

    return 0;
}
