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
	.file	"test.c"
	.text
	.global	__aeabi_idivmod
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	Miller.part.0, %function
Miller.part.0:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}


	tst	r0, #1
	
	sub	sp, sp, #12
	sub	r8, r0, #1
	mov	fp, r0
	mov	r9, r8
	str	r1, [sp, #4]
	beq	.L2
.L3:
	asr	r9, r9, #1
	tst	r9, #1
	beq	.L3
.L2:
	ldr	r3, [sp, #4]
	cmp	r3, #0
	movgt	r3, #0
	strgt	r3, [sp]
	ble	.L14
.L4:
	bl	rand
	mov	r1, r8
	bl	__aeabi_idivmod
	mov	r6, r9
	mov	r5, #1
	add	r4, r1, #1
.L7:
	tst	r6, #1
	mov	r1, fp
	mul	r0, r4, r5
	beq	.L6
	bl	__aeabi_idivmod
	mov	r5, r1
.L6:
	mul	r0, r4, r4
	mov	r1, fp
	bl	__aeabi_idivmod
	asrs	r6, r6, #1
	mov	r4, r1
	bne	.L7
	mov	r0, r5
	mov	r1, fp
	bl	__aeabi_idivmod
	cmp	r8, r9
	mov	r10, r1
	beq	.L18
	cmp	r1, #1
	beq	.L19
	cmp	r8, r1
	beq	.L9
	mov	r7, r9
.L13:
	mov	r1, fp
	mov	r0, r10
	bl	__aeabi_idivmod
	cmp	r10, #0
	lsl	r7, r7, #1
	mov	r4, r1
	ble	.L10
	mov	r5, #0
.L12:
	tst	r10, #1
	add	r0, r5, r4
	mov	r1, fp
	beq	.L11
	bl	__aeabi_idivmod
	mov	r5, r1
.L11:
	lsl	r0, r4, #1
	mov	r1, fp
	bl	__aeabi_idivmod
	asrs	r10, r10, #1
	mov	r4, r1
	bne	.L12
	mov	r0, r5
	mov	r1, fp
	bl	__aeabi_idivmod
	cmp	r8, r7
	mov	r10, r1
	beq	.L8
	cmp	r1, #1
	beq	.L8
	cmp	r8, r1
	bne	.L13
.L9:
	ldr	r3, [sp]
	ldr	r2, [sp, #4]
	add	r3, r3, #1
	str	r3, [sp]
	cmp	r3, r2
	bne	.L4
.L14:
	mov	r6, #1
.L1:
	mov	r0, r6
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L41:
	lsl	r7, r7, #1
.L10:
	cmp	r8, r7
	bne	.L41
	tst	r7, #1
	bne	.L9
	b	.L1
.L19:
	mov	r7, r9
.L8:
	cmp	r8, r10
	beq	.L9
.L42:
	tst	r7, #1
	bne	.L9
	b	.L1
.L18:
	cmp	r8, r10
	mov	r7, r8
	bne	.L42
	b	.L9
	.size	Miller.part.0, .-Miller.part.0
	.align	2
	.global	mulmod
	.syntax unified
	.arm
	.fpu softvfp
	.type	mulmod, %function
mulmod:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r5, r1
	mov	r1, r2
	mov	r7, r2
	bl	__aeabi_idivmod
	cmp	r5, #0
	ble	.L47
	mov	r4, r1
	mov	r6, #0
.L46:
	tst	r5, #1
	add	r0, r6, r4
	mov	r1, r7
	beq	.L45
	bl	__aeabi_idivmod
	mov	r6, r1
.L45:
	lsl	r0, r4, #1
	mov	r1, r7
	bl	__aeabi_idivmod
	asrs	r5, r5, #1
	mov	r4, r1
	bne	.L46
	mov	r1, r7
	mov	r0, r6
	bl	__aeabi_idivmod
	mov	r0, r1
	pop	{r4, r5, r6, r7, r8, pc}
.L47:
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	mulmod, .-mulmod
	.align	2
	.global	modulo
	.syntax unified
	.arm
	.fpu softvfp
	.type	modulo, %function
modulo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	subs	r5, r1, #0
	mov	r7, r2
	ble	.L57
	mov	r4, r0
	mov	r6, #1
.L56:
	tst	r5, #1
	mov	r1, r7
	mul	r0, r4, r6
	beq	.L55
	bl	__aeabi_idivmod
	mov	r6, r1
.L55:
	mul	r0, r4, r4
	mov	r1, r7
	bl	__aeabi_idivmod
	asrs	r5, r5, #1
	mov	r4, r1
	bne	.L56
.L54:
	mov	r1, r7
	mov	r0, r6
	bl	__aeabi_idivmod
	mov	r0, r1
	pop	{r4, r5, r6, r7, r8, pc}
.L57:
	mov	r6, #1
	b	.L54
	.size	modulo, .-modulo
	.align	2
	.global	Miller
	.syntax unified
	.arm
	.fpu softvfp
	.type	Miller, %function
Miller:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r0, #1
	ble	.L63
	cmp	r0, #2
	beq	.L65
	tst	r0, #1
	beq	.L63
.L65:
	b	Miller.part.0
.L63:
	mov	r0, #0
	bx	lr
	.size	Miller, .-Miller
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
	ldr	r3, [r0, r1, lsl #2]
	ldr	ip, [r0, r2, lsl #2]
	str	ip, [r0, r1, lsl #2]
	str	r3, [r0, r2, lsl #2]
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	heapify
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapify, %function
heapify:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	b	.L77
.L82:
	ldr	lr, [r0, ip, lsl #2]
	ldr	r4, [r0, r2, lsl #2]
	cmp	r4, lr
	bcs	.L74
	cmp	r1, r3
	movls	r3, ip
	bhi	.L81
.L75:
	cmp	r3, r2
	popeq	{r4, pc}
.L83:
	ldr	lr, [r0, r2, lsl #2]
	ldr	ip, [r0, r3, lsl #2]
	str	lr, [r0, r3, lsl #2]
	str	ip, [r0, r2, lsl #2]
	mov	r2, r3
.L77:
	lsl	r3, r2, #1
	add	ip, r3, #1
	add	r3, r3, #2
	cmp	ip, r1
	bcc	.L82
.L74:
	cmp	r1, r3
	popls	{r4, pc}
	ldr	lr, [r0, r2, lsl #2]
	ldr	ip, [r0, r3, lsl #2]
	cmp	lr, ip
	popcs	{r4, pc}
	cmp	r3, r2
	bne	.L83
	pop	{r4, pc}
.L81:
	ldr	r4, [r0, r3, lsl #2]
	cmp	lr, r4
	movcs	r3, ip
	b	.L75
	.size	heapify, .-heapify
	.align	2
	.global	heapSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapSort, %function
heapSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	lsr	r4, r1, #1
	cmp	r4, #0
	beq	.L85
	sub	r4, r4, #1
.L86:
	mov	r2, r4
	sub	r4, r4, #1
	bl	heapify
	cmn	r4, #1
	bne	.L86
.L85:
	subs	r5, r1, #1
	popeq	{r4, r5, r6, pc}
	add	r4, r0, r1, lsl #2
	add	r6, r0, #4
.L88:
	ldr	ip, [r4, #-4]!
	mov	r1, r5
	ldr	r3, [r0]
	mov	r2, #0
	sub	r5, r5, #1
	str	ip, [r0]
	str	r3, [r4]
	bl	heapify
	cmp	r6, r4
	bne	.L88
	pop	{r4, r5, r6, pc}
	.size	heapSort, .-heapSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"array[%d]: \000"
	.align	2
.LC2:
	.ascii	"%d\012\000"
	.text
	.align	2
	.global	test
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r1, #10
	mov	r5, r0
	bl	heapSort
	movw	r8, #:lower16:.LC1
	movw	r7, #:lower16:.LC2
	movt	r8, #:upper16:.LC1
	movt	r7, #:upper16:.LC2
	mov	r4, #0
	sub	r6, r0, #4
.L99:
	mov	r2, r4
	mov	r1, r8
	mov	r0, #1
	add	r4, r4, r0
	bl	__printf_chk
	ldr	r2, [r6, #4]!
	mov	r1, r7
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, #10
	bne	.L99
	ldr	r1, [r5]
	mov	r3, #0
	movw	lr, #43691
	movw	r4, #21845
	movt	lr, 43690
	movt	r4, 21845
	mov	r0, r3
	mov	r2, r5
.L100:
	tst	r3, #1
	add	r3, r3, #1
	subne	r0, r0, r1
	ldreq	r1, [r2]
	mul	ip, lr, r3
	addeq	r0, r0, r1
	cmp	r3, #10
	popeq	{r4, r5, r6, r7, r8, pc}
	ldr	r1, [r2, #4]!
	cmp	ip, r4
	mulhi	r0, r1, r0
	b	.L100
	.size	test, .-test
	.align	2
	.global	fib
	.syntax unified
	.arm
	.fpu softvfp
	.type	fib, %function
fib:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r0, #1
	bxle	lr
	push	{r4, r5, r6, r7, r8, lr}
	sub	r7, r0, #2
	sub	r6, r0, #3
	bic	r3, r7, #1
	sub	r5, r0, #1
	sub	r6, r6, r3
	mov	r4, #0
.L110:
	mov	r0, r5
	sub	r5, r5, #2
	bl	fib
	cmp	r5, r6
	add	r4, r4, r0
	bne	.L110
	and	r0, r7, #1
	add	r0, r0, r4
	pop	{r4, r5, r6, r7, r8, pc}
	.size	fib, .-fib
	.section	.rodata.str1.4
	.align	2
.LC3:
	.ascii	"tmp: %d\012\000"
	.align	2
.LC4:
	.ascii	"crossSum: %d\012\000"
	.global	__aeabi_idiv
	.align	2
.LC5:
	.ascii	"tmp2: %d\012\000"
	.align	2
.LC6:
	.ascii	"%d is prime\012\000"
	.align	2
.LC7:
	.ascii	"%d is not prime\012\000"
	.align	2
.LC8:
	.ascii	"Ergebnis: %d\012\000"
	.global	__aeabi_uidiv
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, r7, lr}
	sub	sp, sp, #44
	ldmia	ip!, {r0, r1, r2, r3}
	mov	lr, sp
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldm	ip, {r0, r1}
	stm	lr, {r0, r1}
	mov	r0, sp
	bl	test
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	mul	r6, r0, r0
	mov	r3, r0
	mov	r0, #1
	mul	r6, r6, r3
	mul	r6, r6, r6
	mul	r6, r3, r6
	mov	r2, r6
	bl	__printf_chk
	cmp	r6, #0
	beq	.L118
	movw	r1, #26215
	movt	r1, 26214
	mov	r4, r6
	mov	r5, #0
	mov	r0, #10
.L119:
	smull	r3, r2, r1, r4
	asr	r3, r4, #31
	rsb	r3, r3, r2, asr #2
	mls	r2, r0, r3, r4
	subs	r4, r3, #0
	add	r5, r5, r2
	bne	.L119
	mov	r2, r5
	movw	r1, #:lower16:.LC4
	mov	r0, #1
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
	mul	r1, r5, r5
	mov	r0, r6
	bl	__aeabi_idiv
	movw	r1, #:lower16:.LC5
	movt	r1, #:upper16:.LC5
	mov	r2, r0
	mov	r6, r0
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, #1
	ble	.L141
	sub	r7, r5, #2
	sub	r1, r5, #3
	bic	r3, r7, #1
	sub	r2, r5, #1
	sub	r1, r1, r3
.L123:
	mov	r0, r2
	sub	r2, r2, #2
	bl	fib
	cmp	r2, r1
	add	r4, r4, r0
	bne	.L123
	and	r0, r7, #1
.L124:
	add	r0, r4, r0
	mov	r1, r5
	bl	__aeabi_idiv
	mov	r1, r0
	mov	r0, r6
	bl	__aeabi_idiv
	cmp	r0, #1
	mov	r4, r0
	ble	.L121
	cmp	r0, #2
	beq	.L125
	tst	r0, #1
	beq	.L121
.L125:
	mov	r1, #10
	mov	r0, r4
	bl	Miller.part.0
	cmp	r0, #0
	bne	.L142
.L121:
	movw	r1, #:lower16:.LC7
	mov	r2, r4
	movt	r1, #:upper16:.LC7
	mov	r0, #1
	bl	__printf_chk
.L126:
	mov	r2, r4
	movw	r1, #:lower16:.LC8
	mov	r0, #1
	movt	r1, #:upper16:.LC8
	bl	__printf_chk
	mov	r0, #0
	add	sp, sp, #44
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L142:
	movw	r1, #:lower16:.LC6
	mov	r2, r4
	movt	r1, #:upper16:.LC6
	mov	r0, #1
	bl	__printf_chk
	b	.L126
.L141:
	mov	r0, r5
	b	.L124
.L118:
	mov	r2, r6
	movw	r1, #:lower16:.LC4
	mov	r0, #1
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
	mov	r1, r6
	mov	r0, r6
	bl	__aeabi_idiv
	movw	r1, #:lower16:.LC5
	movt	r1, #:upper16:.LC5
	mov	r2, r0
	mov	r0, #1
	bl	__printf_chk
	.inst	0xe7f000f0
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	1
	.word	34
	.word	6
	.word	2
	.word	6
	.word	2
	.word	7
	.word	2
	.word	17
	.word	7
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
