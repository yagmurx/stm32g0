
/*
 * lab2_prob1.s
 *
 * author: Mervenur Kılıçarslan
 * 1901022259 - ELEC335 - LAB 2
 * Gebze Technical University - Electronics Engineering - Microprocessors labratory class
 * Description: turning on and off the green LED on the G031K8 Nucleo board.
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

.equ GPIOB_BASE,		(0x50000400)          // GPIOC base address
.equ GPIOB_MODER,		(GPIOB_BASE + (0x00)) // GPIOC MODER register offset
.equ GPIOB_ODR,			(GPIOB_BASE + (0x14)) // GPIOC ODR register offset
.equ GPIOB_IDR,			(GPIOB_BASE + (0X10)) // GPIOC IDR offset

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
/* main function */
.section .text
main:

	ldr r6,=RCC_IOPENR
	ldr r5,[r6]
	movs r4,#2 // B portu aktif etmek için
	orrs r5,r5,r4
	str r5,[r6] // r5deki B portu aktif eden datayı r6ya yazıyorum


	ldr r6,=GPIOB_MODER // in out modu
	ldr r5,[r6]
	ldr r4,=0xFFF3F // kullanacagım pinleri modere gore sectim
	mvns r4,r4
	ands r5,r5,r4
	ldr r4,= 0x54555
	orrs r5,r5,r4
	str r5,[r6]

	bl button_control


play:

	ldr r4,=0x100 // D8 orta led t1
	bl leds_on
	bl button_control


	ldr r4,=0x304 // t2
	bl leds_on
	bl button_control


	ldr r4,=0x325 // t3
	bl leds_on
	bl button_control


	ldr r4,=0x337 // t4
	bl leds_on
	bl button_control


	ldr r4,=0x325 //t5
	bl leds_on
	bl button_control


	ldr r4,=0x304 //t6
	bl leds_on
	bl button_control


	ldr r4,=0x100 //t7
	bl leds_on
	bl button_control


 	b play

pause:
	ldr r6, = GPIOB_ODR
	ldr r5, [r6] //ODR Value
	ldr r4,=0x80 //Status led connected to PB8
	orrs r5, r5, r4 //Setting led on
	str r5, [r6]
	b button_control

	leds_on:
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	cmp r4,0x0 //Control the which led on at last
	beq Reset //If all leds are on, then take all them off
	bne On
	Reset:
	ands r5, r5, r4
	On:
	orrs r5, r5, r4
	str r5, [r6]
	// Assign value to register r1 to sub 1 per clock
	ldr r1, =0x927C0
	delay:
	subs r1, r1, #1
	bne delay
	bx lr

	button_control:
	ldr r6, = GPIOB_IDR
	ldr r5, [r6] //IDR Value
	movs r4, #0x40 //Status switch connected to PB6
	ands r5, r5, r4 //Getting the value of button pressed or not
	lsrs r5, #6 //Shifting to lsb for compare
	cmp r5, #0x1 //Compare IDR Value with 1 bit
	bne BNE //If not equal
	beq BEQ

	BEQ:
	b pause

	BNE:
	//Status Led Off
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	ldr r5, =[0x0]
	str r5, [r6]
	bx lr


	nop

