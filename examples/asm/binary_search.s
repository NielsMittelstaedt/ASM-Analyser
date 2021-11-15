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
	.file	"binary_search.c"
	.text
	.align	2
	.global	binarySearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	binarySearch, %function
binarySearch:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	str	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-20]
	cmp	r2, r3
	blt	.L2
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-20]
	sub	r3, r2, r3
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	mov	r2, r3
	ldr	r3, [fp, #-20]
	add	r3, r3, r2
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	bne	.L3
	ldr	r3, [fp, #-8]
	b	.L4
.L3:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	bge	.L5
	ldr	r3, [fp, #-8]
	sub	r2, r3, #1
	ldr	r3, [fp, #-28]
	ldr	r1, [fp, #-20]
	ldr	r0, [fp, #-16]
	bl	binarySearch
	mov	r3, r0
	b	.L4
.L5:
	ldr	r3, [fp, #-8]
	add	r1, r3, #1
	ldr	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	ldr	r0, [fp, #-16]
	bl	binarySearch
	mov	r3, r0
	b	.L4
.L2:
	mvn	r3, #0
.L4:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	binarySearch, .-binarySearch
	.section	.rodata
	.align	2
.LC1:
	.ascii	"Ergebnis: %d\012\000"
	.align	2
.LC0:
	.word	2
	.word	3
	.word	4
	.word	10
	.word	40
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #32
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	sub	ip, fp, #36
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldr	r3, [lr]
	str	r3, [ip]
	mov	r3, #5
	str	r3, [fp, #-8]
	mov	r3, #40
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-8]
	sub	r2, r3, #1
	sub	r0, fp, #36
	ldr	r3, [fp, #-12]
	mov	r1, #0
	bl	binarySearch
	str	r0, [fp, #-16]
	ldr	r1, [fp, #-16]
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
