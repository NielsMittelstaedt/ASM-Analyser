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
	.file	"exponential_search.c"
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	exponential_search.part.0, %function
exponential_search.part.0:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r3, #1
	b	.L2
.L4:
	lsl	r3, r3, #1
	cmp	r3, r1
	bhi	.L3
.L2:
	ldr	ip, [r0, r3, lsl #2]
	cmp	ip, r2
	blt	.L4
.L3:
	cmp	r1, r3
	ubfx	ip, r3, #1, #16
	movcs	r1, r3
	sub	r3, r1, r3, lsr #1
	uxth	r1, r1
	add	r3, r3, r3, lsr #31
	cmp	ip, r1
	add	r3, ip, r3, asr #1
	uxth	r3, r3
	bhi	.L10
	push	{r4, r5, lr}
.L6:
	sub	r5, r3, #1
	ldr	lr, [r0, r3, lsl #2]
	add	r4, r3, #1
	cmp	r2, lr
	beq	.L16
	bge	.L8
	uxth	r1, r5
	sub	r3, r1, ip
	cmp	r1, ip
	add	r3, r3, r3, lsr #31
	add	r3, ip, r3, asr #1
	uxth	r3, r3
	bcs	.L6
.L11:
	mvn	r0, #0
	pop	{r4, r5, pc}
.L8:
	uxth	ip, r4
	sub	r3, r1, ip
	cmp	ip, r1
	add	r3, r3, r3, lsr #31
	add	r3, ip, r3, asr #1
	uxth	r3, r3
	bls	.L6
	b	.L11
.L16:
	mov	r0, r3
	pop	{r4, r5, pc}
.L10:
	mvn	r0, #0
	bx	lr
	.size	exponential_search.part.0, .-exponential_search.part.0
	.align	2
	.global	exponential_search
	.syntax unified
	.arm
	.fpu softvfp
	.type	exponential_search, %function
exponential_search:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #0
	beq	.L27
	mov	r3, #1
	b	.L19
.L21:
	lsl	r3, r3, #1
	cmp	r1, r3
	bcc	.L20
.L19:
	ldr	ip, [r0, r3, lsl #2]
	cmp	r2, ip
	bgt	.L21
.L20:
	cmp	r1, r3
	ubfx	ip, r3, #1, #16
	movcs	r1, r3
	sub	r3, r1, r3, lsr #1
	uxth	r1, r1
	add	r3, r3, r3, lsr #31
	cmp	ip, r1
	add	r3, ip, r3, asr #1
	uxth	r3, r3
	bhi	.L27
	push	{r4, r5, lr}
.L22:
	sub	r5, r3, #1
	ldr	lr, [r0, r3, lsl #2]
	add	r4, r3, #1
	cmp	r2, lr
	beq	.L32
	bge	.L24
	uxth	r1, r5
	sub	r3, r1, ip
	cmp	r1, ip
	add	r3, r3, r3, lsr #31
	add	r3, ip, r3, asr #1
	uxth	r3, r3
	bcs	.L22
.L28:
	mvn	r0, #0
	pop	{r4, r5, pc}
.L24:
	uxth	ip, r4
	sub	r3, r1, ip
	cmp	ip, r1
	add	r3, r3, r3, lsr #31
	add	r3, ip, r3, asr #1
	uxth	r3, r3
	bls	.L22
	b	.L28
.L32:
	mov	r0, r3
	pop	{r4, r5, pc}
.L27:
	mvn	r0, #0
	bx	lr
	.size	exponential_search, .-exponential_search
	.align	2
	.global	binary_search
	.syntax unified
	.arm
	.fpu softvfp
	.type	binary_search, %function
binary_search:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	sub	ip, r2, r1
	cmp	r1, r2
	add	ip, ip, ip, lsr #31
	add	ip, r1, ip, asr #1
	uxth	ip, ip
	bhi	.L39
	push	{r4, r5, lr}
.L35:
	sub	r5, ip, #1
	ldr	lr, [r0, ip, lsl #2]
	add	r4, ip, #1
	cmp	lr, r3
	beq	.L44
	ble	.L37
	uxth	r2, r5
	sub	ip, r2, r1
	cmp	r2, r1
	add	ip, ip, ip, lsr #31
	add	ip, r1, ip, asr #1
	uxth	ip, ip
	bcs	.L35
.L40:
	mvn	r0, #0
	pop	{r4, r5, pc}
.L37:
	uxth	r1, r4
	sub	ip, r2, r1
	cmp	r1, r2
	add	ip, ip, ip, lsr #31
	add	ip, r1, ip, asr #1
	uxth	ip, ip
	bls	.L35
	b	.L40
.L44:
	mov	r0, ip
	pop	{r4, r5, pc}
.L39:
	mvn	r0, #0
	bx	lr
	.size	binary_search, .-binary_search
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	.ascii	"../test_files/c_in/exponential_search.c\000"
	.align	2
.LC4:
	.ascii	"exponential_search(arr_found, 3, 10) == -1\000"
	.align	2
.LC5:
	.ascii	"exponential_search(arr_found, 1, 1) == 0\000"
	.align	2
.LC6:
	.ascii	"exponential_search(arr_first_2, 2, 1) == 0\000"
	.align	2
.LC7:
	.ascii	"exponential_search(arr_last_2, 2, 2) == 1\000"
	.align	2
.LC8:
	.ascii	"exponential_search(arr_first_n, 5, -1) == 0\000"
	.align	2
.LC9:
	.ascii	"exponential_search(arr_last_n, 5, 8) == 4\000"
	.align	2
.LC10:
	.ascii	"exponential_search(arr_middle, 5, 6) == 3\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r8, r9, lr}
	movw	r4, #:lower16:.LANCHOR0
	movt	r4, #:upper16:.LANCHOR0
	sub	sp, sp, #88
	add	r5, sp, #16
	ldm	r4, {r0, r1, r2}
	stm	r5, {r0, r1, r2}
	mov	r0, r5
	mov	r2, #10
	mov	r1, #3
	bl	exponential_search.part.0
	cmn	r0, #1
	bne	.L54
	mov	r2, #1
	mov	r6, r0
	mov	r1, r2
	mov	r0, r5
	bl	exponential_search.part.0
	cmp	r0, #0
	bne	.L55
	mov	r2, #1
	mov	r1, #2
	mov	r0, sp
	mov	r8, #1
	mov	r9, #2
	strd	r8, [sp]
	bl	exponential_search.part.0
	cmp	r0, #0
	bne	.L56
	mov	r2, #2
	add	r0, sp, #8
	mov	r1, r2
	strd	r8, [sp, #8]
	bl	exponential_search.part.0
	cmp	r0, #1
	bne	.L57
	add	lr, r4, #20
	add	ip, sp, #28
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	lr, [lr]
	stmia	ip!, {r0, r1, r2, r3}
	add	r0, sp, #28
	mov	r2, r6
	mov	r1, #5
	str	lr, [ip]
	bl	exponential_search.part.0
	subs	r5, r0, #0
	bne	.L58
	add	lr, r4, #20
	add	ip, sp, #48
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	lr, [lr]
	stmia	ip!, {r0, r1, r2, r3}
	add	r0, sp, #48
	mov	r2, #8
	mov	r1, #5
	str	lr, [ip]
	bl	exponential_search.part.0
	cmp	r0, #4
	bne	.L59
	add	lr, r4, #20
	add	ip, sp, #68
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	lr, [lr]
	stmia	ip!, {r0, r1, r2, r3}
	add	r0, sp, #68
	mov	r2, #6
	mov	r1, #5
	str	lr, [ip]
	bl	exponential_search.part.0
	cmp	r0, #3
	bne	.L60
	mov	r0, r5
	add	sp, sp, #88
	@ sp needed
	pop	{r4, r5, r6, r8, r9, pc}
.L54:
	movw	r1, #:lower16:.LC3
	movw	r0, #:lower16:.LC4
	add	r3, r4, #12
	movt	r1, #:upper16:.LC3
	movt	r0, #:upper16:.LC4
	mov	r2, #89
	bl	__assert_fail
.L60:
	movw	r1, #:lower16:.LC3
	movw	r0, #:lower16:.LC10
	add	r3, r4, #12
	movt	r1, #:upper16:.LC3
	movt	r0, #:upper16:.LC10
	mov	r2, #107
	bl	__assert_fail
.L59:
	movw	r1, #:lower16:.LC3
	movw	r0, #:lower16:.LC9
	add	r3, r4, #12
	movt	r1, #:upper16:.LC3
	movt	r0, #:upper16:.LC9
	mov	r2, #104
	bl	__assert_fail
.L58:
	movw	r1, #:lower16:.LC3
	movw	r0, #:lower16:.LC8
	add	r3, r4, #12
	movt	r1, #:upper16:.LC3
	movt	r0, #:upper16:.LC8
	mov	r2, #101
	bl	__assert_fail
.L57:
	movw	r1, #:lower16:.LC3
	movw	r0, #:lower16:.LC7
	add	r3, r4, #12
	movt	r1, #:upper16:.LC3
	movt	r0, #:upper16:.LC7
	mov	r2, #98
	bl	__assert_fail
.L56:
	movw	r1, #:lower16:.LC3
	movw	r0, #:lower16:.LC6
	add	r3, r4, #12
	movt	r1, #:upper16:.LC3
	movt	r0, #:upper16:.LC6
	mov	r2, #95
	bl	__assert_fail
.L55:
	movw	r1, #:lower16:.LC3
	movw	r0, #:lower16:.LC5
	add	r3, r4, #12
	movt	r1, #:upper16:.LC3
	movt	r0, #:upper16:.LC5
	mov	r2, #92
	bl	__assert_fail
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	1
	.word	2
	.word	3
	.type	__PRETTY_FUNCTION__.4935, %object
	.size	__PRETTY_FUNCTION__.4935, 5
__PRETTY_FUNCTION__.4935:
	.ascii	"test\000"
	.space	3
.LC2:
	.word	-1
	.word	2
	.word	4
	.word	6
	.word	8
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
