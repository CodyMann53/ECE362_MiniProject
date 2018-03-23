#Directives
  		.syntax unified
  		.cpu cortex-m0
  		.fpu softvfp
	  	.thumb

#Equates
		.equ	RCC,	 	0x40021000		//RCC peripheral starting memory address

		.equ	AHBENR,	 	0x14				//AHBENR register address offset from starting address

		.equ	GPIOA,	 	0x48000000		//GPIOA
		.equ	GPIOB,	 	0x48000400		//GPIOB
		.equ	GPIOC,	 	0x48000800		//GPIOC
		.equ	GPIOD,	 	0x48000C00		//GPIOD
		.equ	GPIOE,	 	0x48001000		//GPIOE
		.equ	GPIOF,	 	0x48001400		//GPIOF

		.equ	MODER,	 	0x00				//Mode Type [W]
		.equ	OTYPER,		0x04				//Output Type [W]
		.equ	OSPEEDR,  	0x08				//Output Speed [W]
		.equ	PUPDR,	 	0x0C				//Pull-UP Pull-DOWN [W]
		.equ	IDR,	 	0x10				//Input Data Register [R]
		.equ	ODR,	 	0x14				//Output Data Register [R/W]
		.equ	BSRR,	 	0x18				//Port Bit Set/Reset Register [W]
		.equ	LCKR,	 	0x1C				//Configuration Lock Register [W]
		.equ	AFRL,	 	0x20				//Alternate Function Low Register [W]
		.equ	AFRH,	 	0x24				//Alternate Function High Register [W]
		.equ	BRR,	 	0x28				//Bit Reset Register [R]

.text
.global ledStripWrite

	//r0 - data address	(passed as argument)
	//r1 - bit counter
	//r2 - color byte counter [runs from 0 to one minus the number of color data bytes]
	//r3 - 0b01 left shifted 9
	//r4 - GPIO adress
	//r5 - BSRR/BRR address (loaded with the proper address at the time of the GPIO toggle)
	//r6 - the number of bytes of data to be written to the leds (passed as argument, loaded into r7 from r1)
	//r7 - color data is loaded into this register

ledStripWrite:
		push {r4, r5, r6, r7}
		//load registers with proper values
		//r0 already has the address of the data in it
		movs r6, r1				//move the number of bytes from r1 into r6

		ldr r1, =1
		ldr r2, =0
		ldr r3, =0b01
		lsls r3, r3, 9
		ldr r4, =GPIOC
		ldr r5, =BSRR

		phaseOne:
		str r3, [r4, r5]		//set bsrr
		ldr r7, [r0, r2]		//load the color data from the inital data address plus the color byte offset
		rev r7, r7
		ldr r5, =BRR			//load r5 with the address of the BRR for the next time the GPIO is toggled
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		//adds r5, r5, #0			/*used as a nop*/
		//adds r5, r5, #0			/*used as a nop*/
		//adds r5, r5, #0			/*used as a nop*/
		//adds r5, r5, #0			/*used as a nop*/
		lsls r7, r7, r1			//left shift the data (in r7) by the number of bits in the bit counter (r1)
		bcs phaseTwoHigh		//uses 15 clock cycles till branch
		bcc phaseTwoLow			//uses 16 clock cycles till branch

		phaseTwoHigh:
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop - 27th*/
		b phaseThree

		phaseTwoLow:
		str r3, [r4, r5]		//set brr
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop - 26th*/
		b phaseThree

		phaseThree:
		str r3, [r4, r5]		//set brr (send GPIO Low)
		ldr r5, =BSRR			//load r5 with the address of the bsrr for the next GPIO toggle
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r1, r1, #1			//increment the color bit counter
		cmp r1, 32				//compare the value in the bit counter with 8
		bgt phaseByteUpdate		//if the bit value is greater than 8, go into byte Update
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		adds r5, r5, #0			/*used as a nop*/
		b phaseOne				//branch back to phaseOne

		phaseByteUpdate:
		adds r5, r5, #0			/*used as a nop*/
		ldr r1, =1				//reset the bit counter to 1
		adds r2, r2, #4			//add one (byte in bits) to the byte counter
		cmp r2, r6				//compare the byte counter with the maximum number of bytes to be written
		blt phaseOne			//if the byte counter is less than the number of bytes to be written, branch to phaseONE

		pop {r4, r5, r6, r7}
		bx lr
