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
	.file	"floyd_cycle_detection_algorithm.c"
	.text
	.align	2
	.global	duplicateNumber
	.syntax unified
	.arm
	.fpu softvfp
	.type	duplicateNumber, %function
duplicateNumber:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	ldr	r3, [fp, #-20]
	cmp	r3, #1
	bhi	.L2
	mvn	r3, #0
	b	.L3
.L2:
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	str	r3, [fp, #-12]
.L4:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-12]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	str	r3, [fp, #-12]
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bne	.L4
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	b	.L5
.L6:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-12]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3]
	str	r3, [fp, #-12]
.L5:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bne	.L6
	ldr	r3, [fp, #-8]
.L3:
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	duplicateNumber, .-duplicateNumber
	.section	.rodata
	.align	2
.LC1:
	.ascii	"1st test... \000"
	.align	2
.LC2:
	.ascii	"../test_files/c_in/floyd_cycle_detection_algorithm."
	.ascii	"c\000"
	.align	2
.LC3:
	.ascii	"index == 1\000"
	.align	2
.LC4:
	.ascii	"passed\000"
	.align	2
.LC0:
	.word	1
	.word	1
	.word	2
	.word	3
	.word	5
	.word	8
	.word	13
	.word	21
	.word	34
	.word	55
	.word	89
	.word	144
	.word	233
	.word	377
	.word	610
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #72
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	sub	ip, fp, #72
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1, r2}
	stm	ip, {r0, r1, r2}
	mov	r3, #15
	str	r3, [fp, #-8]
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	printf
	sub	r3, fp, #72
	ldr	r1, [fp, #-8]
	mov	r0, r3
	bl	duplicateNumber
	str	r0, [fp, #-12]
	ldr	r3, [fp, #-12]
	cmp	r3, #1
	beq	.L8
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4682
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4682
	mov	r2, #56
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	__assert_fail
.L8:
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
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
	.type	__PRETTY_FUNCTION__.4682, %object
	.size	__PRETTY_FUNCTION__.4682, 5
__PRETTY_FUNCTION__.4682:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
