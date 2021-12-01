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
	.file	"naive_search.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"--Pattern is found at: %d\012\000"
	.text
	.align	2
	.global	naive_search
	.syntax unified
	.arm
	.fpu softvfp
	.type	naive_search, %function
naive_search:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	ldr	r0, [fp, #-24]
	bl	strlen
	mov	r3, r0
	str	r3, [fp, #-16]
	ldr	r0, [fp, #-28]
	bl	strlen
	mov	r3, r0
	str	r3, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L2
.L8:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L3
.L6:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r3, r2, r3
	mov	r2, r3
	ldr	r3, [fp, #-24]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, [fp, #-12]
	ldr	r1, [fp, #-28]
	add	r3, r1, r3
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r2, r3
	bne	.L9
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L3:
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-20]
	cmp	r2, r3
	blt	.L6
	b	.L5
.L9:
	nop
.L5:
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-20]
	cmp	r2, r3
	bne	.L7
	ldr	r1, [fp, #-8]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
.L7:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-20]
	sub	r3, r2, r3
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	ble	.L8
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	naive_search, .-naive_search
	.section	.rodata
	.align	2
.LC3:
	.ascii	"String test: %s\012\000"
	.align	2
.LC4:
	.ascii	"Test1: search pattern %s\012\000"
	.align	2
.LC5:
	.ascii	"Test2: search pattern %s\012\000"
	.align	2
.LC6:
	.ascii	"Test3: search pattern %s\012\000"
	.align	2
.LC1:
	.ascii	"AABCAB12AFAABCABFFEGABCAB\000"
	.align	2
.LC2:
	.ascii	"ABCAB\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #48
	movw	r3, #:lower16:.LC1
	movt	r3, #:upper16:.LC1
	sub	ip, fp, #32
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1, r2}
	stmia	ip!, {r0, r1}
	strh	r2, [ip]	@ movhi
	movw	r2, #:lower16:.LC2
	movt	r2, #:upper16:.LC2
	sub	r3, fp, #40
	ldm	r2, {r0, r1}
	str	r0, [r3]
	add	r3, r3, #4
	strh	r1, [r3]	@ movhi
	movw	r3, #17990
	movt	r3, 70
	str	r3, [fp, #-44]
	movw	r3, #16707
	movt	r3, 66
	str	r3, [fp, #-48]
	sub	r3, fp, #32
	mov	r1, r3
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	printf
	sub	r3, fp, #40
	mov	r1, r3
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	printf
	sub	r2, fp, #40
	sub	r3, fp, #32
	mov	r1, r2
	mov	r0, r3
	bl	naive_search
	sub	r3, fp, #44
	mov	r1, r3
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	printf
	sub	r2, fp, #44
	sub	r3, fp, #32
	mov	r1, r2
	mov	r0, r3
	bl	naive_search
	sub	r3, fp, #48
	mov	r1, r3
	movw	r0, #:lower16:.LC6
	movt	r0, #:upper16:.LC6
	bl	printf
	sub	r2, fp, #48
	sub	r3, fp, #32
	mov	r1, r2
	mov	r0, r3
	bl	naive_search
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
