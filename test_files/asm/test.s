0 	.arch armv7-a
0 	.eabi_attribute 20, 1
0 	.eabi_attribute 21, 1
0 	.eabi_attribute 23, 3
0 	.eabi_attribute 24, 1
0 	.eabi_attribute 25, 1
0 	.eabi_attribute 26, 2
0 	.eabi_attribute 30, 1
0 	.eabi_attribute 34, 1
0 	.eabi_attribute 18, 4
0 	.file	"test.c"
0 	.text
0 	.global	__aeabi_idivmod
0 	.align	2
0 	.global	mulmod
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	mulmod, %function
0 mulmod:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
0 	push	{r4, r5, r6, r7, r8, lr}
0 	mov	r4, r1
0 	mov	r6, r2
0 	mov	r1, r2
0 	bl	__aeabi_idivmod
0 	cmp	r4, #0
0 	ble	.L5
0 	mov	r5, r1
0 	mov	r7, #0
0 	b	.L4
0 .L3:
0 	mov	r1, r6
0 	lsl	r0, r5, #1
0 	bl	__aeabi_idivmod
0 	mov	r5, r1
0 	add	r3, r4, r4, lsr #31
0 	asr	r3, r3, #1
0 	cmp	r4, #1
0 	ble	.L2
0 	mov	r4, r3
0 .L4:
0 	cmp	r4, #0
0 	and	r3, r4, #1
0 	rsblt	r3, r3, #0
0 	cmp	r3, #1
0 	bne	.L3
0 	mov	r1, r6
0 	add	r0, r7, r5
0 	bl	__aeabi_idivmod
0 	mov	r7, r1
0 	b	.L3
0 .L5:
0 	mov	r7, #0
0 .L2:
0 	mov	r1, r6
0 	mov	r0, r7
0 	bl	__aeabi_idivmod
0 	mov	r0, r1
0 	pop	{r4, r5, r6, r7, r8, pc}
0 	.size	mulmod, .-mulmod
0 	.align	2
0 	.global	modulo
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	modulo, %function
0 modulo:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
0 	push	{r4, r5, r6, r7, r8, lr}
0 	mov	r6, r2
0 	subs	r4, r1, #0
0 	ble	.L12
0 	mov	r5, r0
0 	mov	r7, #1
0 	b	.L11
0 .L10:
0 	mov	r1, r6
0 	mul	r0, r5, r5
0 	bl	__aeabi_idivmod
0 	mov	r5, r1
0 	add	r3, r4, r4, lsr #31
0 	asr	r3, r3, #1
0 	cmp	r4, #1
0 	ble	.L9
0 	mov	r4, r3
0 .L11:
0 	cmp	r4, #0
0 	and	r3, r4, #1
0 	rsblt	r3, r3, #0
0 	cmp	r3, #1
0 	bne	.L10
0 	mov	r1, r6
0 	mul	r0, r5, r7
0 	bl	__aeabi_idivmod
0 	mov	r7, r1
0 	b	.L10
0 .L12:
0 	mov	r7, #1
0 .L9:
0 	mov	r1, r6
0 	mov	r0, r7
0 	bl	__aeabi_idivmod
0 	mov	r0, r1
0 	pop	{r4, r5, r6, r7, r8, pc}
0 	.size	modulo, .-modulo
0 	.align	2
0 	.global	Miller
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	Miller, %function
0 Miller:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
1 	cmp	r0, #1
1 	ble	.L23
1 	push	{r4, r5, r6, r7, r8, r9, r10, lr}
1 	mov	r5, r0
1 	mov	r8, r1
1 	cmp	r0, #2
1 	beq	.L24
1 	tst	r0, #1
1 	beq	.L25
0 	sub	r4, r0, #1
0 	beq	.L26
0 	mov	r6, r4
0 .L18:
0 	add	r3, r6, r6, lsr #31
0 	asr	r6, r3, #1
0 	tst	r3, #2
0 	beq	.L18
0 .L17:
0 	cmp	r8, #0
0 	ble	.L27
0 	mov	r7, #0
0 	b	.L22
0 .L24:
0 	mov	r4, #1
0 	mov	r6, r4
0 	b	.L17
0 .L26:
0 	mov	r6, r4
0 	b	.L17
0 .L28:
0 	mov	r9, r6
0 	b	.L19
0 .L21:
0 	add	r7, r7, #1
0 	cmp	r8, r7
0 	beq	.L37
0 .L22:
0 	bl	rand
0 	mov	r1, r4
0 	bl	__aeabi_idivmod
0 	mov	r0, r1
0 	mov	r2, r5
0 	mov	r1, r6
0 	add	r0, r0, #1
0 	bl	modulo
0 	cmp	r0, #1
0 	cmpne	r4, r0
0 	movne	r3, #1
0 	moveq	r3, #0
0 	cmp	r4, r6
0 	moveq	r3, #0
0 	andne	r3, r3, #1
0 	cmp	r3, #0
0 	beq	.L28
0 	mov	r9, r6
0 .L20:
0 	mov	r2, r5
0 	mov	r1, r0
0 	bl	mulmod
0 	lsl	r9, r9, #1
0 	cmp	r0, #1
0 	cmpne	r4, r0
0 	movne	r3, #1
0 	moveq	r3, #0
0 	cmp	r4, r9
0 	moveq	r3, #0
0 	andne	r3, r3, #1
0 	cmp	r3, #0
0 	bne	.L20
0 .L19:
0 	cmp	r4, r0
0 	beq	.L21
0 	tst	r9, #1
0 	bne	.L21
0 	mov	r0, #0
0 	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
0 .L37:
0 	mov	r0, #1
0 	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
0 .L23:
0 	mov	r0, #0
0 	bx	lr
0 .L25:
1 	mov	r0, #0
1 	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
0 .L27:
0 	mov	r0, #1
0 	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
0 	.size	Miller, .-Miller
0 	.align	2
0 	.global	swap
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	swap, %function
0 swap:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
0 	@ link register save eliminated.
25 	ldr	r3, [r0, r1, lsl #2]
25 	ldr	ip, [r0, r2, lsl #2]
25 	str	ip, [r0, r1, lsl #2]
25 	str	r3, [r0, r2, lsl #2]
25 	bx	lr
0 	.size	swap, .-swap
0 	.align	2
0 	.global	heapify
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	heapify, %function
0 heapify:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
30 	push	{r4, r5, r6, lr}
30 	mov	r5, r0
30 	mov	r6, r1
30 	lsl	r4, r2, #1
30 	add	r3, r4, #1
30 	add	r4, r4, #2
30 	cmp	r3, r1
30 	bcs	.L40
19 	ldr	r0, [r0, r2, lsl #2]
19 	ldr	r1, [r5, r3, lsl #2]
19 	cmp	r0, r1
19 	bcs	.L40
11 	cmp	r4, r6
11 	movcs	r4, r3
11 	bcs	.L41
10 	mov	r0, r1
10 	ldr	r1, [r5, r4, lsl #2]
10 	cmp	r0, r1
10 	movcs	r4, r3
10 	b	.L41
0 .L40:
19 	cmp	r6, r4
19 	popls	{r4, r5, r6, pc}
7 	ldr	r1, [r5, r2, lsl #2]
7 	ldr	r3, [r5, r4, lsl #2]
7 	cmp	r1, r3
7 	popcs	{r4, r5, r6, pc}
0 .L41:
16 	cmp	r4, r2
16 	popeq	{r4, r5, r6, pc}
16 	mov	r1, r4
16 	mov	r0, r5
16 	bl	swap
16 	mov	r2, r4
16 	mov	r1, r6
16 	mov	r0, r5
16 	bl	heapify
16 	pop	{r4, r5, r6, pc}
0 	.size	heapify, .-heapify
0 	.align	2
0 	.global	heapSort
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	heapSort, %function
0 heapSort:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
1 	push	{r4, r5, r6, lr}
1 	mov	r6, r0
1 	mov	r4, r1
1 	lsr	r5, r1, #1
1 	subs	r5, r5, #1
1 	bmi	.L47
0 .L48:
5 	mov	r2, r5
5 	mov	r1, r4
5 	mov	r0, r6
5 	bl	heapify
5 	subs	r5, r5, #1
5 	bpl	.L48
0 .L47:
1 	subs	r4, r4, #1
1 	popeq	{r4, r5, r6, pc}
1 	mov	r5, #0
0 .L50:
9 	mov	r2, r4
9 	mov	r1, r5
9 	mov	r0, r6
9 	bl	swap
9 	mov	r2, r5
9 	mov	r1, r4
9 	mov	r0, r6
9 	bl	heapify
9 	subs	r4, r4, #1
9 	bne	.L50
1 	pop	{r4, r5, r6, pc}
0 	.size	heapSort, .-heapSort
0 	.section	.rodata.str1.4,"aMS",%progbits,1
0 	.align	2
0 .LC1:
0 	.ascii	"array[%d]: \000"
0 	.align	2
0 .LC2:
0 	.ascii	"%d\012\000"
0 	.text
0 	.align	2
0 	.global	test
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	test, %function
0 test:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
1 	push	{r4, r5, r6, r7, r8, r9, r10, lr}
1 	mov	r6, r0
1 	mov	r1, #10
1 	bl	heapSort
1 	sub	r7, r6, #4
1 	mov	r4, #0
1 	movw	r9, #:lower16:.LC1
1 	movt	r9, #:upper16:.LC1
1 	mov	r5, #1
1 	movw	r8, #:lower16:.LC2
1 	movt	r8, #:upper16:.LC2
0 .L55:
10 	mov	r2, r4
10 	mov	r1, r9
10 	mov	r0, r5
10 	bl	__printf_chk
10 	ldr	r2, [r7, #4]!
10 	mov	r1, r8
10 	mov	r0, r5
10 	bl	__printf_chk
10 	add	r4, r4, #1
10 	cmp	r4, #10
10 	bne	.L55
1 	mov	r3, #0
1 	mov	r0, r3
1 	movw	r1, #21846
1 	movt	r1, 21845
0 .L56:
10 	tst	r3, #1
10 	ldr	r2, [r6, r3, lsl #2]
10 	addeq	r0, r0, r2
10 	subne	r0, r0, r2
10 	add	r3, r3, #1
10 	cmp	r3, #10
10 	popeq	{r4, r5, r6, r7, r8, r9, r10, pc}
9 	smull	ip, r2, r1, r3
9 	sub	r2, r2, r3, asr #31
9 	add	r2, r2, r2, lsl #1
9 	cmp	r3, r2
9 	ldrne	r2, [r6, r3, lsl #2]
9 	mulne	r0, r2, r0
9 	b	.L56
0 	.size	test, .-test
0 	.align	2
0 	.global	fib
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	fib, %function
0 fib:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
11405773 	push	{r4, r5, r6, lr}
11405773 	mov	r4, r0
11405773 	cmp	r0, #1
11405773 	pople	{r4, r5, r6, pc}
5702886 	sub	r0, r0, #1
5702886 	bl	fib
5702886 	mov	r5, r0
5702886 	sub	r0, r4, #2
5702886 	bl	fib
5702886 	add	r0, r5, r0
5702886 	pop	{r4, r5, r6, pc}
0 	.size	fib, .-fib
0 	.global	__aeabi_i2d
0 	.global	__aeabi_dadd
0 	.global	__aeabi_d2iz
0 	.section	.rodata.str1.4
0 	.align	2
0 .LC3:
0 	.ascii	"tmp: %d\012\000"
0 	.align	2
0 .LC4:
0 	.ascii	"crossSum: %d\012\000"
0 	.global	__aeabi_idiv
0 	.align	2
0 .LC5:
0 	.ascii	"tmp2: %d\012\000"
0 	.align	2
0 .LC6:
0 	.ascii	"%d is prime\012\000"
0 	.align	2
0 .LC7:
0 	.ascii	"%d is not prime\012\000"
0 	.align	2
0 .LC8:
0 	.ascii	"Ergebnis: %d\012\000"
0 	.text
0 	.align	2
0 	.global	main
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	main, %function
0 main:
0 	@ args = 0, pretend = 0, frame = 40
0 	@ frame_needed = 0, uses_anonymous_args = 0
1 	push	{r4, r5, lr}
1 	sub	sp, sp, #44
1 	mov	lr, sp
1 	movw	ip, #:lower16:.LANCHOR0
1 	movt	ip, #:upper16:.LANCHOR0
1 	ldmia	ip!, {r0, r1, r2, r3}
1 	stmia	lr!, {r0, r1, r2, r3}
1 	ldmia	ip!, {r0, r1, r2, r3}
1 	stmia	lr!, {r0, r1, r2, r3}
1 	ldm	ip, {r0, r1}
1 	stm	lr, {r0, r1}
1 	mov	r0, sp
1 	bl	test
1 	mul	r3, r0, r0
1 	mul	r3, r3, r0
1 	mul	r3, r3, r3
1 	mul	r0, r0, r3
1 	bl	__aeabi_i2d
1 	movw	r2, #18350
1 	movt	r2, 31457
1 	movw	r3, #44564
1 	movt	r3, 16371
1 	bl	__aeabi_dadd
1 	bl	__aeabi_d2iz
1 	mov	r5, r0
1 	mov	r2, r0
1 	movw	r1, #:lower16:.LC3
1 	movt	r1, #:upper16:.LC3
1 	mov	r0, #1
1 	bl	__printf_chk
1 	cmp	r5, #0
1 	beq	.L73
1 	mov	r3, r5
1 	mov	r4, #0
1 	movw	ip, #26215
1 	movt	ip, 26214
1 	mov	r0, #10
0 .L70:
10 	smull	r2, r1, ip, r3
10 	asr	r2, r3, #31
10 	rsb	r2, r2, r1, asr #2
10 	mls	r3, r0, r2, r3
10 	add	r4, r4, r3
10 	mov	r3, r2
10 	cmp	r2, #0
10 	bne	.L70
0 .L69:
1 	mov	r2, r4
1 	movw	r1, #:lower16:.LC4
1 	movt	r1, #:upper16:.LC4
1 	mov	r0, #1
1 	bl	__printf_chk
1 	mul	r1, r4, r4
1 	mov	r0, r5
1 	bl	__aeabi_idiv
1 	mov	r5, r0
1 	mov	r2, r0
1 	movw	r1, #:lower16:.LC5
1 	movt	r1, #:upper16:.LC5
1 	mov	r0, #1
1 	bl	__printf_chk
1 	mov	r0, r4
1 	bl	fib
1 	mov	r1, r4
1 	bl	__aeabi_idiv
1 	mov	r1, r0
1 	mov	r0, r5
1 	bl	__aeabi_idiv
1 	mov	r4, r0
1 	mov	r1, #10
1 	bl	Miller
1 	cmp	r0, #0
1 	mov	r2, r4
1 	movwne	r1, #:lower16:.LC6
1 	movtne	r1, #:upper16:.LC6
1 	movweq	r1, #:lower16:.LC7
1 	movteq	r1, #:upper16:.LC7
1 	mov	r0, #1
1 	bl	__printf_chk
1 	mov	r2, r4
1 	movw	r1, #:lower16:.LC8
1 	movt	r1, #:upper16:.LC8
1 	mov	r0, #1
1 	bl	__printf_chk
1 	mov	r0, #0
1 	add	sp, sp, #44
0 	@ sp needed
1 	pop	{r4, r5, pc}
0 .L73:
0 	mov	r4, r5
0 	b	.L69
