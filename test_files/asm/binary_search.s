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
	.global	binarysearch1
	.syntax unified
	.arm
	.fpu softvfp
	.type	binarysearch1, %function
binarysearch1:
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
	bl	binarysearch1
	mov	r3, r0
	b	.L4
.L5:
	ldr	r3, [fp, #-8]
	add	r1, r3, #1
	ldr	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	ldr	r0, [fp, #-16]
	bl	binarysearch1
	mov	r3, r0
	b	.L4
.L2:
	mvn	r3, #0
.L4:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	binarysearch1, .-binarysearch1
	.align	2
	.global	binarysearch2
	.syntax unified
	.arm
	.fpu softvfp
	.type	binarysearch2, %function
binarysearch2:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	str	r3, [fp, #-28]
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
	b	.L7
.L13:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-20]
	cmp	r2, r3
	ble	.L8
	ldr	r3, [fp, #-24]
	cmp	r3, #0
	bge	.L9
.L8:
	mvn	r3, #0
	b	.L10
.L9:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	bge	.L11
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-24]
	b	.L12
.L11:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-20]
.L12:
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
.L7:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	bne	.L13
	ldr	r3, [fp, #-8]
.L10:
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	binarysearch2, .-binarysearch2
	.section	.rodata
	.align	2
.LC1:
	.ascii	"Test 1.... \000"
	.align	2
.LC2:
	.ascii	"../test_files/c_in/binary_search.c\000"
	.align	2
.LC3:
	.ascii	"result == 3\000"
	.align	2
.LC4:
	.ascii	"passed recursive... \000"
	.align	2
.LC5:
	.ascii	"passed iterative...\000"
	.align	2
.LC6:
	.ascii	"Test 2.... \000"
	.align	2
.LC7:
	.ascii	"result == -1\000"
	.align	2
.LC0:
	.word	2
	.word	3
	.word	4
	.word	10
	.word	40
	.text
	.align	2
	.global	test
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
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
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	printf
	mov	r3, #10
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-8]
	sub	r2, r3, #1
	sub	r0, fp, #36
	ldr	r3, [fp, #-12]
	mov	r1, #0
	bl	binarysearch1
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	cmp	r3, #3
	beq	.L15
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4635
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4635
	mov	r2, #87
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	__assert_fail
.L15:
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	printf
	ldr	r3, [fp, #-8]
	sub	r2, r3, #1
	sub	r0, fp, #36
	ldr	r3, [fp, #-12]
	mov	r1, #0
	bl	binarysearch2
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	cmp	r3, #3
	beq	.L16
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4635
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4635
	mov	r2, #90
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	__assert_fail
.L16:
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	puts
	movw	r0, #:lower16:.LC6
	movt	r0, #:upper16:.LC6
	bl	printf
	mov	r3, #5
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-8]
	sub	r2, r3, #1
	sub	r0, fp, #36
	ldr	r3, [fp, #-12]
	mov	r1, #0
	bl	binarysearch1
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	cmn	r3, #1
	beq	.L17
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4635
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4635
	mov	r2, #97
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC7
	movt	r0, #:upper16:.LC7
	bl	__assert_fail
.L17:
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	printf
	ldr	r3, [fp, #-8]
	sub	r2, r3, #1
	sub	r0, fp, #36
	ldr	r3, [fp, #-12]
	mov	r1, #0
	bl	binarysearch2
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	cmn	r3, #1
	beq	.L18
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4635
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4635
	mov	r2, #100
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC7
	movt	r0, #:upper16:.LC7
	bl	__assert_fail
.L18:
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	puts
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	test, .-test
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	bl	test
	mov	r3, #0
	mov	r0, r3
	pop	{fp, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.type	__PRETTY_FUNCTION__.4635, %object
	.size	__PRETTY_FUNCTION__.4635, 5
__PRETTY_FUNCTION__.4635:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
