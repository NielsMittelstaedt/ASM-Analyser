	.arch armv7-a
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 1
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
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r2, r1
	blt	.L4
	push	{r4, lr}
	mov	lr, r0
	sub	ip, r2, r1
	add	ip, ip, ip, lsr #31
	add	r0, r1, ip, asr #1
	ldr	ip, [lr, r0, lsl #2]
	cmp	ip, r3
	popeq	{r4, pc}
	subgt	r2, r0, #1
	addle	r1, r0, #1
	mov	r0, lr
	bl	binarysearch1
	pop	{r4, pc}
.L4:
	mvn	r0, #0
	bx	lr
	.size	binarysearch1, .-binarysearch1
	.align	2
	.global	binarysearch2
	.syntax unified
	.arm
	.fpu softvfp
	.type	binarysearch2, %function
binarysearch2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	lr, r0
	sub	ip, r2, r1
	add	ip, ip, ip, lsr #31
	add	r0, r1, ip, asr #1
	ldr	ip, [lr, r0, lsl #2]
	cmp	r3, ip
	popeq	{r4, pc}
	cmp	r2, r1
	movgt	r4, #0
	movle	r4, #1
	orrs	r4, r4, r2, lsr #31
	bne	.L19
.L11:
	cmp	r3, ip
	sublt	r2, r0, #1
	addge	r1, r0, #1
	sub	r0, r2, r1
	add	r0, r0, r0, lsr #31
	add	r0, r1, r0, asr #1
	ldr	ip, [lr, r0, lsl #2]
	cmp	ip, r3
	popeq	{r4, pc}
	cmp	r1, r2
	movlt	r4, #0
	movge	r4, #1
	orrs	r4, r4, r2, lsr #31
	beq	.L11
	mvn	r0, #0
	pop	{r4, pc}
.L19:
	mvn	r0, #0
	pop	{r4, pc}
	.size	binarysearch2, .-binarysearch2
	.section	.rodata.str1.4,"aMS",%progbits,1
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
	.text
	.align	2
	.global	test
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	str	lr, [sp, #-4]!
	sub	sp, sp, #28
	add	lr, sp, #4
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldr	r3, [ip]
	str	r3, [lr]
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	mov	r0, #1
	bl	__printf_chk
	mov	r3, #10
	mov	r2, #4
	mov	r1, #0
	add	r0, sp, r2
	bl	binarysearch1
	cmp	r0, #3
	bne	.L26
	movw	r1, #:lower16:.LC4
	movt	r1, #:upper16:.LC4
	mov	r0, #1
	bl	__printf_chk
	mov	r3, #10
	mov	r2, #4
	mov	r1, #0
	add	r0, sp, r2
	bl	binarysearch2
	cmp	r0, #3
	bne	.L27
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	puts
	movw	r1, #:lower16:.LC6
	movt	r1, #:upper16:.LC6
	mov	r0, #1
	bl	__printf_chk
	mov	r3, #5
	mov	r2, #4
	mov	r1, #0
	add	r0, sp, r2
	bl	binarysearch1
	cmn	r0, #1
	bne	.L28
	movw	r1, #:lower16:.LC4
	movt	r1, #:upper16:.LC4
	mov	r0, #1
	bl	__printf_chk
	mov	r3, #5
	mov	r2, #4
	mov	r1, #0
	add	r0, sp, r2
	bl	binarysearch2
	cmn	r0, #1
	bne	.L29
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	puts
	add	sp, sp, #28
	@ sp needed
	ldr	pc, [sp], #4
.L26:
	ldr	r3, .L30
	mov	r2, #87
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	__assert_fail
.L27:
	ldr	r3, .L30
	mov	r2, #90
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	__assert_fail
.L28:
	ldr	r3, .L30
	mov	r2, #97
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC7
	movt	r0, #:upper16:.LC7
	bl	__assert_fail
.L29:
	ldr	r3, .L30
	mov	r2, #100
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movw	r0, #:lower16:.LC7
	movt	r0, #:upper16:.LC7
	bl	__assert_fail
.L31:
	.align	2
.L30:
	.word	.LANCHOR0+20
	.size	test, .-test
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	bl	test
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	2
	.word	3
	.word	4
	.word	10
	.word	40
	.type	__PRETTY_FUNCTION__.4832, %object
	.size	__PRETTY_FUNCTION__.4832, 5
__PRETTY_FUNCTION__.4832:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
