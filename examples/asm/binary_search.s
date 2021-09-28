	.arch armv7-a
	.arch_extension virt
	.arch_extension idiv
	.arch_extension sec
	.arch_extension mp
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
	.ascii	"Element is not present in array\000"
	.align	2
.LC2:
	.ascii	"Element is present at index %d\000"
	.align	2
.LC0:
	.word	2
	.word	3
	.word	4
	.word	10
	.word	40
	.align	2
.LC3:
	.word	__stack_chk_guard
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #40
	movw	r3, #:lower16:.LC3
	movt	r3, #:upper16:.LC3
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	mov	r3,#0
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	sub	ip, fp, #28
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldr	r3, [lr]
	str	r3, [ip]
	mov	r3, #5
	str	r3, [fp, #-40]
	mov	r3, #10
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-40]
	sub	r2, r3, #1
	sub	r0, fp, #28
	ldr	r3, [fp, #-36]
	mov	r1, #0
	bl	binarySearch
	str	r0, [fp, #-32]
	ldr	r3, [fp, #-32]
	cmn	r3, #1
	bne	.L7
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	printf
	b	.L8
.L7:
	ldr	r1, [fp, #-32]
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	printf
.L8:
	mov	r3, #0
	movw	r2, #:lower16:.LC3
	movt	r2, #:upper16:.LC3
	ldr	r1, [r2]
	ldr	r2, [fp, #-8]
	eors	r1, r2, r1
	mov	r2, #0
	beq	.L10
	bl	__stack_chk_fail
.L10:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
