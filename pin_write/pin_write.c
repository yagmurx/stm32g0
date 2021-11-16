/*
 * pin_write.c
 *
 * author: Yagmur Yildiz
 *
 * Description: pin_write function used to write 0 or 1 to any OUTPUT Pin.
 *
 * NOTE: This file also included pin_mode function for adjust GPIO pin to OUTPUT and delay function.
 */

#include "stm32g0xx.h"

#define LEDDELAY    1600000
void delay(volatile uint32_t);
void pin_mode(char type, int gpio_pin, char reg_io);
void pin_write(char type, int gpio_pin, char status);

int main(void) {

	/*pin_write function example */
	pin_mode('A', 5, 'o');

    while(1) {
        pin_write('A', 5, 'h');
        delay(LEDDELAY);
		pin_write('A', 5, 'l');
		delay(LEDDELAY);
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

void pin_write(char type, int gpio_pin, char status)
{
	if (type == 'A')
		{
			/* Write HIGH to PAX */
			if(status == 'h')
				GPIOA->ODR |= (1U << gpio_pin);

			/* Write LOW to PAX */
			else if(status == 'l')
				GPIOA->ODR &= ~(3U << gpio_pin);
		}
	else if (type == 'B')
		{
			/* Write HIGH to PBX */
			if(status == 'h')
				GPIOB->ODR |= (1U << gpio_pin);

			/* Write LOW to PBX */
			else if(status == 'l')
				GPIOB->ODR &= ~(3U << gpio_pin);
		}

}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
