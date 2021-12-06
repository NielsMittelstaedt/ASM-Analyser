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
	.file	"sentinel_linear_search.c"
	.text
	.align	2
	.global	sentinel_linear_search
	.syntax unified
	.arm
	.fpu softvfp
	.type	sentinel_linear_search, %function
sentinel_linear_search:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	sub	r4, r1, #-1073741823
	sub	lr, r1, #1
	ldr	r5, [r0, r4, lsl #2]
	cmp	r5, r2
	beq	.L5
	str	r2, [r0, r4, lsl #2]
	mov	ip, r0
	ldr	r3, [r0]
	cmp	r2, r3
	beq	.L6
	mov	r3, r0
	mov	r0, #0
.L4:
	ldr	r1, [r3, #4]!
	add	r0, r0, #1
	cmp	r1, r2
	bne	.L4
.L3:
	cmp	r0, lr
	str	r5, [ip, r4, lsl #2]
	mvneq	r0, #0
	pop	{r4, r5, pc}
.L5:
	mov	r0, lr
	pop	{r4, r5, pc}
.L6:
	mov	r0, #0
	b	.L3
	.size	sentinel_linear_search, .-sentinel_linear_search
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"../test_files/c_in/sentinel_linear_search.c\000"
	.align	2
.LC2:
	.ascii	"sentinel_linear_search( arr, n, 2 )==1\000"
	.align	2
.LC3:
	.ascii	"sentinel_linear_search( arr, n, 6 )==3\000"
	.align	2
.LC4:
	.ascii	"All test cases have successfully passed!\000"
	.align	2
.LC5:
	.ascii	"sentinel_linear_search( arr, n, 101 )==-1\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, lr}
	sub	sp, sp, #32
	ldmia	ip!, {r0, r1, r2, r3}
	add	lr, sp, #4
	mov	r4, #2
	stmia	lr!, {r0, r1, r2, r3}
	ldm	ip, {r0, r1, r2}
	ldr	ip, [sp, #4]
	cmp	ip, r4
	stm	lr, {r0, r1, r2}
	str	r4, [sp, #20]
	beq	.L12
	add	r1, sp, #4
	mov	r3, #0
	mov	r2, r1
.L13:
	ldr	r0, [r2, #4]!
	add	r3, r3, #1
	cmp	r0, #2
	bne	.L13
	cmp	r3, #1
	bne	.L12
	cmp	ip, #6
	mov	r3, #6
	str	r3, [sp, #20]
	beq	.L15
	add	r3, sp, #4
	mov	r2, #0
.L16:
	ldr	r0, [r3, #4]!
	add	r2, r2, #1
	cmp	r0, #6
	bne	.L16
	cmp	r2, #3
	bne	.L15
	cmp	ip, #101
	mov	r3, #101
	str	r3, [sp, #20]
	beq	.L18
	mov	r3, #0
.L19:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	cmp	r2, #101
	bne	.L19
	cmp	r3, #4
	mov	r3, #99
	str	r3, [sp, #20]
	beq	.L33
.L18:
	movw	r1, #:lower16:.LC1
	movw	r0, #:lower16:.LC5
	ldr	r3, .L35
	movt	r1, #:upper16:.LC1
	movt	r0, #:upper16:.LC5
	mov	r2, #68
	bl	__assert_fail
.L12:
	movw	r1, #:lower16:.LC1
	movw	r0, #:lower16:.LC2
	ldr	r3, .L35
	movt	r1, #:upper16:.LC1
	movt	r0, #:upper16:.LC2
	mov	r2, #66
	bl	__assert_fail
.L15:
	movw	r1, #:lower16:.LC1
	movw	r0, #:lower16:.LC3
	ldr	r3, .L35
	movt	r1, #:upper16:.LC1
	movt	r0, #:upper16:.LC3
	mov	r2, #67
	bl	__assert_fail
.L33:
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	puts
	mov	r0, #0
	add	sp, sp, #32
	@ sp needed
	pop	{r4, pc}
.L36:
	.align	2
.L35:
	.word	.LANCHOR0+28
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	1
	.word	2
	.word	2
	.word	6
	.word	99
	.word	100
	.word	999
	.type	__PRETTY_FUNCTION__.4824, %object
	.size	__PRETTY_FUNCTION__.4824, 5
__PRETTY_FUNCTION__.4824:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
