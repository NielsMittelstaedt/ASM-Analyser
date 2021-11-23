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
	.file	"shaker_sort.c"
	.text
	.align	2
	.global	swap
	.syntax unified
	.arm
	.fpu softvfp
	.type	swap, %function
swap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, [r0]
	ldr	r2, [r1]
	str	r2, [r0]
	str	r3, [r1]
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	shakersort
	.syntax unified
	.arm
	.fpu softvfp
	.type	shakersort, %function
shakersort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, r7, lr}
	add	r6, r1, r1, lsr #31
	pople	{r4, r5, r6, r7, pc}
	sub	ip, r1, #1
	asr	r6, r6, #1
	sub	r5, r1, #2
	mov	lr, r0
	add	ip, r0, ip, lsl #2
	mov	r4, #0
	mov	r7, #1
.L11:
	sub	r3, r1, r7
	cmp	r4, r3
	bge	.L5
	mov	r3, lr
.L7:
	ldr	r2, [r3]
	ldr	r0, [r3, #4]!
	cmp	r2, r0
	stmdagt	r3, {r0, r2}
	cmp	r3, ip
	bne	.L7
.L5:
	sub	ip, ip, #4
	cmp	r5, r7
	movge	r3, ip
	blt	.L8
.L10:
	ldr	r2, [r3]
	ldr	r0, [r3, #-4]!
	cmp	r2, r0
	strlt	r0, [r3, #4]
	strlt	r2, [r3]
	cmp	r3, lr
	bne	.L10
.L8:
	add	r7, r7, #1
	add	r4, r4, #1
	cmp	r7, r6
	sub	r5, r5, #1
	add	lr, lr, #4
	ble	.L11
	pop	{r4, r5, r6, r7, pc}
	.size	shakersort, .-shakersort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
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
	push	{r4, r5, r6, r7, r8, lr}
	mov	r0, #24
	bl	malloc
	mov	r1, #6
	mov	r3, #5
	mov	r2, #4
	movw	r6, #:lower16:.LC0
	movt	r6, #:upper16:.LC0
	str	r3, [r0, #4]
	mov	r3, #3
	str	r2, [r0, #8]
	mov	r2, #2
	str	r3, [r0, #12]
	mov	r3, #1
	str	r1, [r0]
	mov	r5, r0
	str	r2, [r0, #16]
	sub	r4, r5, #4
	str	r3, [r0, #20]
	add	r7, r5, #20
	bl	shakersort
.L19:
	ldr	r2, [r4, #4]!
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r7, r4
	bne	.L19
	mov	r0, r5
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
