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
	.file	"floyd_cycle_detection_algorithm.c"
	.text
	.align	2
	.global	duplicateNumber
	.syntax unified
	.arm
	.fpu softvfp
	.type	duplicateNumber, %function
duplicateNumber:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #1
	mov	r3, r0
	bls	.L5
	ldr	r2, [r0]
	mov	r0, r2
	mov	r1, r2
.L3:
	ldr	r0, [r3, r0, lsl #2]
	ldr	r1, [r3, r1, lsl #2]
	ldr	r0, [r3, r0, lsl #2]
	cmp	r1, r0
	bne	.L3
	cmp	r2, r0
	bxeq	lr
.L4:
	ldr	r2, [r3, r2, lsl #2]
	ldr	r0, [r3, r0, lsl #2]
	cmp	r2, r0
	bne	.L4
	bx	lr
.L5:
	mvn	r0, #0
	bx	lr
	.size	duplicateNumber, .-duplicateNumber
	.section	.rodata.str1.4,"aMS",%progbits,1
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
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	movw	r4, #:lower16:.LANCHOR0
	movt	r4, #:upper16:.LANCHOR0
	sub	sp, sp, #64
	add	ip, sp, #4
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	r4, {r0, r1, r2}
	stm	ip, {r0, r1, r2}
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	bl	__printf_chk
	add	r0, sp, #4
	mov	r1, #15
	bl	duplicateNumber
	cmp	r0, #1
	bne	.L13
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	puts
	mov	r0, #0
	add	sp, sp, #64
	@ sp needed
	pop	{r4, pc}
.L13:
	movw	r1, #:lower16:.LC2
	movw	r0, #:lower16:.LC3
	add	r3, r4, #12
	movt	r1, #:upper16:.LC2
	movt	r0, #:upper16:.LC3
	mov	r2, #56
	bl	__assert_fail
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
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
	.type	__PRETTY_FUNCTION__.4919, %object
	.size	__PRETTY_FUNCTION__.4919, 5
__PRETTY_FUNCTION__.4919:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
