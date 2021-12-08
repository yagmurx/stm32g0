/*
 * main.c
 *
 * AUTHOR: Yagmur Yildiz
 *
 * DESCRIPTION:
 *
 *
 * NOTE: Keypad Connection: (D5 - D12)
 * 				R1->PB4 / R2->PB5 / R3->PB9 / R4->PA8
 * 				C1->PB8 / C2->PB2 / C3->PB0 / C4->PA9
 *
 * DATE: 07.12.2021
 */

#include "stm32g0xx.h"
#include "standart_function.h"

#define LEDDELAY    1600000

void setRowsKeypad (void);
void clearRowsKeypad (void);


void EXTI0_1_IRQHandler (void)		// Interrupt from PB0 (C3)
{
	clearRowsKeypad();

	pin_mode('A', 8, 'h');	//  HIGH R4
	if(pin_read('B', 0) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('A', 8, 'l');	//  LOW R4
	pin_mode('B', 9, 'h');	//  HIGH R3

	if(pin_read('B', 0) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('B', 9, 'l');	//  LOW R3
	pin_mode('B', 5, 'h');	//  HIGH R2

	if(pin_read('B', 0) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('B', 5, 'l');	//  LOW R2
	pin_mode('B', 4, 'h');	//  HIGH R1

	if(pin_read('B', 0) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('B', 4, 'l');	//  LOW R1

	EXTI->RPR1 |= (1U << 0);	//Clear interrupt flag
	setRowsKeypad();
}

void EXTI2_3_IRQHandler (void) // Interrupt from PB2
{
	clearRowsKeypad();

	pin_mode('A', 8, 'h');	//  HIGH R4
	if(pin_read('B', 2) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('A', 8, 'l');	//  LOW R4
	pin_mode('B', 9, 'h');	//  HIGH R3

	if(pin_read('B', 2) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('B', 9, 'l');	//  LOW R3
	pin_mode('B', 5, 'h');	//  HIGH R2

	if(pin_read('B', 2) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('B', 5, 'l');	//  LOW R2
	pin_mode('B', 4, 'h');	//  HIGH R1

	if(pin_read('B', 2) == 1)
	{
		pin_write('B', 6, 'h');
		delay(LEDDELAY);
	}

	pin_mode('B', 4, 'l');	//  LOW R1


	EXTI->RPR1 |= (1U << 2);	//Clear interrupt flag
	setRowsKeypad();
}

void EXTI4_15_IRQHandler (void) //Interrupt from PB8 or PA9
{
	if((EXTI->RPR1) & (1U << 8))
	{
		clearRowsKeypad();

		pin_mode('A', 8, 'h');	//  HIGH R4
		if(pin_read('B', 8) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('A', 8, 'l');	//  LOW R4
		pin_mode('B', 9, 'h');	//  HIGH R3

		if(pin_read('B', 8) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('B', 9, 'l');	//  LOW R3
		pin_mode('B', 5, 'h');	//  HIGH R2

		if(pin_read('B', 8) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('B', 5, 'l');	//  LOW R2
		pin_mode('B', 4, 'h');	//  HIGH R1

		if(pin_read('B', 8) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('B', 4, 'l');	//  LOW R1

		setRowsKeypad();
		EXTI->RPR1 |= (1U << 2);	//Clear interrupt flag
		setRowsKeypad();
	}

	if((EXTI->RPR1) & (1U << 9))
	{
		clearRowsKeypad();

		pin_mode('A', 8, 'h');	//  HIGH R4
		if(pin_read('A', 9) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('A', 8, 'l');	//  LOW R4
		pin_mode('B', 9, 'h');	//  HIGH R3

		if(pin_read('A', 9) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('B', 9, 'l');	//  LOW R3
		pin_mode('B', 5, 'h');	//  HIGH R2

		if(pin_read('A', 9) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('B', 5, 'l');	//  LOW R2
		pin_mode('B', 4, 'h');	//  HIGH R1

		if(pin_read('A', 9) == 1)
		{
			pin_write('B', 6, 'h');
			delay(LEDDELAY);
		}

		pin_mode('B', 4, 'l');	//  LOW R1

		setRowsKeypad();
		EXTI->RPR1 |= (1U << 2);	//Clear interrupt flag
		setRowsKeypad();
	}
}


int main(void) {

	enable_clock('A');
	enable_clock('B');

	// SET ROWS AS OUTPUT
	pin_mode('B', 4, 'o'); 			//R1
	pin_mode('B', 5, 'o');			//R2
	pin_mode('B', 9, 'o'); 			//R3
	pin_mode('A', 8, 'o');			//R4

	// SET COLUMNS AS INPUT
	pin_mode('B', 8, 'i'); 			//C1
	GPIOB->PUPDR |= (2U << 2*8); 	// Pull-down mode
	pin_mode('B', 2, 'i');			//C2
	GPIOB->PUPDR |= (2U << 2*2); 	// Pull-down mode
	pin_mode('B', 0, 'i'); 			//C3
	GPIOB->PUPDR |= (2U << 2*0); 	// Pull-down mode
	pin_mode('A', 9, 'i');			//C4
	GPIOA->PUPDR |= (2U << 2*9); 	// Pull-down mode

	//SET INTERRUPTS
	EXTI->EXTICR[2] |= (0U << 8*1);	// PA9
	EXTI->EXTICR[0] |= (1U << 8*0);	// PB0
	EXTI->EXTICR[0] |= (1U << 8*2);	// PB2
	EXTI->EXTICR[2] |= (1U << 8*0);	// PB8

	// RISING EDGE
	EXTI->RTSR1     |= (1U << 9);	// 9th Pin
	EXTI->RTSR1     |= (1U << 0);	// 0th Pin
	EXTI->RTSR1     |= (1U << 2);	// 2nd Pin
	EXTI->RTSR1     |= (1U << 8);	// 8th Pin

	// MASKS
	EXTI->IMR1		|= (1U << 9);
	EXTI->IMR1		|= (1U << 0);
	EXTI->IMR1		|= (1U << 2);
	EXTI->IMR1		|= (1U << 8);

	// NVIC
	NVIC_SetPriority(EXTI0_1_IRQn, 0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	NVIC_SetPriority(EXTI2_3_IRQn, 0);
	NVIC_EnableIRQ(EXTI2_3_IRQn);

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	//SET ALL ROWS HIGH
	pin_write('B', 4, 'h');		//R1
	pin_write('B', 5, 'h');		//R2
	pin_write('B', 9, 'h');		//R3
	pin_write('A', 8, 'h');		//R4

	//CONTROL LED
	pin_mode('B', 6, 'o');


    while(1) {
    	/*
    	 * wait here
    	 */
    }
    return 0;
}

void clearRowsKeypad (void)
{
	pin_write('B', 4, 'l');		//R1
	pin_write('B', 5, 'l');		//R2
	pin_write('B', 9, 'l');		//R3
	pin_write('A', 8, 'l');		//R4
}

void setRowsKeypad (void)
{
	pin_write('B', 4, 'h');		//R1
	pin_write('B', 5, 'h');		//R2
	pin_write('B', 9, 'h');		//R3
	pin_write('A', 8, 'h');		//R4
}
