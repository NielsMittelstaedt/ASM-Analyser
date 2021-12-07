	.arch armv7-a
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"test.c"
	.text
	.global	__aeabi_idivmod
	.align	2
	.global	mulmod
	.syntax unified
	.arm
	.fpu softvfp
	.type	mulmod, %function
mulmod:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	mov	r3, #0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	ldr	r1, [fp, #-24]
	mov	r0, r3
	bl	__aeabi_idivmod
	mov	r3, r1
	str	r3, [fp, #-12]
	b	.L2
.L4:
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	and	r3, r3, #1
	rsblt	r3, r3, #0
	cmp	r3, #1
	bne	.L3
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r3, r2, r3
	ldr	r1, [fp, #-24]
	mov	r0, r3
	bl	__aeabi_idivmod
	mov	r3, r1
	str	r3, [fp, #-8]
.L3:
	ldr	r3, [fp, #-12]
	lsl	r3, r3, #1
	ldr	r1, [fp, #-24]
	mov	r0, r3
	bl	__aeabi_idivmod
	mov	r3, r1
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-20]
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	str	r3, [fp, #-20]
.L2:
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	bgt	.L4
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-24]
	mov	r0, r3
	bl	__aeabi_idivmod
	mov	r3, r1
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	mulmod, .-mulmod
	.align	2
	.global	modulo
	.syntax unified
	.arm
	.fpu softvfp
	.type	modulo, %function
modulo:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	mov	r3, #1
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-12]
	b	.L7
.L9:
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	and	r3, r3, #1
	rsblt	r3, r3, #0
	cmp	r3, #1
	bne	.L8
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-12]
	mul	r3, r2, r3
	ldr	r1, [fp, #-24]
	mov	r0, r3
	bl	__aeabi_idivmod
	mov	r3, r1
	str	r3, [fp, #-8]
.L8:
	ldr	r3, [fp, #-12]
	mul	r3, r3, r3
	ldr	r1, [fp, #-24]
	mov	r0, r3
	bl	__aeabi_idivmod
	mov	r3, r1
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-20]
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	str	r3, [fp, #-20]
.L7:
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	bgt	.L9
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-24]
	mov	r0, r3
	bl	__aeabi_idivmod
	mov	r3, r1
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	modulo, .-modulo
	.align	2
	.global	Miller
	.syntax unified
	.arm
	.fpu softvfp
	.type	Miller, %function
Miller:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #32
	str	r0, [fp, #-32]
	str	r1, [fp, #-36]
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	bgt	.L12
	mov	r3, #0
	b	.L13
.L12:
	ldr	r3, [fp, #-32]
	cmp	r3, #2
	beq	.L14
	ldr	r3, [fp, #-32]
	and	r3, r3, #1
	cmp	r3, #0
	bne	.L14
	mov	r3, #0
	b	.L13
.L14:
	ldr	r3, [fp, #-32]
	sub	r3, r3, #1
	str	r3, [fp, #-12]
	b	.L15
.L16:
	ldr	r3, [fp, #-12]
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	str	r3, [fp, #-12]
.L15:
	ldr	r3, [fp, #-12]
	and	r3, r3, #1
	cmp	r3, #0
	beq	.L16
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L17
.L22:
	bl	rand
	mov	r2, r0
	ldr	r3, [fp, #-32]
	sub	r3, r3, #1
	mov	r1, r3
	mov	r0, r2
	bl	__aeabi_idivmod
	mov	r3, r1
	add	r3, r3, #1
	str	r3, [fp, #-24]
	ldr	r3, [fp, #-12]
	str	r3, [fp, #-16]
	ldr	r2, [fp, #-32]
	ldr	r1, [fp, #-16]
	ldr	r0, [fp, #-24]
	bl	modulo
	str	r0, [fp, #-20]
	b	.L18
.L20:
	ldr	r2, [fp, #-32]
	ldr	r1, [fp, #-20]
	ldr	r0, [fp, #-20]
	bl	mulmod
	str	r0, [fp, #-20]
	ldr	r3, [fp, #-16]
	lsl	r3, r3, #1
	str	r3, [fp, #-16]
.L18:
	ldr	r3, [fp, #-32]
	sub	r3, r3, #1
	ldr	r2, [fp, #-16]
	cmp	r2, r3
	beq	.L19
	ldr	r3, [fp, #-20]
	cmp	r3, #1
	beq	.L19
	ldr	r3, [fp, #-32]
	sub	r3, r3, #1
	ldr	r2, [fp, #-20]
	cmp	r2, r3
	bne	.L20
.L19:
	ldr	r3, [fp, #-32]
	sub	r3, r3, #1
	ldr	r2, [fp, #-20]
	cmp	r2, r3
	beq	.L21
	ldr	r3, [fp, #-16]
	and	r3, r3, #1
	cmp	r3, #0
	bne	.L21
	mov	r3, #0
	b	.L13
.L21:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L17:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-36]
	cmp	r2, r3
	blt	.L22
	mov	r3, #1
.L13:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	Miller, .-Miller
	.align	2
	.global	swap
	.syntax unified
	.arm
	.fpu softvfp
	.type	swap, %function
swap:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-24]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r2, r2, r3
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r1, [fp, #-16]
	add	r3, r1, r3
	ldr	r2, [r2]
	str	r2, [r3]
	ldr	r3, [fp, #-24]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r2, [fp, #-8]
	str	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	heapify
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapify, %function
heapify:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #32
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	str	r2, [fp, #-32]
	ldr	r3, [fp, #-32]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-32]
	lsl	r3, r3, #1
	add	r3, r3, #1
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-32]
	add	r3, r3, #1
	lsl	r3, r3, #1
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	bls	.L25
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-12]
	lsl	r3, r3, #2
	ldr	r1, [fp, #-24]
	add	r3, r1, r3
	ldr	r3, [r3]
	cmp	r2, r3
	bcs	.L25
	ldr	r3, [fp, #-12]
	str	r3, [fp, #-8]
.L25:
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	bls	.L26
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	lsl	r3, r3, #2
	ldr	r1, [fp, #-24]
	add	r3, r1, r3
	ldr	r3, [r3]
	cmp	r2, r3
	bcs	.L26
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-8]
.L26:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-32]
	cmp	r2, r3
	beq	.L28
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-32]
	mov	r1, r3
	ldr	r0, [fp, #-24]
	bl	swap
	ldr	r2, [fp, #-8]
	ldr	r1, [fp, #-28]
	ldr	r0, [fp, #-24]
	bl	heapify
.L28:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	heapify, .-heapify
	.align	2
	.global	heapSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapSort, %function
heapSort:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	ldr	r3, [fp, #-20]
	lsr	r3, r3, #1
	sub	r3, r3, #1
	str	r3, [fp, #-8]
	b	.L30
.L31:
	ldr	r2, [fp, #-8]
	ldr	r1, [fp, #-20]
	ldr	r0, [fp, #-16]
	bl	heapify
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-8]
.L30:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bge	.L31
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L32
.L33:
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-20]
	sub	r3, r2, r3
	sub	r3, r3, #1
	mov	r2, r3
	mov	r1, #0
	ldr	r0, [fp, #-16]
	bl	swap
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-20]
	sub	r3, r2, r3
	sub	r3, r3, #1
	mov	r2, #0
	mov	r1, r3
	ldr	r0, [fp, #-16]
	bl	heapify
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L32:
	ldr	r3, [fp, #-20]
	sub	r2, r3, #1
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bhi	.L33
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	heapSort, .-heapSort
	.align	2
	.global	test
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #64
	str	r0, [fp, #-64]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L35
.L36:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-64]
	add	r3, r2, r3
	ldr	r3, [r3]
	mov	r2, r3
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	sub	r1, fp, #4
	add	r3, r1, r3
	str	r2, [r3, #-56]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L35:
	ldr	r3, [fp, #-8]
	cmp	r3, #9
	ble	.L36
	sub	r3, fp, #60
	mov	r1, #10
	mov	r0, r3
	bl	heapSort
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L37
.L38:
	ldr	r3, [fp, #-12]
	lsl	r3, r3, #2
	sub	r2, fp, #4
	add	r3, r2, r3
	ldr	r1, [r3, #-56]
	ldr	r3, [fp, #-12]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-64]
	add	r3, r2, r3
	mov	r2, r1
	str	r2, [r3]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L37:
	ldr	r3, [fp, #-12]
	cmp	r3, #9
	ble	.L38
	mov	r3, #0
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-20]
	b	.L39
.L43:
	ldr	r1, [fp, #-20]
	movw	r3, #21846
	movt	r3, 21845
	smull	r3, r2, r3, r1
	asr	r3, r1, #31
	sub	r2, r2, r3
	mov	r3, r2
	lsl	r3, r3, #1
	add	r3, r3, r2
	sub	r2, r1, r3
	cmp	r2, #0
	beq	.L40
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-64]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	mul	r3, r2, r3
	str	r3, [fp, #-16]
.L40:
	ldr	r3, [fp, #-20]
	and	r3, r3, #1
	cmp	r3, #0
	bne	.L41
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-64]
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	str	r3, [fp, #-16]
	b	.L42
.L41:
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-64]
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-16]
	sub	r3, r2, r3
	str	r3, [fp, #-16]
.L42:
	ldr	r3, [fp, #-20]
	add	r3, r3, #1
	str	r3, [fp, #-20]
.L39:
	ldr	r3, [fp, #-20]
	cmp	r3, #9
	ble	.L43
	ldr	r3, [fp, #-16]
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	test, .-test
	.global	__aeabi_idiv
	.section	.rodata
	.align	2
.LC1:
	.ascii	"%d is prime\012\000"
	.align	2
.LC2:
	.ascii	"%d is not prime\012\000"
	.align	2
.LC3:
	.ascii	"Ergebnis: %d\012\000"
	.align	2
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
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #56
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	sub	ip, fp, #56
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1}
	stm	ip, {r0, r1}
	sub	r3, fp, #56
	mov	r0, r3
	bl	test
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	mul	r3, r3, r3
	ldr	r2, [fp, #-16]
	mul	r3, r2, r3
	ldr	r2, [fp, #-16]
	mul	r3, r2, r3
	ldr	r2, [fp, #-16]
	mul	r3, r2, r3
	ldr	r2, [fp, #-16]
	mul	r2, r2, r3
	ldr	r3, [fp, #-16]
	mul	r3, r2, r3
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-12]
	b	.L46
.L47:
	ldr	r2, [fp, #-12]
	movw	r3, #26215
	movt	r3, 26214
	smull	r1, r3, r3, r2
	asr	r1, r3, #2
	asr	r3, r2, #31
	sub	r3, r1, r3
	mov	r1, #10
	mul	r3, r1, r3
	sub	r3, r2, r3
	ldr	r2, [fp, #-8]
	add	r3, r2, r3
	str	r3, [fp, #-8]
	ldr	r2, [fp, #-12]
	movw	r3, #26215
	movt	r3, 26214
	smull	r1, r3, r3, r2
	asr	r1, r3, #2
	asr	r3, r2, #31
	sub	r3, r1, r3
	str	r3, [fp, #-12]
.L46:
	ldr	r3, [fp, #-12]
	cmp	r3, #0
	bne	.L47
	ldr	r3, [fp, #-8]
	mul	r3, r3, r3
	mov	r1, r3
	ldr	r0, [fp, #-16]
	bl	__aeabi_idiv
	mov	r3, r0
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-16]
	sub	r3, r3, #1
	str	r3, [fp, #-16]
	mov	r1, #10
	ldr	r0, [fp, #-16]
	bl	Miller
	mov	r3, r0
	cmp	r3, #0
	beq	.L48
	ldr	r1, [fp, #-16]
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	printf
	b	.L49
.L48:
	ldr	r1, [fp, #-16]
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	printf
.L49:
	ldr	r1, [fp, #-16]
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
