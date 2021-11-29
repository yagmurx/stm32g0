/*
 * 7-segment-display.c
 *
 * author: Yagmur Yildiz
 *
 * Description: this file includes functions for 7-segment-display.
 * 				pins[] 			<- pins that connected A, B, C, D, E, F, G.
 * 				decimal_pins[]	<- pins that connected D1, D2, D3, D4 common pins.
 *				Because of STM32G0 has pins A[0:12] and B[0:12], pins[] use A pins, decimal_pins[] use B pins.
 *
 * 		set_7SD function: Use for set 7SD OUTPUT pins.
 * 						void set_7SD(int pins[])
 *
 * 		7SD_ON function: Use for turn on numbers. x is the INPUT number as 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
 *						void ON_7SD(int x, int pins[])
 *
 *		OFF_7SD function: Use for turn off numbers.
 *						void OFF_7SD(int pins[])
 *
 *		set_4x_7SD function: I used 4x 7 segment display. This function sets common pins.
 *						void set_4x_7SD(int decimal_pins[])
 *
 *		selected_4x_7SD function: I used 4x 7 segment display. So for activating segments, this function used.
 *						void select_4x_7SD(int digit, int decimal_pins[])
 *
 *		print_7SD function: Print numbers 0 to 99.
 *						void print_7SD (int x, int pins[], int decimal_pins[])
 *
 *  DATE: 29.11.2021
 */


void set_7SD(int pins[])
{
	pin_mode('A', pins[0], 'o');		//PAX A
	pin_mode('A', pins[1], 'o');		//PAX B
	pin_mode('A', pins[2], 'o');		//PAX C
	pin_mode('A', pins[3], 'o');		//PAX D
	pin_mode('A', pins[4], 'o');		//PAX E
	pin_mode('A', pins[5], 'o');		//PAX F
	pin_mode('A', pins[6], 'o');		//PAX G
}

void OFF_7SD(int pins[])
{
	pin_write('A', pins[0], 'l');		// PAX A
	pin_write('A', pins[1], 'l');		// PAX B
	pin_write('A', pins[2], 'l');		// PAX C
	pin_write('A', pins[3], 'l');		// PAX D
	pin_write('A', pins[4], 'l');		// PAX E
	pin_write('A', pins[5], 'l');		// PAX F
	pin_write('A', pins[6], 'l');		// PAX G
}

void ON_7SD(int x, int pins[]) {

		OFF_7SD(pins);

	switch ( x )
	{
		case 0:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'h');		//PAX D
			pin_write('A', pins[4], 'h');		//PAX E
			pin_write('A', pins[5], 'h');		//PAX F
			pin_write('A', pins[6], 'l');		//PAX G
			break;

		case 1:
			pin_write('A', pins[0], 'l');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'l');		//PAX D
			pin_write('A', pins[4], 'l');		//PAX E
			pin_write('A', pins[5], 'l');		//PAX F
			pin_write('A', pins[6], 'l');		//PAX G
			break;

		case 2:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'l');		//PAX C
			pin_write('A', pins[3], 'h');		//PAX D
			pin_write('A', pins[4], 'h');		//PAX E
			pin_write('A', pins[5], 'l');		//PAX F
			pin_write('A', pins[6], 'h');		//PAX G
			break;

		case 3:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'h');		//PAX D
			pin_write('A', pins[4], 'l');		//PAX E
			pin_write('A', pins[5], 'l');		//PAX F
			pin_write('A', pins[6], 'h');		//PAX G
			break;

		case 4:
			pin_write('A', pins[0], 'l');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'l');		//PAX D
			pin_write('A', pins[4], 'l');		//PAX E
			pin_write('A', pins[5], 'h');		//PAX F
			pin_write('A', pins[6], 'h');		//PAX G
			break;

		case 5:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'l');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'h');		//PAX D
			pin_write('A', pins[4], 'l');		//PAX E
			pin_write('A', pins[5], 'h');		//PAX F
			pin_write('A', pins[6], 'h');		//PAX G
			break;

		case 6:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'l');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'h');		//PAX D
			pin_write('A', pins[4], 'h');		//PAX E
			pin_write('A', pins[5], 'h');		//PAX F
			pin_write('A', pins[6], 'h');		//PAX G
			break;

		case 7:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'l');		//PAX D
			pin_write('A', pins[4], 'l');		//PAX E
			pin_write('A', pins[5], 'l');		//PAX F
			pin_write('A', pins[6], 'l');		//PAX G
			break;

		case 8:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'h');		//PAX D
			pin_write('A', pins[4], 'h');		//PAX E
			pin_write('A', pins[5], 'h');		//PAX F
			pin_write('A', pins[6], 'h');		//PAX G
			break;

		case 9:
			pin_write('A', pins[0], 'h');		//PAX A
			pin_write('A', pins[1], 'h');		//PAX B
			pin_write('A', pins[2], 'h');		//PAX C
			pin_write('A', pins[3], 'h');		//PAX D
			pin_write('A', pins[4], 'l');		//PAX E
			pin_write('A', pins[5], 'h');		//PAX F
			pin_write('A', pins[6], 'h');		//PAX G
			break;
	}
}

void set_4x_7SD(int decimal_pins[])
{
	pin_mode('B', decimal_pins[0], 'o');		//PBX D1
	pin_mode('B', decimal_pins[1], 'o');		//PBX D2
	pin_mode('B', decimal_pins[2], 'o');		//PBX D3
	pin_mode('B', decimal_pins[3], 'o');		//PBX D4
}

void select_4x_7SD(int digit, int decimal_pins[])
{
	switch (digit)
	{
		case 1:
			pin_write('B', decimal_pins[0], 'h');
			pin_write('B', decimal_pins[1], 'l');
			pin_write('B', decimal_pins[2], 'l');
			pin_write('B', decimal_pins[3], 'l');
			break;

		case 2:
			pin_write('B', decimal_pins[0], 'l');
			pin_write('B', decimal_pins[1], 'h');
			pin_write('B', decimal_pins[2], 'l');
			pin_write('B', decimal_pins[3], 'l');
			break;

		case 3:
			pin_write('B', decimal_pins[0], 'l');
			pin_write('B', decimal_pins[1], 'l');
			pin_write('B', decimal_pins[2], 'h');
			pin_write('B', decimal_pins[3], 'l');
			break;

		case 4:
			pin_write('B', decimal_pins[0], 'l');
			pin_write('B', decimal_pins[1], 'l');
			pin_write('B', decimal_pins[2], 'h');
			pin_write('B', decimal_pins[3], 'l');
			break;
	}

}

void print_7SD (int x, int pins[], int decimal_pins[])
{

	if(x >= 0 && x < 10)
	{
		select_4x_7SD(1, decimal_pins);
		ON_7SD(x, pins);
		delay(20000);
	}

	else if(x >= 10 && x < 100)
	{
		int digit[2] = {0};
		digit[1] = x % 10; // ones digit
		digit[0] = x / 10; // teens digit

		select_4x_7SD(1, decimal_pins);
		ON_7SD(digit[0], pins);
		delay(10000);

		select_4x_7SD(2, decimal_pins);
		ON_7SD(digit[1], pins);
		delay(10000);
	}
}
