/*
 * BSP.h
 *
 * AUTHOR: Yagmur Yildiz
 *
 * DESCRIPTION: This header file is a Board Support Package (BSP)
 *
 * 				set_on_board_led(): Configure on-board LED at PC6.
 * 								void set_on_board_led()
 *
 * 				on_board_led function: Turn on / turn off and toggle on-board LED at PC6.
 * 								void on_board_led(volatile uint32_t LEDDELAY)
 * 								EX: on_board_led(0) ===== Turn Off LED
 * 								EX: on_board_led(1) ===== Turn ON LED
 * 								EX: on_board_led(LEDDELAY) ===== Toggle LED
 *
 *				set_on_board_button() : Configure on-board Button as INPUT at PF2.
 * 										void set_on_board_button(void)
 *
 *				read_on_board_button() : Read digital signal from on-board Button. RETURNS 0 or 1.
 *										int read_on_board_button(void)
 *  DATE: 16.11.2021
 *  LAST UPDATE: 30.11.2021
 */

#include "stm32g0xx.h"

// Configure on-board LED at PC6.
void set_on_board_led()
{
	RCC->IOPENR |= (1U << 2); //ENABLE GPIOC Clock

    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);
}

// Turn on / turn off and toggle on-board LED at PC6.
void on_board_led(volatile uint32_t LEDDELAY)
{
	if (LEDDELAY == 0)
		GPIOC->ODR &= ~(3U << 6);

	else if(LEDDELAY == 1)
		GPIOC->ODR |= (1U << 6);

	else
	{
		GPIOC->ODR |= (1U << 6); // HIGH PC6
		delay(LEDDELAY);
		GPIOC->ODR &= ~(3U << 6); // LOW PC6
		delay(LEDDELAY);
	}
}

// Configure on-board Button as INPUT at PF2.
void set_on_board_button(void)
{
	RCC->IOPENR |= (1U << 5); //ENABLE GPIOF Clock
	GPIOF->MODER &= ~(3U << 2*2); // INPUT
	GPIOF->PUPDR |= (2U << 2); // Pull-down mode
}

// Read digital signal from on-board Button
int read_on_board_button(void)
{
	int status;
	status = ((GPIOF->IDR >> 2) & 1);

	return status;
}
