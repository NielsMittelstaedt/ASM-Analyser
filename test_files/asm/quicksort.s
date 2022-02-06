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
	.file	"quicksort.c"
	.text
	.align	2
	.global	quicksort
	.syntax unified
	.arm
	.fpu softvfp
	.type	quicksort, %function
quicksort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, r2
	bxge	lr
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r5, r2
	mov	r6, r0
.L10:
	lsl	r7, r1, #2
	mov	r4, r5
	add	r0, r6, r7
	mov	ip, r1
.L3:
	cmp	r5, ip
	ldr	r2, [r6, ip, lsl #2]
	ldr	lr, [r0]
	lsl	r3, ip, #2
	movgt	r9, #1
	movle	r9, #0
	cmp	r2, lr
	add	r8, r6, r3
	movgt	r9, #0
	cmp	r9, #0
	addne	r3, r3, #4
	addne	r3, r6, r3
	beq	.L9
.L4:
	mov	r8, r3
	ldr	r2, [r3], #4
	add	ip, ip, #1
	cmp	r2, lr
	cmple	ip, r5
	blt	.L4
.L9:
	ldr	r10, [r6, r4, lsl #2]
	lsl	r3, r4, #2
	add	r9, r6, r3
	cmp	r10, lr
	ble	.L5
	sub	r3, r3, #4
	add	r3, r6, r3
.L6:
	mov	r9, r3
	ldr	r10, [r3], #-4
	sub	r4, r4, #1
	cmp	r10, lr
	bgt	.L6
.L5:
	cmp	ip, r4
	blt	.L19
	str	r10, [r6, r7]
	sub	r2, r4, #1
	mov	r0, r6
	str	lr, [r9]
	bl	quicksort
	add	r1, r4, #1
	cmp	r1, r5
	blt	.L10
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L19:
	str	r10, [r8]
	str	r2, [r9]
	b	.L3
	.size	quicksort, .-quicksort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"Order of Sorted elements: \000"
	.align	2
.LC2:
	.ascii	" %d\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #32
	ldmia	ip!, {r0, r1, r2, r3}
	add	lr, sp, #4
	movw	r5, #:lower16:.LC2
	add	r6, sp, #28
	movt	r5, #:upper16:.LC2
	mov	r4, sp
	stmia	lr!, {r0, r1, r2, r3}
	ldm	ip, {r0, r1, r2}
	stm	lr, {r0, r1, r2}
	add	r0, sp, #4
	mov	r1, #0
	mov	r2, #6
	bl	quicksort
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	bl	__printf_chk
.L21:
	ldr	r2, [r4, #4]!
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L21
	mov	r0, #0
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
