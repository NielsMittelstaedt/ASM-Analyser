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
	cmp	r1, r2
	str	lr, [sp, #-4]!
	mov	lr, r0
	bgt	.L8
.L2:
	sub	r0, r2, r1
	add	r0, r1, r0, asr #1
	ldr	ip, [lr, r0, lsl #2]
	cmp	ip, r3
	ldreq	pc, [sp], #4
	ble	.L4
	sub	r2, r0, #1
	cmp	r2, r1
	bge	.L2
.L8:
	mvn	r0, #0
	ldr	pc, [sp], #4
.L4:
	add	r1, r0, #1
	cmp	r1, r2
	ble	.L2
	b	.L8
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
	sub	ip, r2, r1
	push	{r4, lr}
	add	ip, ip, ip, lsr #31
	mov	r4, r0
	add	r0, r1, ip, asr #1
	ldr	ip, [r4, r0, lsl #2]
	cmp	r3, ip
	popeq	{r4, pc}
	cmp	r2, r1
	movgt	lr, #0
	movle	lr, #1
	orrs	lr, lr, r2, lsr #31
	bne	.L17
.L12:
	cmp	r3, ip
	addge	r1, r0, #1
	sublt	r2, r0, #1
	sub	r0, r2, r1
	add	r0, r0, r0, lsr #31
	add	r0, r1, r0, asr #1
	ldr	ip, [r4, r0, lsl #2]
	cmp	ip, r3
	popeq	{r4, pc}
	cmp	r1, r2
	movlt	lr, #0
	movge	lr, #1
	orrs	lr, lr, r2, lsr #31
	beq	.L12
.L17:
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
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, lr}
	sub	sp, sp, #24
	ldmia	ip!, {r0, r1, r2, r3}
	add	lr, sp, #4
	ldr	ip, [ip]
	stmia	lr!, {r0, r1, r2, r3}
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	str	ip, [lr]
	bl	__printf_chk
	mov	r2, #0
	mov	r1, #4
.L21:
	sub	r3, r1, r2
	add	r0, sp, #24
	add	r3, r2, r3, asr #1
	add	r0, r0, r3, lsl #2
	ldr	r0, [r0, #-20]
	cmp	r0, #10
	beq	.L22
	ble	.L23
	sub	r1, r3, #1
	cmp	r1, r2
	bge	.L21
.L25:
	movw	r1, #:lower16:.LC2
	movw	r0, #:lower16:.LC3
	ldr	r3, .L50
	movt	r1, #:upper16:.LC2
	movt	r0, #:upper16:.LC3
	mov	r2, #87
	bl	__assert_fail
.L23:
	add	r2, r3, #1
	cmp	r2, r1
	ble	.L21
	b	.L25
.L22:
	cmp	r3, #3
	bne	.L25
	movw	r1, #:lower16:.LC4
	mov	r0, #1
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
	ldr	r4, [sp, #12]
	cmp	r4, #10
	movne	r0, r4
	movne	r3, #2
	movne	r1, #4
	movne	r2, #0
	bne	.L27
	b	.L28
.L31:
	cmp	r1, r2
	movgt	ip, #0
	movle	ip, #1
	orrs	ip, ip, r1, lsr #31
	bne	.L28
.L27:
	cmp	r0, #10
	add	r0, sp, #24
	addle	r2, r3, #1
	subgt	r1, r3, #1
	sub	r3, r1, r2
	add	r3, r3, r3, lsr #31
	add	r3, r2, r3, asr #1
	add	r0, r0, r3, lsl #2
	ldr	r0, [r0, #-20]
	cmp	r0, #10
	bne	.L31
	cmp	r3, #3
	bne	.L28
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	puts
	movw	r1, #:lower16:.LC6
	mov	r0, #1
	movt	r1, #:upper16:.LC6
	bl	__printf_chk
	mov	r2, #0
	mov	r1, #4
.L33:
	sub	r3, r1, r2
	add	r0, sp, #24
	add	r3, r2, r3, asr #1
	add	r0, r0, r3, lsl #2
	ldr	r0, [r0, #-20]
	cmp	r0, #5
	beq	.L34
	ble	.L35
	sub	r1, r3, #1
	cmp	r1, r2
	bge	.L33
.L37:
	movw	r1, #:lower16:.LC4
	mov	r0, #1
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
	cmp	r4, #5
	movne	r3, #2
	movne	r1, #4
	movne	r2, #0
	bne	.L42
	b	.L43
.L41:
	cmp	r1, r2
	movgt	r0, #0
	movle	r0, #1
	orrs	r0, r0, r1, lsr #31
	bne	.L38
.L42:
	cmp	r4, #5
	add	r0, sp, #24
	addle	r2, r3, #1
	subgt	r1, r3, #1
	sub	r3, r1, r2
	add	r3, r3, r3, lsr #31
	add	r3, r2, r3, asr #1
	add	r0, r0, r3, lsl #2
	ldr	r4, [r0, #-20]
	cmp	r4, #5
	bne	.L41
	cmn	r3, #1
	bne	.L43
.L38:
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	add	sp, sp, #24
	@ sp needed
	pop	{r4, lr}
	b	puts
.L35:
	add	r2, r3, #1
	cmp	r2, r1
	ble	.L33
	b	.L37
.L28:
	movw	r1, #:lower16:.LC2
	movw	r0, #:lower16:.LC3
	ldr	r3, .L50
	movt	r1, #:upper16:.LC2
	movt	r0, #:upper16:.LC3
	mov	r2, #90
	bl	__assert_fail
.L43:
	movw	r1, #:lower16:.LC2
	movw	r0, #:lower16:.LC7
	ldr	r3, .L50
	movt	r1, #:upper16:.LC2
	movt	r0, #:upper16:.LC7
	mov	r2, #100
	bl	__assert_fail
.L34:
	movw	r1, #:lower16:.LC2
	movw	r0, #:lower16:.LC7
	ldr	r3, .L50
	movt	r1, #:upper16:.LC2
	movt	r0, #:upper16:.LC7
	mov	r2, #97
	bl	__assert_fail
.L51:
	.align	2
.L50:
	.word	.LANCHOR0+20
	.size	test, .-test
	.section	.text.startup,"ax",%progbits
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
