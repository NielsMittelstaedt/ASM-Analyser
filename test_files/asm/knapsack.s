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
	.file	"knapsack.c"
	.text
	.align	2
	.global	max
	.syntax unified
	.arm
	.fpu softvfp
	.type	max, %function
max:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, r0
	movge	r0, r1
	bx	lr
	.size	max, .-max
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC2:
	.ascii	"%d\012\000"
	.align	2
.LC3:
	.ascii	"%d \000"
	.text
	.align	2
	.global	printknapSack
	.syntax unified
	.arm
	.fpu softvfp
	.type	printknapSack, %function
printknapSack:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	add	r4, r0, #1
	subs	r5, r3, #0
	add	fp, sp, #32
	mla	r3, r3, r4, r4
	sub	sp, sp, #36
	lsl	ip, r4, #2
	str	r0, [fp, #-60]
	str	ip, [fp, #-56]
	bic	ip, r4, #-1073741824
	str	r1, [fp, #-64]
	str	r2, [fp, #-68]
	lsl	r3, r3, #2
	str	ip, [fp, #-48]
	add	r3, r3, #7
	bic	r3, r3, #7
	sub	sp, sp, r3
	mov	r3, sp
	str	r3, [fp, #-40]
	blt	.L4
	cmp	r0, #0
	blt	.L5
	str	r3, [fp, #-44]
	sub	r9, r2, #4
	mvn	r3, #0
	sub	r6, r1, #4
	rsb	r8, ip, #0
	str	r5, [fp, #-52]
	mov	r7, #0
	mov	r5, r3
.L6:
	ldr	r3, [fp, #-48]
	mov	lr, r5
	ldr	r2, [fp, #-44]
	adds	r5, r5, #1
	mul	lr, lr, r3
	moveq	ip, #1
	movne	ip, #0
	mov	r3, #0
.L10:
	cmp	r3, #0
	movne	r1, ip
	moveq	r1, #1
	cmp	r1, #0
	strne	r7, [r2]
	bne	.L8
	ldr	r10, [r6]
	ldr	r0, [r2, r8, lsl #2]
	cmp	r10, r3
	sub	r1, r3, r10
	add	r1, lr, r1
	strgt	r0, [r2]
	bgt	.L8
	ldr	r10, [fp, #-40]
	ldr	r1, [r10, r1, lsl #2]
	ldr	r10, [r9]
	add	r1, r1, r10
	cmp	r1, r0
	movlt	r1, r0
	str	r1, [r2]
.L8:
	add	r3, r3, #1
	add	r2, r2, #4
	cmp	r3, r4
	bne	.L10
	ldr	r3, [fp, #-52]
	add	r9, r9, #4
	ldr	r2, [fp, #-56]
	add	r6, r6, #4
	cmp	r3, r5
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	str	r3, [fp, #-44]
	bne	.L6
	ldr	r5, [fp, #-52]
.L5:
	ldr	r3, [fp, #-48]
	movw	r1, #:lower16:.LC2
	ldr	r7, [fp, #-60]
	movt	r1, #:upper16:.LC2
	ldr	r2, [fp, #-40]
	mov	r0, #1
	mla	r3, r3, r5, r7
	ldr	r4, [r2, r3, lsl #2]
	mov	r2, r4
	bl	__printf_chk
	cmp	r5, #0
	movgt	r3, #1
	movle	r3, #0
	cmp	r4, #0
	movle	r3, #0
	andgt	r3, r3, #1
	cmp	r3, #0
	beq	.L3
	ldr	r8, [fp, #-64]
	movw	r6, #:lower16:.LC3
	ldr	r9, [fp, #-68]
	movt	r6, #:upper16:.LC3
.L11:
	ldr	r3, [fp, #-48]
	sub	r5, r5, #1
	ldr	r2, [fp, #-40]
	mov	r1, r6
	mov	r0, #1
	mla	r3, r3, r5, r7
	ldr	r3, [r2, r3, lsl #2]
	cmp	r3, r4
	beq	.L13
	ldr	r2, [r8, r5, lsl #2]
	bl	__printf_chk
	ldr	r3, [r9, r5, lsl #2]
	cmp	r5, #0
	ldr	r2, [r8, r5, lsl #2]
	sub	r4, r4, r3
	movgt	r3, #1
	movle	r3, #0
	cmp	r4, #0
	sub	r7, r7, r2
	andgt	r3, r3, #1
	movle	r3, #0
	cmp	r3, #0
	bne	.L11
.L3:
	sub	sp, fp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L13:
	cmp	r5, #0
	bgt	.L11
	sub	sp, fp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L4:
	mla	r5, ip, r5, r0
	ldr	r3, [fp, #-40]
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	ldr	r2, [r3, r5, lsl #2]
	bl	__printf_chk
	sub	sp, fp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	printknapSack, .-printknapSack
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #:lower16:.LANCHOR0
	movt	r3, #:upper16:.LANCHOR0
	push	{r4, lr}
	sub	sp, sp, #24
	ldm	r3, {r0, r1, r2}
	add	r4, r3, #12
	mov	lr, sp
	add	ip, sp, #12
	mov	r3, #3
	stm	lr, {r0, r1, r2}
	ldm	r4, {r0, r1, r2}
	stm	ip, {r0, r1, r2}
	mov	r2, lr
	mov	r1, ip
	mov	r0, #50
	bl	printknapSack
	mov	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	60
	.word	100
	.word	120
.LC1:
	.word	10
	.word	20
	.word	30
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
