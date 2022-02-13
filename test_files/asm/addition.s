1.00 0 	.arch armv7-a
1.00 0 	.eabi_attribute 20, 1
1.00 0 	.eabi_attribute 21, 1
1.00 0 	.eabi_attribute 23, 3
1.00 0 	.eabi_attribute 24, 1
1.00 0 	.eabi_attribute 25, 1
1.00 0 	.eabi_attribute 26, 2
1.00 0 	.eabi_attribute 30, 2
1.00 0 	.eabi_attribute 34, 1
1.00 0 	.eabi_attribute 18, 4
1.00 0 	.file	"addition.c"
1.00 0 	.text
1.00 0 	.align	2
1.00 0 	.global	addition
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	addition, %function
1.00 0 addition:
1.00 0 	@ args = 0, pretend = 0, frame = 0
1.00 0 	@ frame_needed = 0, uses_anonymous_args = 0
1.00 0 	@ link register save eliminated.
1.00 0 	add	r0, r0, r1
1.00 0 	bx	lr
1.00 0 	.size	addition, .-addition
1.00 0 	.section	.text.startup,"ax",%progbits
1.00 0 	.align	2
1.00 0 	.global	main
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	main, %function
1.00 0 main:
1.00 0 	@ args = 0, pretend = 0, frame = 0
1.00 0 	@ frame_needed = 0, uses_anonymous_args = 0
1.00 0 	@ link register save eliminated.
1.00 1 	mov	r0, #5
1.00 1 	bx	lr
1.00 0 	.size	main, .-main
1.00 0 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
1.00 0 	.section	.note.GNU-stack,"",%progbits
