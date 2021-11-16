/*
 * pin_mode.c
 *
 * author: Yagmur Yildiz
 *
 * Description: pin_mode function is used for adjust any GPIO pin as an INPUT or an OUTPUT
 */

#include "stm32g0xx.h"

void pin_mode(char type, int gpio_pin, char reg_io);

int main(void) {

	/*pin_mode function example */

	pin_mode('A', 5, 'o');



    while(1) {
        /* Turn on LED */
        GPIOA->ODR |= (1U << 5);
    }
    return 0;
}

void pin_mode(char type, int gpio_pin, char reg_io)
{
	if (type == 'A')
	{
	    /* Enable GPIOA clock */
	    RCC->IOPENR |= 1U;

	    if(reg_io == 'o')
	    {
		    /* Setup PAX as output */
		    GPIOA->MODER &= ~(3U << 2*gpio_pin);
		    GPIOA->MODER |= (1U << 2*gpio_pin);
	    }

	    else if(reg_io == 'i')
	    {
		    /* Setup PAX as input */
		    GPIOA->MODER &= ~(3U << 2*gpio_pin);
	    }

	}
	else if (type == 'B')
	{
	    /* Enable GPIOB clock */
	    RCC->IOPENR |= (1U << 1);

	    if(reg_io == 'o')
	    {
		    /* Setup PBX as output */
		    GPIOB->MODER &= ~(3U << 2*gpio_pin);
		    GPIOB->MODER |= (1U << 2*gpio_pin);
	    }

	    else if(reg_io == 'i')
	    {
		    /* Setup PBX as input */
		    GPIOB->MODER &= ~(3U << 2*gpio_pin);
	    }

	}
}

