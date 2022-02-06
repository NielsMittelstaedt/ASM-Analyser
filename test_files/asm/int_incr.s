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
	.file	"int_incr.c"
	.text
	.align	2
	.global	f
	.syntax unified
	.arm
	.fpu softvfp
	.type	f, %function
f:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	add	r0, r0, #1
	bx	lr
	.size	f, .-f
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Result: %d\012\000"
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
	mov	r2, #3
	movw	r1, #:lower16:.LC0
	push	{r4, lr}
	movt	r1, #:upper16:.LC0
	mov	r0, #1
	bl	__printf_chk
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
