0 	.arch armv7-a
0 	.eabi_attribute 20, 1
0 	.eabi_attribute 21, 1
0 	.eabi_attribute 23, 3
0 	.eabi_attribute 24, 1
0 	.eabi_attribute 25, 1
0 	.eabi_attribute 26, 2
0 	.eabi_attribute 30, 2
0 	.eabi_attribute 34, 1
0 	.eabi_attribute 18, 4
0 	.file	"quicksort.c"
0 	.text
0 	.align	2
0 	.global	quicksort
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	quicksort, %function
0 quicksort:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
7 	cmp	r1, r2
7 	bxge	lr
1 	push	{r4, r5, r6, r7, r8, r9, r10, lr}
1 	mov	r5, r2
1 	mov	r6, r0
0 .L10:
6 	lsl	r7, r1, #2
6 	mov	r4, r5
6 	add	r0, r6, r7
6 	mov	ip, r1
0 .L3:
6 	cmp	r5, ip
6 	ldr	r2, [r6, ip, lsl #2]
6 	ldr	lr, [r0]
6 	lsl	r3, ip, #2
6 	movgt	r9, #1
6 	movle	r9, #0
6 	cmp	r2, lr
6 	add	r8, r6, r3
6 	movgt	r9, #0
6 	cmp	r9, #0
6 	addne	r3, r3, #4
6 	addne	r3, r6, r3
6 	beq	.L9
0 .L4:
6 	mov	r8, r3
6 	ldr	r2, [r3], #4
6 	add	ip, ip, #1
6 	cmp	r2, lr
6 	cmple	ip, r5
6 	blt	.L4
0 .L9:
6 	ldr	r10, [r6, r4, lsl #2]
6 	lsl	r3, r4, #2
6 	add	r9, r6, r3
6 	cmp	r10, lr
6 	ble	.L5
6 	sub	r3, r3, #4
6 	add	r3, r6, r3
0 .L6:
21 	mov	r9, r3
21 	ldr	r10, [r3], #-4
21 	sub	r4, r4, #1
21 	cmp	r10, lr
21 	bgt	.L6
0 .L5:
6 	cmp	ip, r4
6 	blt	.L19
6 	str	r10, [r6, r7]
6 	sub	r2, r4, #1
6 	mov	r0, r6
6 	str	lr, [r9]
6 	bl	quicksort
6 	add	r1, r4, #1
6 	cmp	r1, r5
6 	blt	.L10
1 	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
0 .L19:
0 	str	r10, [r8]
0 	str	r2, [r9]
0 	b	.L3
0 	.size	quicksort, .-quicksort
0 	.section	.rodata.str1.4,"aMS",%progbits,1
0 	.align	2
0 .LC1:
0 	.ascii	"Order of Sorted elements: \000"
0 	.align	2
0 .LC2:
0 	.ascii	" %d\000"
0 	.section	.text.startup,"ax",%progbits
0 	.align	2
0 	.global	main
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	main, %function
0 main:
0 	@ args = 0, pretend = 0, frame = 32
0 	@ frame_needed = 0, uses_anonymous_args = 0
1 	movw	ip, #:lower16:.LANCHOR0
1 	movt	ip, #:upper16:.LANCHOR0
1 	push	{r4, r5, r6, lr}
1 	sub	sp, sp, #32
1 	ldmia	ip!, {r0, r1, r2, r3}
1 	add	lr, sp, #4
1 	movw	r5, #:lower16:.LC2
1 	add	r6, sp, #28
1 	movt	r5, #:upper16:.LC2
1 	mov	r4, sp
1 	stmia	lr!, {r0, r1, r2, r3}
1 	ldm	ip, {r0, r1, r2}
1 	stm	lr, {r0, r1, r2}
1 	add	r0, sp, #4
1 	mov	r1, #0
1 	mov	r2, #6
1 	bl	quicksort
1 	movw	r1, #:lower16:.LC1
1 	mov	r0, #1
1 	movt	r1, #:upper16:.LC1
1 	bl	__printf_chk
0 .L21:
7 	ldr	r2, [r4, #4]!
7 	mov	r1, r5
7 	mov	r0, #1
7 	bl	__printf_chk
7 	cmp	r4, r6
7 	bne	.L21
1 	mov	r0, #0
1 	add	sp, sp, #32
0 	@ sp needed
1 	pop	{r4, r5, r6, pc}
