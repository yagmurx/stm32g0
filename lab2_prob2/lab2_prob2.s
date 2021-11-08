/*
 * lab2_prob2.s
 *
 * author: Yagmur Yildiz
 *
 * PROBLEM 2: Write a decimal counter using Seven Segment Displays
 *				- Connect 1 x Seven Segment Displays, 2 x buttons, and 1 status LED
 *				- One button should cycle through each project member's ID on the SSD
 *				- Second button should start the automatic counting down from that number down to 0.
 *				- Upon reaching 0, it should stay there and wait there for any button press.
 *					- If the cycle button is pressed, it should display the next ID.
 *					- If the counter button is pressed, it should count down from the original ID again.
 *				- Status LED should be ON when the countdown operation is in progress. OFF otherwise.
 * DATE: 08.11.2021

 * NOTE: I used PA/4/5/6/7/8 and PB/4/5/9 as OUTPUT, PB/0/2 as INPUT.
 */


.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb


/* make linker see this */
.global Reset_Handler

/* get these from linker script */
.word _sdata
.word _edata
.word _sbss
.word _ebss


/* define peripheral addresses from RM0444 page 57, Tables 3-4 */
.equ RCC_BASE,         (0x40021000)          // RCC base address
.equ RCC_IOPENR,       (RCC_BASE   + (0x34)) // RCC IOPENR register offset

.equ GPIOA_BASE,       (0x50000000)          // GPIOA base address
.equ GPIOA_MODER,      (GPIOA_BASE + (0x00)) // GPIOA MODER offset
.equ GPIOA_ODR,        (GPIOA_BASE + (0x14)) // GPIOA ODR  offset
.equ GPIOA_IDR, 	   (GPIOA_BASE + (0x10)) // GPIOA IDR offset

.equ GPIOB_BASE,       (0x50000400)          // GPIOB base address
.equ GPIOB_MODER,      (GPIOB_BASE + (0x00)) // GPIOB MODER offset
.equ GPIOB_ODR,        (GPIOB_BASE + (0x14)) // GPIOB ODR  offset
.equ GPIOB_IDR, 	   (GPIOB_BASE + (0x10)) // GPIOB IDR offset


/* vector table, +1 thumb mode */
.section .vectors
vector_table:
	.word _estack             /*     Stack pointer */
	.word Reset_Handler +1    /*     Reset handler */
	.word Default_Handler +1  /*       NMI handler */
	.word Default_Handler +1  /* HardFault handler */
	/* add rest of them here if needed */


/* reset handler */
.section .text
Reset_Handler:
	/* set stack pointer */
	ldr r0, =_estack
	mov sp, r0

	/* initialize data and bss 
	 * not necessary for rom only code 
	 * */
	bl init_data
	/* call main */
	bl main
	/* trap if returned */
	b .


/* initialize data and bss sections */
.section .text
init_data:

	/* copy rom to ram */
	ldr r0, =_sdata
	ldr r1, =_edata
	ldr r2, =_sidata
	movs r3, #0
	b LoopCopyDataInit

	CopyDataInit:
		ldr r4, [r2, r3]
		str r4, [r0, r3]
		adds r3, r3, #4

	LoopCopyDataInit:
		adds r4, r0, r3
		cmp r4, r1
		bcc CopyDataInit

	/* zero bss */
	ldr r2, =_sbss
	ldr r4, =_ebss
	movs r3, #0
	b LoopFillZerobss

	FillZerobss:
		str  r3, [r2]
		adds r2, r2, #4

	LoopFillZerobss:
		cmp r2, r4
		bcc FillZerobss

	bx lr


/* default handler */
.section .text
Default_Handler:
	b Default_Handler


/* main function */
.section .text
main:
	/* enable GPIO/A/B clock, 11 to bits[0:1] on IOPENR */
	ldr r6, =RCC_IOPENR
	ldr r5, [r6]
	movs r4, 0x3
	orrs r5, r5, r4
	str r5, [r6]
/*
	ldr r6, =GPIOA_MODER
	ldr r5, [r6]
	ldr r4, =0xC000
	bics r5, r5, r4
	ldr r4, =0x4000
	orrs r5, r5, r4
	str r5, [r6]
*/

	// Setup PA/4/5/6/7/8 as OUTPUT.
	ldr r6, =GPIOA_MODER
	ldr r5, [r6]
	ldr r4, =1023
	lsls r4, r4, #8
	bics r5, r5, r4
	ldr r4, =341
	lsls r4, r4, #8
	orrs r5, r5, r4
	str r5, [r6]

	// Setup PB/4/5/8/9 as OUTPUT
	ldr r6, =GPIOB_MODER
	ldr r5, [r6]
	ldr r4, =0x78F00
	bics r5, r5, r4
	ldr r4, =0x28500
	orrs r5, r5, r4
	str r5, [r6]

	//Turn off D1 of 7SD
	ldr r6, =GPIOA_ODR
	ldr r5, [r6]
	movs r4, #1			// r4 = 0001
	lsls r4, r4, #7
	bics r5, r5, r4		// clean OD7
	movs r4, #1
	lsls r4, r4, #7		// make 1 to OD7
	bics r5, r5, r4
	str r5, [r6]

	//Turn on PA leds
	ldr r6, =GPIOA_ODR
	ldr r5, [r6]
	movs r4, 0x1F		// r4 = 1_1111
	lsls r4, r4, #4
	bics r5, r5, r4		// clean OD/4/5/6/8
	movs r4, 0x17
	lsls r4, r4, #4		// make 1 to OD/4/5/6/8
	orrs r5, r5, r4
	str r5, [r6]

	//Turn on PB leds
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	movs r4, 0x3F		// r4 = 11_1111
	lsls r4, r4, #4
	bics r5, r5, r4		// clean OD/4/5/8/9
	movs r4, 0x33		// r4 = 11_0011
	lsls r4, r4, #4
	orrs r5, r5, r4
	str r5, [r6]		// make 1 to OD/4/5/8/9

	/* for(;;); */
	b .

	/* this should never get executed */
	nop

