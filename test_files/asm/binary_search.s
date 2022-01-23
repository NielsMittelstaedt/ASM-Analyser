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
0 	.file	"binary_search.c"
0 	.text
0 	.align	2
0 	.global	binarySearch
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	binarySearch, %function
0 binarySearch:
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 1, uses_anonymous_args = 0
2 	push	{fp, lr}
2 	add	fp, sp, #4
2 	sub	sp, sp, #24
2 	str	r0, [fp, #-16]
2 	str	r1, [fp, #-20]
2 	str	r2, [fp, #-24]
2 	str	r3, [fp, #-28]
2 	ldr	r2, [fp, #-24]
2 	ldr	r3, [fp, #-20]
2 	cmp	r2, r3
2 	blt	.L2
2 	ldr	r2, [fp, #-24]
2 	ldr	r3, [fp, #-20]
2 	sub	r3, r2, r3
2 	lsr	r2, r3, #31
2 	add	r3, r2, r3
2 	asr	r3, r3, #1
2 	mov	r2, r3
2 	ldr	r3, [fp, #-20]
2 	add	r3, r3, r2
2 	str	r3, [fp, #-8]
2 	ldr	r3, [fp, #-8]
2 	lsl	r3, r3, #2
2 	ldr	r2, [fp, #-16]
2 	add	r3, r2, r3
2 	ldr	r3, [r3]
2 	ldr	r2, [fp, #-28]
2 	cmp	r2, r3
2 	bne	.L3
1 	ldr	r3, [fp, #-8]
1 	b	.L4
0 .L3:
1 	ldr	r3, [fp, #-8]
1 	lsl	r3, r3, #2
1 	ldr	r2, [fp, #-16]
1 	add	r3, r2, r3
1 	ldr	r3, [r3]
1 	ldr	r2, [fp, #-28]
1 	cmp	r2, r3
1 	bge	.L5
0 	ldr	r3, [fp, #-8]
0 	sub	r2, r3, #1
0 	ldr	r3, [fp, #-28]
0 	ldr	r1, [fp, #-20]
0 	ldr	r0, [fp, #-16]
0 	bl	binarySearch
0 	mov	r3, r0
0 	b	.L4
0 .L5:
1 	ldr	r3, [fp, #-8]
1 	add	r1, r3, #1
1 	ldr	r3, [fp, #-28]
1 	ldr	r2, [fp, #-24]
1 	ldr	r0, [fp, #-16]
1 	bl	binarySearch
1 	mov	r3, r0
1 	b	.L4
0 .L2:
0 	mvn	r3, #0
0 .L4:
2 	mov	r0, r3
2 	sub	sp, fp, #4
0 	@ sp needed
2 	pop	{fp, pc}
0 	.size	binarySearch, .-binarySearch
0 	.section	.rodata
0 	.align	2
0 .LC1:
0 	.ascii	"Result: %d\012\000"
0 	.align	2
0 .LC0:
0 	.word	2
0 	.word	3
0 	.word	4
0 	.word	10
0 	.word	40
0 	.text
0 	.align	2
0 	.global	main
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	main, %function
0 main:
0 	@ args = 0, pretend = 0, frame = 32
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #32
1 	movw	r3, #:lower16:.LC0
1 	movt	r3, #:upper16:.LC0
1 	sub	ip, fp, #32
1 	mov	lr, r3
1 	ldmia	lr!, {r0, r1, r2, r3}
1 	stmia	ip!, {r0, r1, r2, r3}
1 	ldr	r3, [lr]
1 	str	r3, [ip]
1 	mov	r3, #6
1 	str	r3, [fp, #-8]
1 	mov	r3, #40
1 	str	r3, [fp, #-12]
1 	ldr	r3, [fp, #-8]
1 	sub	r2, r3, #1
1 	sub	r0, fp, #32
1 	ldr	r3, [fp, #-12]
1 	mov	r1, #0
1 	bl	binarySearch
1 	mov	r3, r0
1 	mov	r1, r3
1 	movw	r0, #:lower16:.LC1
1 	movt	r0, #:upper16:.LC1
1 	bl	printf
1 	mov	r3, #0
1 	mov	r0, r3
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
