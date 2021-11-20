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
	.file	"float_incr.c"
	.text
	.global	__aeabi_f2d
	.global	__aeabi_dadd
	.global	__aeabi_d2f
	.align	2
	.global	f
	.syntax unified
	.arm
	.fpu softvfp
	.type	f, %function
f:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	bl	__aeabi_f2d
	movw	r2, #3626
	movw	r3, #4829
	movt	r2, 21078
	movt	r3, 16385
	bl	__aeabi_dadd
	bl	__aeabi_d2f
	pop	{r4, pc}
	.size	f, .-f
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
	@ link register save eliminated.
	mov	r0, #0
	bx	lr
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
