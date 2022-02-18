1.00 0 	.arch armv7-a
1.00 0 	.eabi_attribute 20, 1
1.00 0 	.eabi_attribute 21, 1
1.00 0 	.eabi_attribute 23, 3
1.00 0 	.eabi_attribute 24, 1
1.00 0 	.eabi_attribute 25, 1
1.00 0 	.eabi_attribute 26, 2
1.00 0 	.eabi_attribute 30, 6
1.00 0 	.eabi_attribute 34, 1
1.00 0 	.eabi_attribute 18, 4
1.00 0 	.file	"binary_search.c"
1.00 0 	.text
1.00 0 	.align	2
1.00 0 	.global	binarySearch
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	binarySearch, %function
1.00 0 binarySearch:
1.00 0 	@ args = 0, pretend = 0, frame = 24
1.00 0 	@ frame_needed = 1, uses_anonymous_args = 0
1.00 2 	push	{fp, lr}
1.00 2 	add	fp, sp, #4
1.00 2 	sub	sp, sp, #24
1.00 2 	str	r0, [fp, #-16]
1.00 2 	str	r1, [fp, #-20]
1.00 2 	str	r2, [fp, #-24]
1.00 2 	str	r3, [fp, #-28]
1.00 2 	ldr	r2, [fp, #-24]
1.00 2 	ldr	r3, [fp, #-20]
1.00 2 	cmp	r2, r3
1.00 2 	blt	.L2
1.00 2 	ldr	r2, [fp, #-24]
1.00 2 	ldr	r3, [fp, #-20]
1.00 2 	sub	r3, r2, r3
1.00 2 	lsr	r2, r3, #31
1.00 2 	add	r3, r2, r3
1.00 2 	asr	r3, r3, #1
1.00 2 	mov	r2, r3
1.00 2 	ldr	r3, [fp, #-20]
1.00 2 	add	r3, r3, r2
1.00 2 	str	r3, [fp, #-8]
1.00 2 	ldr	r3, [fp, #-8]
1.00 2 	lsl	r3, r3, #2
1.00 2 	ldr	r2, [fp, #-16]
1.00 2 	add	r3, r2, r3
1.00 2 	ldr	r3, [r3]
1.00 2 	ldr	r2, [fp, #-28]
1.00 2 	cmp	r2, r3
0.00 2 	bne	.L3
1.00 1 	ldr	r3, [fp, #-8]
1.00 1 	b	.L4
1.00 0 .L3:
1.00 1 	ldr	r3, [fp, #-8]
1.00 1 	lsl	r3, r3, #2
1.00 1 	ldr	r2, [fp, #-16]
1.00 1 	add	r3, r2, r3
1.00 1 	ldr	r3, [r3]
1.00 1 	ldr	r2, [fp, #-28]
1.00 1 	cmp	r2, r3
0.00 1 	bge	.L5
1.00 0 	ldr	r3, [fp, #-8]
1.00 0 	sub	r2, r3, #1
1.00 0 	ldr	r3, [fp, #-28]
1.00 0 	ldr	r1, [fp, #-20]
1.00 0 	ldr	r0, [fp, #-16]
1.00 0 	bl	binarySearch
1.00 0 	mov	r3, r0
1.00 0 	b	.L4
1.00 0 .L5:
1.00 1 	ldr	r3, [fp, #-8]
1.00 1 	add	r1, r3, #1
1.00 1 	ldr	r3, [fp, #-28]
1.00 1 	ldr	r2, [fp, #-24]
1.00 1 	ldr	r0, [fp, #-16]
1.00 1 	bl	binarySearch
1.00 1 	mov	r3, r0
1.00 1 	b	.L4
1.00 0 .L2:
1.00 0 	mvn	r3, #0
1.00 0 .L4:
1.00 2 	mov	r0, r3
1.00 2 	sub	sp, fp, #4
1.00 0 	@ sp needed
1.00 2 	pop	{fp, pc}
1.00 0 	.size	binarySearch, .-binarySearch
1.00 0 	.section	.rodata
1.00 0 	.align	2
1.00 0 .LC1:
1.00 0 	.ascii	"Result: %d\012\000"
1.00 0 	.align	2
1.00 0 .LC0:
1.00 0 	.word	2
1.00 0 	.word	3
1.00 0 	.word	4
1.00 0 	.word	10
1.00 0 	.word	40
1.00 0 	.text
1.00 0 	.align	2
1.00 0 	.global	main
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	main, %function
1.00 0 main:
1.00 0 	@ args = 0, pretend = 0, frame = 32
1.00 0 	@ frame_needed = 1, uses_anonymous_args = 0
1.00 1 	push	{fp, lr}
1.00 1 	add	fp, sp, #4
1.00 1 	sub	sp, sp, #32
1.00 1 	movw	r3, #:lower16:.LC0
1.00 1 	movt	r3, #:upper16:.LC0
1.00 1 	sub	ip, fp, #32
1.00 1 	mov	lr, r3
1.00 1 	ldmia	lr!, {r0, r1, r2, r3}
1.00 1 	stmia	ip!, {r0, r1, r2, r3}
1.00 1 	ldr	r3, [lr]
1.00 1 	str	r3, [ip]
1.00 1 	mov	r3, #6
1.00 1 	str	r3, [fp, #-8]
1.00 1 	mov	r3, #40
1.00 1 	str	r3, [fp, #-12]
1.00 1 	ldr	r3, [fp, #-8]
1.00 1 	sub	r2, r3, #1
1.00 1 	sub	r0, fp, #32
1.00 1 	ldr	r3, [fp, #-12]
1.00 1 	mov	r1, #0
1.00 1 	bl	binarySearch
1.00 1 	mov	r3, r0
1.00 1 	mov	r1, r3
1.00 1 	movw	r0, #:lower16:.LC1
1.00 1 	movt	r0, #:upper16:.LC1
1.00 1 	bl	printf
1.00 1 	mov	r3, #0
1.00 1 	mov	r0, r3
1.00 1 	sub	sp, fp, #4
1.00 0 	@ sp needed
1.00 1 	pop	{fp, pc}
1.00 0 	.size	main, .-main
1.00 0 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
1.00 0 	.section	.note.GNU-stack,"",%progbits
