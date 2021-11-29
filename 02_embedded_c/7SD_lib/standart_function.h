/*
 * standart_functions.c
 *
 * author: Yagmur Yildiz
 *
 * Description: this file includes;
 *
 * 		pin_mode function: Used for adjust any GPIOX_MODER as INPUT or OUTPUT.
 * 							pin_mode(char type, int gpio_pin, char reg_io);
 * 							EX: pin_mode('A', 5, 'o');
 * 							EX: pin_mode('B', 4, 'i');
 *
 * 		pin_write function: Used for control OUTPUT SIGNAL of a GPIO pin.
 * 							pin_write(char type, int gpio_pin, char status)
 * 							EX: pin_write('A', 5, 'h');
 * 							EX: pin_write('B', 4, 'l');
 *
 * 		delay function: delay program
 * 							delay(voltile uint32_t)
 * 							EX: delay(1600000)
 *
 *  DATE: 16.11.2021
 */

#include "stm32g0xx.h"

/* pin_mode function */
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

/* pin_write function */
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

/* delay function */
void delay(volatile uint32_t s)
{
    for(; s>0; s--);
}
