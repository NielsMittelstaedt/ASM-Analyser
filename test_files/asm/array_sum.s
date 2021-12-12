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
	.file	"array_sum.c"
	.text
	.align	2
	.global	sum
	.syntax unified
	.arm
	.fpu softvfp
	.type	sum, %function
sum:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #0
	ble	.L4
	add	r1, r0, r1, lsl #2
	mov	r3, r0
	mov	r0, #0
.L3:
	ldr	r2, [r3], #4
	cmp	r1, r3
	add	r0, r0, r2
	bne	.L3
	bx	lr
.L4:
	mov	r0, #0
	bx	lr
	.size	sum, .-sum
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
