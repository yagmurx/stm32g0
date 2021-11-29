/*
 * main.c
 *
 * author: Alican Bayındır
 *
 * Description: The code blinks the LED that connected to the PA_1 with the given interval.
 *
 * Problem 2 [20 pts]. Using a state machine blink the external LED at different intervals.
 * Assign each speed to a mode, and attach a button to cycle through the modes.
 * (Each button press will cycle through these modes.) You should do polling for the button press.
 *
 * Modes:
 * Mode 0 → No toggling, LED is off
 * Mode 1 → LED is toggling at roughly 2 second intervals
 * Mode 2 → LED is toggling at roughly 1 second intervals
 * Mode 3 → LED is toggling at roughly .5 second intervals
 * Mode 4 → LED is toggling at roughly .1 second intervals
 * Mode 5 → No toggling, LED is on
 *
 * Warnings:
 * Define an enum for your states, and cycle through them in each button press.
 * Depending on the state, define the delay.
 * Your flowchart should be detailed enough and should overlap with your implementation.
 * Make sure your code works when the optimization is defined as O2.
 *
 * Questions:
 * What is the difference in code size when the optimization is enabled / disabled?
 * How about the actual blinking speed of the LED? Is there any change? If so, what wouldbe the difference?
 * Compare the state machine approach to a regular super loop approach.
 * What are the advantages / disadvantages?
 * You need to give a pseudo-code for this comparison.
 *
 */

/*****************************************
 * * * * * * * LIBRARIES * * * * * * * * *
*****************************************/
#include "stm32g0xx.h"

/*****************************************
 * * * * * * * CONSTANTS * * * * * * * * *
*****************************************/
#define LEDDELAY    1600000

/*****************************************
 * * * * FUNCTION DEFINITIONS * * * * * *
*****************************************/
void delay(volatile uint32_t);
void led_blink(int32_t change);
void led_off();

/*****************************************
 * * * * * * * * ENUM * * * * * * * * * *
*****************************************/
enum states{
    mode_0,
	mode_1,
	mode_2,
	mode_3,
	mode_4,
	mode_5,
} mode;

/*****************************************
 * * * * * * * MAIN FUNC * * * * * * * * *
*****************************************/
int main(void) {
    /* Enable GPIOB clock */
    RCC -> IOPENR |= (2U);

    /* Setup PB_0 as output */
    GPIOB -> MODER &= ~(1U << 1);

    /* Setup PB_1 as input */
    GPIOB -> MODER &= ~(12U);

/*****************************************
 * * * * * * * VARIABLES * * * * * * * * *
*****************************************/
    mode = mode_0;
    int mode_counter = 0;

    while(1){
    	/* Checks if button pressed or not if pressed make button_pressed = 1*/
    	int button_pressed = ((GPIOB -> IDR & 2) >> 1 );
    	/* If button pressed then increase mode and counter +1*/
	    if (button_pressed == 1){
			mode ++;
			mode_counter++;
	    }

	    /* if mode is more than 6 then make mode = mode_0 if not then stay same*/
	    mode = (mode_counter >= 6) ?  mode_0 : mode_counter;
	    /* if mode_counter is more than 6 then reset it if not then stay same */
	    mode_counter = (mode_counter == 6) ? 0 : mode_counter;

	    /* taking action according to modes*/
	    switch(mode){
	    	case mode_0:
				led_off();
	    		break;
	    	case mode_1:
				led_blink(1600000);
	    		break;
	    	case mode_2:
				led_blink(0);
	    		break;
	    	case mode_3:
				led_blink(-800000);
	    		break;
	    	case mode_4:
				led_blink(-1300000);
	    		break;
	    	case mode_5:
				led_blink(-1600000);
	    		break;
	    }
    }

    return 0;
}

void led_blink(int32_t change){
	// There is a warning which will occur if change > LEDDELAY const
    delay(LEDDELAY + change);
    if(change >= -1500000)
    	GPIOB -> ODR ^= (1U);
    else
    /* To prevent toggling we should the code below when change = LEDDELAY */
    	GPIOB -> ODR = (1U);
}

void led_off(){
	GPIOB -> ODR =(0U);
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
