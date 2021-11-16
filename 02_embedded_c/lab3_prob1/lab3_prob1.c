/*
 * lab3_prob1.c
 *
 * Author: Yagmur Yildiz
 *
 * PROBLEM 1: Write a program to blink an external LED at roughly 1 second intervals.
 *
 * NOTE: the external LED connected PB4 (D12).
 */

#include "stm32g0xx.h"

#define LEDDELAY    1600000

void delay(volatile uint32_t);

int main(void) {

    // Enable GPIOB clock
    RCC->IOPENR |= (1U << 1);

    // Setup PB4 as output
    GPIOB->MODER &= ~(3U << 2*4);
    GPIOB->MODER |= (1U << 2*4);

    GPIOB->ODR |= (1U << 4);		// Turn on LED

    while(1) {
        delay(LEDDELAY);
        GPIOB->ODR ^= (1U << 4);	// Toggle LED
    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
