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
	.file	"exponential_search.c"
	.text
	.align	2
	.global	exponential_search
	.syntax unified
	.arm
	.fpu softvfp
	.type	exponential_search, %function
exponential_search:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #32
	str	r0, [fp, #-16]
	strd	r2, [fp, #-28]
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-18]	@ movhi
	ldrh	r3, [fp, #-18]
	cmp	r3, #0
	bne	.L2
	mvn	r2, #0
	mvn	r3, #0
	b	.L3
.L2:
	mov	r3, #1
	str	r3, [fp, #-8]
	b	.L4
.L6:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #1
	str	r3, [fp, #-8]
.L4:
	ldrh	r3, [fp, #-18]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	bhi	.L5
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #3
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-28]
	cmp	r0, r2
	sbcs	r3, r1, r3
	blt	.L6
.L5:
	ldr	r3, [fp, #-8]
	lsr	r3, r3, #1
	strh	r3, [fp, #-10]	@ movhi
	ldrh	r3, [fp, #-18]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	bls	.L7
	ldrh	r3, [fp, #-18]
	str	r3, [fp, #-8]
.L7:
	ldr	r3, [fp, #-8]
	uxth	r0, r3
	ldrh	r1, [fp, #-10]
	ldrd	r2, [fp, #-28]
	strd	r2, [sp]
	mov	r2, r0
	ldr	r0, [fp, #-16]
	bl	binary_search
	mov	r2, r0
	mov	r3, r1
.L3:
	mov	r0, r2
	mov	r1, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	exponential_search, .-exponential_search
	.align	2
	.global	binary_search
	.syntax unified
	.arm
	.fpu softvfp
	.type	binary_search, %function
binary_search:
	@ args = 8, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	mov	r3, r1
	strh	r3, [fp, #-18]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-20]	@ movhi
	ldrh	r2, [fp, #-20]
	ldrh	r3, [fp, #-18]
	sub	r3, r2, r3
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	uxth	r2, r3
	ldrh	r3, [fp, #-18]	@ movhi
	add	r3, r2, r3
	strh	r3, [fp, #-6]	@ movhi
	ldrh	r2, [fp, #-18]
	ldrh	r3, [fp, #-20]
	cmp	r2, r3
	bls	.L9
	mvn	r2, #0
	mvn	r3, #0
	b	.L10
.L9:
	ldrh	r3, [fp, #-6]
	lsl	r3, r3, #3
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldrd	r2, [r3]
	ldrd	r0, [fp, #4]
	cmp	r1, r3
	cmpeq	r0, r2
	bne	.L11
	ldrh	r2, [fp, #-6]
	mov	r3, #0
	b	.L10
.L11:
	ldrh	r3, [fp, #-6]
	lsl	r3, r3, #3
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldrd	r2, [r3]
	ldrd	r0, [fp, #4]
	cmp	r0, r2
	sbcs	r3, r1, r3
	bge	.L12
	ldrh	r3, [fp, #-6]	@ movhi
	sub	r3, r3, #1
	uxth	r0, r3
	ldrh	r1, [fp, #-18]
	ldrd	r2, [fp, #4]
	strd	r2, [sp]
	mov	r2, r0
	ldr	r0, [fp, #-16]
	bl	binary_search
	mov	r2, r0
	mov	r3, r1
	b	.L10
.L12:
	ldrh	r3, [fp, #-6]	@ movhi
	add	r3, r3, #1
	uxth	r1, r3
	ldrh	r0, [fp, #-20]
	ldrd	r2, [fp, #4]
	strd	r2, [sp]
	mov	r2, r0
	ldr	r0, [fp, #-16]
	bl	binary_search
	mov	r2, r0
	mov	r3, r1
.L10:
	mov	r0, r2
	mov	r1, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	binary_search, .-binary_search
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
.LC3:
	.ascii	"../test_files/c_in/exponential_search.c\000"
	.align	2
.LC4:
	.ascii	"exponential_search(arr_empty, 0, 10) == -1\000"
	.align	2
.LC5:
	.ascii	"exponential_search(arr_found, 3, 10) == -1\000"
	.align	2
.LC6:
	.ascii	"exponential_search(arr_found, 1, 1) == 0\000"
	.align	2
.LC7:
	.ascii	"exponential_search(arr_first_2, 2, 1) == 0\000"
	.align	2
.LC8:
	.ascii	"exponential_search(arr_last_2, 2, 2) == 1\000"
	.align	2
.LC9:
	.ascii	"exponential_search(arr_first_n, 5, -1) == 0\000"
	.align	2
.LC10:
	.ascii	"exponential_search(arr_last_n, 5, 8) == 4\000"
	.align	2
.LC11:
	.ascii	"exponential_search(arr_middle, 5, 6) == 3\000"
	.align	3
.LC0:
	.word	1
	.word	0
	.word	2
	.word	0
	.word	3
	.word	0
	.align	3
.LC1:
	.word	1
	.word	0
	.word	2
	.word	0
	.align	3
.LC2:
	.word	-1
	.word	-1
	.word	2
	.word	0
	.word	4
	.word	0
	.word	6
	.word	0
	.word	8
	.word	0
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 184
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #184
	mov	r2, #10
	mov	r3, #0
	mov	r1, #0
	sub	r0, fp, #4
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	mvn	r0, #0
	mvn	r1, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L16
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #85
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	__assert_fail
.L16:
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	sub	ip, fp, #28
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1}
	stm	ip, {r0, r1}
	sub	r0, fp, #28
	mov	r2, #10
	mov	r3, #0
	mov	r1, #3
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	mvn	r0, #0
	mvn	r1, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L17
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #88
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	__assert_fail
.L17:
	mov	r2, #1
	mov	r3, #0
	strd	r2, [fp, #-36]
	sub	r0, fp, #28
	mov	r2, #1
	mov	r3, #0
	mov	r1, #1
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	orrs	r3, r2, r3
	beq	.L18
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #91
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC6
	movt	r0, #:upper16:.LC6
	bl	__assert_fail
.L18:
	movw	r3, #:lower16:.LC1
	movt	r3, #:upper16:.LC1
	sub	ip, fp, #52
	ldm	r3, {r0, r1, r2, r3}
	stm	ip, {r0, r1, r2, r3}
	sub	r0, fp, #52
	mov	r2, #1
	mov	r3, #0
	mov	r1, #2
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	orrs	r3, r2, r3
	beq	.L19
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #94
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC7
	movt	r0, #:upper16:.LC7
	bl	__assert_fail
.L19:
	movw	r3, #:lower16:.LC1
	movt	r3, #:upper16:.LC1
	sub	ip, fp, #68
	ldm	r3, {r0, r1, r2, r3}
	stm	ip, {r0, r1, r2, r3}
	sub	r0, fp, #68
	mov	r2, #2
	mov	r3, #0
	mov	r1, #2
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	cmp	r3, #0
	cmpeq	r2, #1
	beq	.L20
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #97
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC8
	movt	r0, #:upper16:.LC8
	bl	__assert_fail
.L20:
	movw	r3, #:lower16:.LC2
	movt	r3, #:upper16:.LC2
	sub	ip, fp, #108
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1}
	stm	ip, {r0, r1}
	sub	r0, fp, #108
	mvn	r2, #0
	mvn	r3, #0
	mov	r1, #5
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	orrs	r3, r2, r3
	beq	.L21
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #100
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC9
	movt	r0, #:upper16:.LC9
	bl	__assert_fail
.L21:
	movw	r3, #:lower16:.LC2
	movt	r3, #:upper16:.LC2
	sub	ip, fp, #148
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1}
	stm	ip, {r0, r1}
	sub	r0, fp, #148
	mov	r2, #8
	mov	r3, #0
	mov	r1, #5
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	cmp	r3, #0
	cmpeq	r2, #4
	beq	.L22
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #103
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC10
	movt	r0, #:upper16:.LC10
	bl	__assert_fail
.L22:
	movw	r3, #:lower16:.LC2
	movt	r3, #:upper16:.LC2
	sub	ip, fp, #188
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1}
	stm	ip, {r0, r1}
	sub	r0, fp, #188
	mov	r2, #6
	mov	r3, #0
	mov	r1, #5
	bl	exponential_search
	mov	r2, r0
	mov	r3, r1
	cmp	r3, #0
	cmpeq	r2, #3
	beq	.L24
	movw	r3, #:lower16:__PRETTY_FUNCTION__.4359
	movt	r3, #:upper16:__PRETTY_FUNCTION__.4359
	mov	r2, #106
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movw	r0, #:lower16:.LC11
	movt	r0, #:upper16:.LC11
	bl	__assert_fail
.L24:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	test, .-test
	.section	.rodata
	.align	2
	.type	__PRETTY_FUNCTION__.4359, %object
	.size	__PRETTY_FUNCTION__.4359, 5
__PRETTY_FUNCTION__.4359:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
