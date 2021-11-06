/*
 * lab1_prob3.s
 *
 * author: Yagmur Yildiz
 *
 * PROBLEM 2: Write code that will light up 4 external LEDs connected to the board.
 * DATE: 06.11.2021

 * NOTE: I used PB5,6,8 and 9 as OUTPUT
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
	/* enable GPIOB clock, bit2 on IOPENR */
	ldr r6, =RCC_IOPENR
	ldr r5, [r6]
	movs r4, 0x2
	orrs r5, r5, r4
	str r5, [r6]

	// Setup PB4/5 as OUTPUT, write 0101 to bits [8:11] in MODER
	ldr r6, =GPIOB_MODER
	ldr r5, [r6]
	movs r4, #15
	lsls r4, r4, #8
	bics r5, r5, r4 	//clean bits [8:11]
	movs r4, #5
	lsls r4, r4, #8
	orrs r5, r5, r4 	// write 0101 to bits [8:11]
	str r5, [r6]

	//Setup PB8/9 as OUTPUT, write 0101 to bits [16:19] in MODER
	ldr r6, =GPIOB_MODER
	ldr r5, [r6]
	movs r4, #15
	lsls r4, r4, #16
	bics r5, r5, r4 	// clean bits [16:19]
	movs r4, #5
	lsls r4, r4, #16
	orrs r5, r5, r4 	// write 0101 to bits [8:11]
	str r5, [r6]


	/* turn on led connected to B4,B5,B8 and B9 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	movs r4, #255		// r4 = 1111_1111
	lsls r4, r4, #4
	bics r5, r5, r4 	// clean bits [8:11] [16:19]
	movs r4, #51  		// r4 = 0011_0011
	lsls r4, #4
	orrs r5, r5, r4		// r5 = 0011_0011_0000
	str r5, [r6]


	/* for(;;); */
	b .

	/* this should never get executed */
	nop

