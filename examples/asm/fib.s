	.arch armv7-a
	.arch_extension virt
	.arch_extension idiv
	.arch_extension sec
	.arch_extension mp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
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
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #12
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	cmp	r3, #1
	bgt	.L2
	ldr	r3, [fp, #-16]
	b	.L3
.L2:
	ldr	r3, [fp, #-16]
	sub	r3, r3, #1
	mov	r0, r3
	bl	fib
	mov	r4, r0
	ldr	r3, [fp, #-16]
	sub	r3, r3, #2
	mov	r0, r3
	bl	fib
	mov	r3, r0
	add	r3, r4, r3
.L3:
	mov	r0, r3
	sub	sp, fp, #8
	@ sp needed
	pop	{r4, fp, pc}
	.size	fib, .-fib
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	mov	r0, #3
	bl	fib
	mov	r3, #0
	mov	r0, r3
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
