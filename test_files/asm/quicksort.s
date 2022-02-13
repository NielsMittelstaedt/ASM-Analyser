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
1.00 0 	.file	"quicksort.c"
1.00 0 	.text
1.00 0 	.align	2
1.00 0 	.global	quicksort
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	quicksort, %function
1.00 0 quicksort:
1.00 0 	@ args = 0, pretend = 0, frame = 0
1.00 0 	@ frame_needed = 0, uses_anonymous_args = 0
1.00 7 	cmp	r1, r2
0.86 7 	bxge	lr
1.00 1 	push	{r4, r5, r6, r7, r8, r9, r10, lr}
1.00 1 	mov	r5, r2
1.00 1 	mov	r6, r0
1.00 0 .L10:
1.00 6 	lsl	r7, r1, #2
1.00 6 	mov	r4, r5
1.00 6 	add	r0, r6, r7
1.00 6 	mov	ip, r1
1.00 0 .L3:
1.00 6 	cmp	r5, ip
1.00 6 	ldr	r2, [r6, ip, lsl #2]
1.00 6 	ldr	lr, [r0]
1.00 6 	lsl	r3, ip, #2
1.00 6 	movgt	r9, #1
1.00 6 	movle	r9, #0
1.00 6 	cmp	r2, lr
1.00 6 	add	r8, r6, r3
1.00 6 	movgt	r9, #0
1.00 6 	cmp	r9, #0
1.00 6 	addne	r3, r3, #4
1.00 6 	addne	r3, r6, r3
1.00 6 	beq	.L9
1.00 0 .L4:
1.00 6 	mov	r8, r3
1.00 6 	ldr	r2, [r3], #4
1.00 6 	add	ip, ip, #1
1.00 6 	cmp	r2, lr
1.00 6 	cmple	ip, r5
1.00 6 	blt	.L4
1.00 0 .L9:
1.00 6 	ldr	r10, [r6, r4, lsl #2]
1.00 6 	lsl	r3, r4, #2
1.00 6 	add	r9, r6, r3
1.00 6 	cmp	r10, lr
1.00 6 	ble	.L5
1.00 6 	sub	r3, r3, #4
1.00 6 	add	r3, r6, r3
1.00 0 .L6:
1.00 21 	mov	r9, r3
1.00 21 	ldr	r10, [r3], #-4
1.00 21 	sub	r4, r4, #1
1.00 21 	cmp	r10, lr
0.52 21 	bgt	.L6
1.00 0 .L5:
1.00 6 	cmp	ip, r4
1.00 6 	blt	.L19
1.00 6 	str	r10, [r6, r7]
1.00 6 	sub	r2, r4, #1
1.00 6 	mov	r0, r6
1.00 6 	str	lr, [r9]
1.00 6 	bl	quicksort
1.00 6 	add	r1, r4, #1
1.00 6 	cmp	r1, r5
0.67 6 	blt	.L10
1.00 1 	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
1.00 0 .L19:
1.00 0 	str	r10, [r8]
1.00 0 	str	r2, [r9]
1.00 0 	b	.L3
1.00 0 	.size	quicksort, .-quicksort
1.00 0 	.section	.rodata.str1.4,"aMS",%progbits,1
1.00 0 	.align	2
1.00 0 .LC1:
1.00 0 	.ascii	"Order of Sorted elements: \000"
1.00 0 	.align	2
1.00 0 .LC2:
1.00 0 	.ascii	" %d\000"
1.00 0 	.section	.text.startup,"ax",%progbits
1.00 0 	.align	2
1.00 0 	.global	main
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	main, %function
1.00 0 main:
1.00 0 	@ args = 0, pretend = 0, frame = 32
1.00 0 	@ frame_needed = 0, uses_anonymous_args = 0
1.00 1 	movw	ip, #:lower16:.LANCHOR0
1.00 1 	movt	ip, #:upper16:.LANCHOR0
1.00 1 	push	{r4, r5, r6, lr}
1.00 1 	sub	sp, sp, #32
1.00 1 	ldmia	ip!, {r0, r1, r2, r3}
1.00 1 	add	lr, sp, #4
1.00 1 	movw	r5, #:lower16:.LC2
1.00 1 	add	r6, sp, #28
1.00 1 	movt	r5, #:upper16:.LC2
1.00 1 	mov	r4, sp
1.00 1 	stmia	lr!, {r0, r1, r2, r3}
1.00 1 	ldm	ip, {r0, r1, r2}
1.00 1 	stm	lr, {r0, r1, r2}
1.00 1 	add	r0, sp, #4
1.00 1 	mov	r1, #0
1.00 1 	mov	r2, #6
1.00 1 	bl	quicksort
1.00 1 	movw	r1, #:lower16:.LC1
1.00 1 	mov	r0, #1
1.00 1 	movt	r1, #:upper16:.LC1
1.00 1 	bl	__printf_chk
1.00 0 .L21:
1.00 7 	ldr	r2, [r4, #4]!
1.00 7 	mov	r1, r5
1.00 7 	mov	r0, #1
1.00 7 	bl	__printf_chk
1.00 7 	cmp	r4, r6
0.71 7 	bne	.L21
1.00 1 	mov	r0, #0
1.00 1 	add	sp, sp, #32
1.00 0 	@ sp needed
1.00 1 	pop	{r4, r5, r6, pc}
1.00 0 	.size	main, .-main
1.00 0 	.section	.rodata
1.00 0 	.align	2
1.00 0 	.set	.LANCHOR0,. + 0
1.00 0 .LC0:
1.00 0 	.word	0
1.00 0 	.word	1
1.00 0 	.word	2
1.00 0 	.word	3
1.00 0 	.word	4
1.00 0 	.word	5
1.00 0 	.word	6
1.00 0 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
1.00 0 	.section	.note.GNU-stack,"",%progbits
