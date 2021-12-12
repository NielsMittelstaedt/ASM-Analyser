	.arch armv7-a
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"fib.c"
	.text
	.align	2
	.global	fib
	.syntax unified
	.arm
	.fpu softvfp
	.type	fib, %function
fib:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r0, #1
	bxle	lr
	push	{r4, r5, r6, r7, r8, lr}
	sub	r7, r0, #2
	sub	r6, r0, #3
	bic	r3, r7, #1
	sub	r5, r0, #1
	sub	r6, r6, r3
	mov	r4, #0
.L3:
	mov	r0, r5
	sub	r5, r5, #2
	bl	fib
	cmp	r5, r6
	add	r4, r4, r0
	bne	.L3
	and	r0, r7, #1
	add	r0, r0, r4
	pop	{r4, r5, r6, r7, r8, pc}
	.size	fib, .-fib
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r0, #5
	bl	fib
	mov	r0, #3
	bl	fib
	mov	r0, #1
	bl	fib
	mov	r0, #3
	bl	fib
	mov	r0, #1
	bl	fib
	mov	r0, #1
	bl	fib
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
