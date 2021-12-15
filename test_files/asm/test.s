0 	.arch armv7-a
0 	.eabi_attribute 20, 1
0 	.eabi_attribute 21, 1
0 	.eabi_attribute 23, 3
0 	.eabi_attribute 24, 1
0 	.eabi_attribute 25, 1
0 	.eabi_attribute 26, 2
0 	.eabi_attribute 30, 6
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
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 1, uses_anonymous_args = 0
21 	push	{fp, lr}
21 	add	fp, sp, #4
21 	sub	sp, sp, #24
21 	str	r0, [fp, #-16]
21 	str	r1, [fp, #-20]
21 	str	r2, [fp, #-24]
21 	mov	r3, #0
21 	str	r3, [fp, #-8]
21 	ldr	r3, [fp, #-16]
21 	ldr	r1, [fp, #-24]
21 	mov	r0, r3
21 	bl	__aeabi_idivmod
21 	mov	r3, r1
21 	str	r3, [fp, #-12]
21 	b	.L2
0 .L4:
73 	ldr	r3, [fp, #-20]
73 	cmp	r3, #0
73 	and	r3, r3, #1
73 	rsblt	r3, r3, #0
73 	cmp	r3, #1
73 	bne	.L3
45 	ldr	r2, [fp, #-8]
45 	ldr	r3, [fp, #-12]
45 	add	r3, r2, r3
45 	ldr	r1, [fp, #-24]
45 	mov	r0, r3
45 	bl	__aeabi_idivmod
45 	mov	r3, r1
45 	str	r3, [fp, #-8]
0 .L3:
73 	ldr	r3, [fp, #-12]
73 	lsl	r3, r3, #1
73 	ldr	r1, [fp, #-24]
73 	mov	r0, r3
73 	bl	__aeabi_idivmod
73 	mov	r3, r1
73 	str	r3, [fp, #-12]
73 	ldr	r3, [fp, #-20]
73 	lsr	r2, r3, #31
73 	add	r3, r2, r3
73 	asr	r3, r3, #1
73 	str	r3, [fp, #-20]
0 .L2:
94 	ldr	r3, [fp, #-20]
94 	cmp	r3, #0
94 	bgt	.L4
21 	ldr	r3, [fp, #-8]
21 	ldr	r1, [fp, #-24]
21 	mov	r0, r3
21 	bl	__aeabi_idivmod
21 	mov	r3, r1
21 	mov	r0, r3
21 	sub	sp, fp, #4
0 	@ sp needed
21 	pop	{fp, pc}
0 	.size	mulmod, .-mulmod
0 	.align	2
0 	.global	modulo
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	modulo, %function
0 modulo:
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 1, uses_anonymous_args = 0
10 	push	{fp, lr}
10 	add	fp, sp, #4
10 	sub	sp, sp, #24
10 	str	r0, [fp, #-16]
10 	str	r1, [fp, #-20]
10 	str	r2, [fp, #-24]
10 	mov	r3, #1
10 	str	r3, [fp, #-8]
10 	ldr	r3, [fp, #-16]
10 	str	r3, [fp, #-12]
10 	b	.L7
0 .L9:
10 	ldr	r3, [fp, #-20]
10 	cmp	r3, #0
10 	and	r3, r3, #1
10 	rsblt	r3, r3, #0
10 	cmp	r3, #1
10 	bne	.L8
10 	ldr	r3, [fp, #-8]
10 	ldr	r2, [fp, #-12]
10 	mul	r3, r2, r3
10 	ldr	r1, [fp, #-24]
10 	mov	r0, r3
10 	bl	__aeabi_idivmod
10 	mov	r3, r1
10 	str	r3, [fp, #-8]
0 .L8:
10 	ldr	r3, [fp, #-12]
10 	mul	r3, r3, r3
10 	ldr	r1, [fp, #-24]
10 	mov	r0, r3
10 	bl	__aeabi_idivmod
10 	mov	r3, r1
10 	str	r3, [fp, #-12]
10 	ldr	r3, [fp, #-20]
10 	lsr	r2, r3, #31
10 	add	r3, r2, r3
10 	asr	r3, r3, #1
10 	str	r3, [fp, #-20]
0 .L7:
20 	ldr	r3, [fp, #-20]
20 	cmp	r3, #0
20 	bgt	.L9
10 	ldr	r3, [fp, #-8]
10 	ldr	r1, [fp, #-24]
10 	mov	r0, r3
10 	bl	__aeabi_idivmod
10 	mov	r3, r1
10 	mov	r0, r3
10 	sub	sp, fp, #4
0 	@ sp needed
10 	pop	{fp, pc}
0 	.size	modulo, .-modulo
0 	.align	2
0 	.global	Miller
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	Miller, %function
0 Miller:
0 	@ args = 0, pretend = 0, frame = 32
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #32
1 	str	r0, [fp, #-32]
1 	str	r1, [fp, #-36]
1 	ldr	r3, [fp, #-32]
1 	cmp	r3, #1
1 	bgt	.L12
0 	mov	r3, #0
0 	b	.L13
0 .L12:
1 	ldr	r3, [fp, #-32]
1 	cmp	r3, #2
1 	beq	.L14
1 	ldr	r3, [fp, #-32]
1 	and	r3, r3, #1
1 	cmp	r3, #0
1 	bne	.L14
0 	mov	r3, #0
0 	b	.L13
0 .L14:
1 	ldr	r3, [fp, #-32]
1 	sub	r3, r3, #1
1 	str	r3, [fp, #-12]
1 	b	.L15
0 .L16:
4 	ldr	r3, [fp, #-12]
4 	lsr	r2, r3, #31
4 	add	r3, r2, r3
4 	asr	r3, r3, #1
4 	str	r3, [fp, #-12]
0 .L15:
5 	ldr	r3, [fp, #-12]
5 	and	r3, r3, #1
5 	cmp	r3, #0
5 	beq	.L16
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	b	.L17
0 .L22:
10 	bl	rand
10 	mov	r2, r0
10 	ldr	r3, [fp, #-32]
10 	sub	r3, r3, #1
10 	mov	r1, r3
10 	mov	r0, r2
10 	bl	__aeabi_idivmod
10 	mov	r3, r1
10 	add	r3, r3, #1
10 	str	r3, [fp, #-24]
10 	ldr	r3, [fp, #-12]
10 	str	r3, [fp, #-16]
10 	ldr	r2, [fp, #-32]
10 	ldr	r1, [fp, #-16]
10 	ldr	r0, [fp, #-24]
10 	bl	modulo
10 	str	r0, [fp, #-20]
10 	b	.L18
0 .L20:
21 	ldr	r2, [fp, #-32]
21 	ldr	r1, [fp, #-20]
21 	ldr	r0, [fp, #-20]
21 	bl	mulmod
21 	str	r0, [fp, #-20]
21 	ldr	r3, [fp, #-16]
21 	lsl	r3, r3, #1
21 	str	r3, [fp, #-16]
0 .L18:
31 	ldr	r3, [fp, #-32]
31 	sub	r3, r3, #1
31 	ldr	r2, [fp, #-16]
31 	cmp	r2, r3
31 	beq	.L19
31 	ldr	r3, [fp, #-20]
31 	cmp	r3, #1
31 	beq	.L19
31 	ldr	r3, [fp, #-32]
31 	sub	r3, r3, #1
31 	ldr	r2, [fp, #-20]
31 	cmp	r2, r3
31 	bne	.L20
0 .L19:
10 	ldr	r3, [fp, #-32]
10 	sub	r3, r3, #1
10 	ldr	r2, [fp, #-20]
10 	cmp	r2, r3
10 	beq	.L21
0 	ldr	r3, [fp, #-16]
0 	and	r3, r3, #1
0 	cmp	r3, #0
0 	bne	.L21
0 	mov	r3, #0
0 	b	.L13
0 .L21:
10 	ldr	r3, [fp, #-8]
10 	add	r3, r3, #1
10 	str	r3, [fp, #-8]
0 .L17:
11 	ldr	r2, [fp, #-8]
11 	ldr	r3, [fp, #-36]
11 	cmp	r2, r3
11 	blt	.L22
1 	mov	r3, #1
0 .L13:
1 	mov	r0, r3
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
0 	.size	Miller, .-Miller
0 	.align	2
0 	.global	swap
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	swap, %function
0 swap:
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 1, uses_anonymous_args = 0
0 	@ link register save eliminated.
25 	str	fp, [sp, #-4]!
25 	add	fp, sp, #0
25 	sub	sp, sp, #28
25 	str	r0, [fp, #-16]
25 	str	r1, [fp, #-20]
25 	str	r2, [fp, #-24]
25 	ldr	r3, [fp, #-20]
25 	lsl	r3, r3, #2
25 	ldr	r2, [fp, #-16]
25 	add	r3, r2, r3
25 	ldr	r3, [r3]
25 	str	r3, [fp, #-8]
25 	ldr	r3, [fp, #-24]
25 	lsl	r3, r3, #2
25 	ldr	r2, [fp, #-16]
25 	add	r2, r2, r3
25 	ldr	r3, [fp, #-20]
25 	lsl	r3, r3, #2
25 	ldr	r1, [fp, #-16]
25 	add	r3, r1, r3
25 	ldr	r2, [r2]
25 	str	r2, [r3]
25 	ldr	r3, [fp, #-24]
25 	lsl	r3, r3, #2
25 	ldr	r2, [fp, #-16]
25 	add	r3, r2, r3
25 	ldr	r2, [fp, #-8]
25 	str	r2, [r3]
25 	nop
25 	add	sp, fp, #0
0 	@ sp needed
25 	ldr	fp, [sp], #4
25 	bx	lr
0 	.size	swap, .-swap
0 	.align	2
0 	.global	heapify
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	heapify, %function
0 heapify:
0 	@ args = 0, pretend = 0, frame = 32
0 	@ frame_needed = 1, uses_anonymous_args = 0
30 	push	{fp, lr}
30 	add	fp, sp, #4
30 	sub	sp, sp, #32
30 	str	r0, [fp, #-24]
30 	str	r1, [fp, #-28]
30 	str	r2, [fp, #-32]
30 	ldr	r3, [fp, #-32]
30 	str	r3, [fp, #-8]
30 	ldr	r3, [fp, #-32]
30 	lsl	r3, r3, #1
30 	add	r3, r3, #1
30 	str	r3, [fp, #-12]
30 	ldr	r3, [fp, #-32]
30 	add	r3, r3, #1
30 	lsl	r3, r3, #1
30 	str	r3, [fp, #-16]
30 	ldr	r3, [fp, #-12]
30 	ldr	r2, [fp, #-28]
30 	cmp	r2, r3
30 	bls	.L25
19 	ldr	r3, [fp, #-8]
19 	lsl	r3, r3, #2
19 	ldr	r2, [fp, #-24]
19 	add	r3, r2, r3
19 	ldr	r2, [r3]
19 	ldr	r3, [fp, #-12]
19 	lsl	r3, r3, #2
19 	ldr	r1, [fp, #-24]
19 	add	r3, r1, r3
19 	ldr	r3, [r3]
19 	cmp	r2, r3
19 	bcs	.L25
11 	ldr	r3, [fp, #-12]
11 	str	r3, [fp, #-8]
0 .L25:
30 	ldr	r3, [fp, #-16]
30 	ldr	r2, [fp, #-28]
30 	cmp	r2, r3
30 	bls	.L26
17 	ldr	r3, [fp, #-8]
17 	lsl	r3, r3, #2
17 	ldr	r2, [fp, #-24]
17 	add	r3, r2, r3
17 	ldr	r2, [r3]
17 	ldr	r3, [fp, #-16]
17 	lsl	r3, r3, #2
17 	ldr	r1, [fp, #-24]
17 	add	r3, r1, r3
17 	ldr	r3, [r3]
17 	cmp	r2, r3
17 	bcs	.L26
7 	ldr	r3, [fp, #-16]
7 	str	r3, [fp, #-8]
0 .L26:
30 	ldr	r2, [fp, #-8]
30 	ldr	r3, [fp, #-32]
30 	cmp	r2, r3
30 	beq	.L28
16 	ldr	r3, [fp, #-8]
16 	ldr	r2, [fp, #-32]
16 	mov	r1, r3
16 	ldr	r0, [fp, #-24]
16 	bl	swap
16 	ldr	r2, [fp, #-8]
16 	ldr	r1, [fp, #-28]
16 	ldr	r0, [fp, #-24]
16 	bl	heapify
0 .L28:
30 	nop
30 	sub	sp, fp, #4
0 	@ sp needed
30 	pop	{fp, pc}
0 	.size	heapify, .-heapify
0 	.align	2
0 	.global	heapSort
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	heapSort, %function
0 heapSort:
0 	@ args = 0, pretend = 0, frame = 16
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #16
1 	str	r0, [fp, #-16]
1 	str	r1, [fp, #-20]
1 	ldr	r3, [fp, #-20]
1 	lsr	r3, r3, #1
1 	sub	r3, r3, #1
1 	str	r3, [fp, #-8]
1 	b	.L30
0 .L31:
5 	ldr	r2, [fp, #-8]
5 	ldr	r1, [fp, #-20]
5 	ldr	r0, [fp, #-16]
5 	bl	heapify
5 	ldr	r3, [fp, #-8]
5 	sub	r3, r3, #1
5 	str	r3, [fp, #-8]
0 .L30:
6 	ldr	r3, [fp, #-8]
6 	cmp	r3, #0
6 	bge	.L31
1 	mov	r3, #0
1 	str	r3, [fp, #-12]
1 	b	.L32
0 .L33:
9 	ldr	r3, [fp, #-12]
9 	ldr	r2, [fp, #-20]
9 	sub	r3, r2, r3
9 	sub	r3, r3, #1
9 	mov	r2, r3
9 	mov	r1, #0
9 	ldr	r0, [fp, #-16]
9 	bl	swap
9 	ldr	r3, [fp, #-12]
9 	ldr	r2, [fp, #-20]
9 	sub	r3, r2, r3
9 	sub	r3, r3, #1
9 	mov	r2, #0
9 	mov	r1, r3
9 	ldr	r0, [fp, #-16]
9 	bl	heapify
9 	ldr	r3, [fp, #-12]
9 	add	r3, r3, #1
9 	str	r3, [fp, #-12]
0 .L32:
10 	ldr	r3, [fp, #-20]
10 	sub	r2, r3, #1
10 	ldr	r3, [fp, #-12]
10 	cmp	r2, r3
10 	bhi	.L33
1 	nop
1 	nop
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
0 	.size	heapSort, .-heapSort
0 	.section	.rodata
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
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #24
1 	str	r0, [fp, #-24]
1 	mov	r1, #10
1 	ldr	r0, [fp, #-24]
1 	bl	heapSort
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	b	.L35
0 .L36:
10 	ldr	r1, [fp, #-8]
10 	movw	r0, #:lower16:.LC1
10 	movt	r0, #:upper16:.LC1
10 	bl	printf
10 	ldr	r3, [fp, #-8]
10 	lsl	r3, r3, #2
10 	ldr	r2, [fp, #-24]
10 	add	r3, r2, r3
10 	ldr	r3, [r3]
10 	mov	r1, r3
10 	movw	r0, #:lower16:.LC2
10 	movt	r0, #:upper16:.LC2
10 	bl	printf
10 	ldr	r3, [fp, #-8]
10 	add	r3, r3, #1
10 	str	r3, [fp, #-8]
0 .L35:
11 	ldr	r3, [fp, #-8]
11 	cmp	r3, #9
11 	ble	.L36
1 	mov	r3, #0
1 	str	r3, [fp, #-12]
1 	mov	r3, #0
1 	str	r3, [fp, #-16]
1 	b	.L37
0 .L41:
10 	ldr	r1, [fp, #-16]
10 	movw	r3, #21846
10 	movt	r3, 21845
10 	smull	r3, r2, r3, r1
10 	asr	r3, r1, #31
10 	sub	r2, r2, r3
10 	mov	r3, r2
10 	lsl	r3, r3, #1
10 	add	r3, r3, r2
10 	sub	r2, r1, r3
10 	cmp	r2, #0
10 	beq	.L38
6 	ldr	r3, [fp, #-16]
6 	lsl	r3, r3, #2
6 	ldr	r2, [fp, #-24]
6 	add	r3, r2, r3
6 	ldr	r2, [r3]
6 	ldr	r3, [fp, #-12]
6 	mul	r3, r2, r3
6 	str	r3, [fp, #-12]
0 .L38:
10 	ldr	r3, [fp, #-16]
10 	and	r3, r3, #1
10 	cmp	r3, #0
10 	bne	.L39
5 	ldr	r3, [fp, #-16]
5 	lsl	r3, r3, #2
5 	ldr	r2, [fp, #-24]
5 	add	r3, r2, r3
5 	ldr	r3, [r3]
5 	ldr	r2, [fp, #-12]
5 	add	r3, r2, r3
5 	str	r3, [fp, #-12]
5 	b	.L40
0 .L39:
5 	ldr	r3, [fp, #-16]
5 	lsl	r3, r3, #2
5 	ldr	r2, [fp, #-24]
5 	add	r3, r2, r3
5 	ldr	r3, [r3]
5 	ldr	r2, [fp, #-12]
5 	sub	r3, r2, r3
5 	str	r3, [fp, #-12]
0 .L40:
10 	ldr	r3, [fp, #-16]
10 	add	r3, r3, #1
10 	str	r3, [fp, #-16]
0 .L37:
11 	ldr	r3, [fp, #-16]
11 	cmp	r3, #9
11 	ble	.L41
1 	ldr	r3, [fp, #-12]
1 	mov	r0, r3
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
0 	.size	test, .-test
0 	.align	2
0 	.global	fib
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	fib, %function
0 fib:
0 	@ args = 0, pretend = 0, frame = 8
0 	@ frame_needed = 1, uses_anonymous_args = 0
7049155 	push	{r4, fp, lr}
7049155 	add	fp, sp, #8
7049155 	sub	sp, sp, #12
7049155 	str	r0, [fp, #-16]
7049155 	ldr	r3, [fp, #-16]
7049155 	cmp	r3, #1
7049155 	bgt	.L44
3524578 	ldr	r3, [fp, #-16]
3524578 	b	.L45
0 .L44:
3524577 	ldr	r3, [fp, #-16]
3524577 	sub	r3, r3, #1
3524577 	mov	r0, r3
3524577 	bl	fib
3524577 	mov	r4, r0
3524577 	ldr	r3, [fp, #-16]
3524577 	sub	r3, r3, #2
3524577 	mov	r0, r3
3524577 	bl	fib
3524577 	mov	r3, r0
3524577 	add	r3, r4, r3
0 .L45:
7049155 	mov	r0, r3
7049155 	sub	sp, fp, #8
0 	@ sp needed
7049155 	pop	{r4, fp, pc}
0 	.size	fib, .-fib
0 	.section	.rodata
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
0 	.align	2
0 .LC0:
0 	.word	1
0 	.word	34
0 	.word	6
0 	.word	2
0 	.word	6
0 	.word	2
0 	.word	7
0 	.word	2
0 	.word	17
0 	.word	7
0 	.text
0 	.align	2
0 	.global	main
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	main, %function
0 main:
0 	@ args = 0, pretend = 0, frame = 56
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #56
1 	movw	r3, #:lower16:.LC0
1 	movt	r3, #:upper16:.LC0
1 	sub	ip, fp, #56
1 	mov	lr, r3
1 	ldmia	lr!, {r0, r1, r2, r3}
1 	stmia	ip!, {r0, r1, r2, r3}
1 	ldmia	lr!, {r0, r1, r2, r3}
1 	stmia	ip!, {r0, r1, r2, r3}
1 	ldm	lr, {r0, r1}
1 	stm	ip, {r0, r1}
1 	sub	r3, fp, #56
1 	mov	r0, r3
1 	bl	test
1 	str	r0, [fp, #-16]
1 	ldr	r3, [fp, #-16]
1 	mul	r3, r3, r3
1 	ldr	r2, [fp, #-16]
1 	mul	r3, r2, r3
1 	ldr	r2, [fp, #-16]
1 	mul	r3, r2, r3
1 	ldr	r2, [fp, #-16]
1 	mul	r3, r2, r3
1 	ldr	r2, [fp, #-16]
1 	mul	r2, r2, r3
1 	ldr	r3, [fp, #-16]
1 	mul	r3, r2, r3
1 	str	r3, [fp, #-16]
1 	ldr	r1, [fp, #-16]
1 	movw	r0, #:lower16:.LC3
1 	movt	r0, #:upper16:.LC3
1 	bl	printf
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	ldr	r3, [fp, #-16]
1 	str	r3, [fp, #-12]
1 	b	.L47
0 .L48:
10 	ldr	r2, [fp, #-12]
10 	movw	r3, #26215
10 	movt	r3, 26214
10 	smull	r1, r3, r3, r2
10 	asr	r1, r3, #2
10 	asr	r3, r2, #31
10 	sub	r3, r1, r3
10 	mov	r1, #10
10 	mul	r3, r1, r3
10 	sub	r3, r2, r3
10 	ldr	r2, [fp, #-8]
10 	add	r3, r2, r3
10 	str	r3, [fp, #-8]
10 	ldr	r2, [fp, #-12]
10 	movw	r3, #26215
10 	movt	r3, 26214
10 	smull	r1, r3, r3, r2
10 	asr	r1, r3, #2
10 	asr	r3, r2, #31
10 	sub	r3, r1, r3
10 	str	r3, [fp, #-12]
0 .L47:
11 	ldr	r3, [fp, #-12]
11 	cmp	r3, #0
11 	bne	.L48
1 	ldr	r1, [fp, #-8]
1 	movw	r0, #:lower16:.LC4
1 	movt	r0, #:upper16:.LC4
1 	bl	printf
1 	ldr	r3, [fp, #-8]
1 	mul	r3, r3, r3
1 	mov	r1, r3
1 	ldr	r0, [fp, #-16]
1 	bl	__aeabi_idiv
1 	mov	r3, r0
1 	str	r3, [fp, #-16]
1 	ldr	r1, [fp, #-16]
1 	movw	r0, #:lower16:.LC5
1 	movt	r0, #:upper16:.LC5
1 	bl	printf
1 	ldr	r0, [fp, #-8]
1 	bl	fib
1 	mov	r3, r0
1 	ldr	r1, [fp, #-8]
1 	mov	r0, r3
1 	bl	__aeabi_idiv
1 	mov	r3, r0
1 	mov	r1, r3
1 	ldr	r0, [fp, #-16]
1 	bl	__aeabi_idiv
1 	mov	r3, r0
1 	str	r3, [fp, #-16]
1 	mov	r1, #10
1 	ldr	r0, [fp, #-16]
1 	bl	Miller
1 	mov	r3, r0
1 	cmp	r3, #0
1 	beq	.L49
1 	ldr	r1, [fp, #-16]
1 	movw	r0, #:lower16:.LC6
1 	movt	r0, #:upper16:.LC6
1 	bl	printf
1 	b	.L50
0 .L49:
0 	ldr	r1, [fp, #-16]
0 	movw	r0, #:lower16:.LC7
0 	movt	r0, #:upper16:.LC7
0 	bl	printf
0 .L50:
1 	ldr	r1, [fp, #-16]
1 	movw	r0, #:lower16:.LC8
1 	movt	r0, #:upper16:.LC8
1 	bl	printf
1 	mov	r3, #0
1 	mov	r0, r3
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
