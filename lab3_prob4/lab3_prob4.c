/*
 * lab3_prob4.c
 *
 * Author: Yagmur Yildiz
 *
 * PROBLEM 4: Connect the keypad to the microcontroller, and using external interrupts detect button presses.
 * 			  Use an SSD to display the pressed button. Your main loop should only be used to display the SSDs.
 * 			  You should create a function that will display the given number on SSDs.
 *			  - Each time button is pressed, the number should slide in from the right of the SSD.
 *			  - When there are 4 digits already, the next number should erase the oldest number.
 */

#include "stm32g0xx.h"

#define LEDDELAY    1600000

void delay(volatile uint32_t);

int main(void) {

    /* Enable GPIOC clock */
    RCC->IOPENR |= (1U << 2);

    /* Setup PC6 as output */
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);

    /* Turn on LED */
    GPIOC->ODR |= (1U << 6);

    while(1) {
        delay(LEDDELAY);
        /* Toggle LED */
        GPIOC->ODR ^= (1U << 6);
    }

    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
