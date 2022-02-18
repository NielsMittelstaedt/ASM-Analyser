1.00 0 	.arch armv7-a
1.00 0 	.eabi_attribute 20, 1
1.00 0 	.eabi_attribute 21, 1
1.00 0 	.eabi_attribute 23, 3
1.00 0 	.eabi_attribute 24, 1
1.00 0 	.eabi_attribute 25, 1
1.00 0 	.eabi_attribute 26, 2
1.00 0 	.eabi_attribute 30, 6
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
1.00 0 	@ args = 0, pretend = 0, frame = 16
1.00 0 	@ frame_needed = 1, uses_anonymous_args = 0
1.00 0 	@ link register save eliminated.
1.00 1 	str	fp, [sp, #-4]!
1.00 1 	add	fp, sp, #0
1.00 1 	sub	sp, sp, #20
1.00 1 	str	r0, [fp, #-16]
1.00 1 	str	r1, [fp, #-20]
1.00 1 	ldr	r2, [fp, #-16]
1.00 1 	ldr	r3, [fp, #-20]
1.00 1 	add	r3, r2, r3
1.00 1 	str	r3, [fp, #-8]
1.00 1 	ldr	r3, [fp, #-8]
1.00 1 	mov	r0, r3
1.00 1 	add	sp, fp, #0
1.00 0 	@ sp needed
1.00 1 	ldr	fp, [sp], #4
1.00 1 	bx	lr
1.00 0 	.size	addition, .-addition
1.00 0 	.align	2
1.00 0 	.global	main
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	main, %function
1.00 0 main:
1.00 0 	@ args = 0, pretend = 0, frame = 0
1.00 0 	@ frame_needed = 1, uses_anonymous_args = 0
1.00 1 	push	{fp, lr}
1.00 1 	add	fp, sp, #4
1.00 1 	mov	r1, #3
1.00 1 	mov	r0, #2
1.00 1 	bl	addition
1.00 1 	mov	r3, r0
1.00 1 	mov	r0, r3
1.00 1 	pop	{fp, pc}
1.00 0 	.size	main, .-main
1.00 0 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
1.00 0 	.section	.note.GNU-stack,"",%progbits
