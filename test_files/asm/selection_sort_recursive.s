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
	.file	"selection_sort_recursive.c"
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	findIndex.part.0, %function
findIndex.part.0:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	sub	r5, r1, #1
	mov	r6, r1
	mov	r4, r0
	uxtb	r5, r5
	cmp	r5, #1
	beq	.L4
	mov	r1, r5
	bl	findIndex.part.0
	add	r3, r4, r0
.L2:
	add	r4, r4, r6
	ldrsb	r3, [r3]
	ldrsb	r2, [r4, #-1]
	cmp	r2, r3
	movlt	r0, r5
	pop	{r4, r5, r6, pc}
.L4:
	mov	r3, r0
	mov	r0, #0
	b	.L2
	.size	findIndex.part.0, .-findIndex.part.0
	.align	2
	.global	swap
	.syntax unified
	.arm
	.fpu softvfp
	.type	swap, %function
swap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldrsb	r3, [r0]
	ldrsb	r2, [r1]
	strb	r2, [r0]
	strb	r3, [r1]
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	findIndex
	.syntax unified
	.arm
	.fpu softvfp
	.type	findIndex, %function
findIndex:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	beq	.L21
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	r7, r1, #1
	mov	r4, r0
	mov	r6, r1
	uxtb	r7, r7
	cmp	r7, #1
	ldrsbeq	r3, [r0]
	moveq	r0, #0
	beq	.L11
	sub	r5, r1, #2
	uxtb	r5, r5
	cmp	r5, #1
	ldrsbeq	r3, [r4]
	moveq	r0, #0
	beq	.L13
	sub	r8, r1, #3
	uxtb	r8, r8
	cmp	r8, #1
	ldrsbeq	r3, [r4]
	moveq	r0, #0
	beq	.L15
	sub	r9, r1, #4
	uxtb	r9, r9
	cmp	r9, #1
	ldrsbeq	r3, [r4]
	moveq	r0, #0
	beq	.L17
	sub	r10, r1, #5
	uxtb	r10, r10
	cmp	r10, #1
	ldrsbeq	r3, [r4]
	moveq	r0, #0
	beq	.L19
	sub	fp, r1, #6
	uxtb	fp, fp
	cmp	fp, #1
	beq	.L22
	mov	r1, fp
	bl	findIndex.part.0
	add	r3, r4, r0
.L20:
	add	r2, r4, r10
	ldrsb	r3, [r3]
	ldrsb	r2, [r2, #-1]
	cmp	r2, r3
	ldrsblt	r3, [r4, fp]
	movlt	r0, fp
.L19:
	add	r2, r4, r9
	ldrsb	r2, [r2, #-1]
	cmp	r2, r3
	ldrsblt	r3, [r4, r10]
	movlt	r0, r10
.L17:
	add	r2, r4, r8
	ldrsb	r2, [r2, #-1]
	cmp	r2, r3
	ldrsblt	r3, [r4, r9]
	movlt	r0, r9
.L15:
	add	r2, r4, r5
	ldrsb	r2, [r2, #-1]
	cmp	r2, r3
	ldrsblt	r3, [r4, r8]
	movlt	r0, r8
.L13:
	add	r2, r4, r7
	ldrsb	r2, [r2, #-1]
	cmp	r2, r3
	ldrsblt	r3, [r4, r5]
	movlt	r0, r5
.L11:
	add	r4, r4, r6
	ldrsb	r2, [r4, #-1]
	cmp	r2, r3
	movlt	r0, r7
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L21:
	mov	r0, #0
	bx	lr
.L22:
	mov	r3, r4
	mov	r0, #0
	b	.L20
	.size	findIndex, .-findIndex
	.align	2
	.global	selectionSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	selectionSort, %function
selectionSort:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxls	lr
	sub	r1, r1, #1
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	uxtb	r7, r1
	sub	sp, sp, #12
	mov	r4, r0
	b	.L29
.L30:
	sub	r8, r5, #1
	uxtb	r8, r8
	cmp	r8, #1
	beq	.L54
	sub	r9, r5, #2
	uxtb	r9, r9
	cmp	r9, #1
	beq	.L55
	sub	r10, r5, #3
	uxtb	r10, r10
	cmp	r10, #1
	beq	.L56
	sub	fp, r5, #4
	uxtb	fp, fp
	cmp	fp, #1
	beq	.L57
	sub	r1, r5, #5
	uxtb	r1, r1
	cmp	r1, #1
	beq	.L46
	mov	r0, r4
	str	r1, [sp, #4]
	bl	findIndex.part.0
	ldr	r1, [sp, #4]
	add	r2, r4, r0
.L39:
	add	ip, r4, fp
	ldrsb	r3, [r2]
	ldrsb	ip, [ip, #-1]
	cmp	ip, r3
	addlt	r2, r4, r1
	ldrsblt	r3, [r4, r1]
	movlt	r0, r1
.L38:
	add	r1, r4, r10
	ldrsb	r1, [r1, #-1]
	cmp	r1, r3
	addlt	r2, r4, fp
	ldrsblt	r3, [r4, fp]
	movlt	r0, fp
.L36:
	add	r1, r4, r9
	ldrsb	r1, [r1, #-1]
	cmp	r1, r3
	addlt	r2, r4, r10
	ldrsblt	r3, [r4, r10]
	movlt	r0, r10
.L34:
	add	r1, r4, r8
	ldrsb	r1, [r1, #-1]
	cmp	r1, r3
	addlt	r2, r4, r9
	ldrsblt	r3, [r4, r9]
	movlt	r0, r9
.L32:
	add	ip, r4, r7
	ldrsb	r1, [ip, #-1]
	cmp	r1, r3
	add	r1, r4, r6
	bge	.L40
	ldrsb	r3, [r4, r8]
	add	r2, r4, r8
	ldrsb	r1, [r1, #-1]
	cmp	r1, r3
	bge	.L42
.L41:
	ldrsb	r3, [ip]
	mov	r2, ip
	ldrsb	r1, [r4]
.L44:
	cmp	r5, #1
	strb	r3, [r4]
	strb	r1, [r2]
	bls	.L27
.L45:
	add	r4, r4, #1
	sub	r7, r7, #1
.L29:
	uxtb	r5, r7
	add	r1, r5, #1
	cmp	r5, #1
	uxtb	r6, r1
	bne	.L30
	ldrsb	r2, [r4, #1]
	ldrsb	r3, [r4]
	cmp	r2, r3
	strblt	r2, [r4]
	strblt	r3, [r4, #1]
.L27:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L40:
	ldrsb	r1, [r1, #-1]
	cmp	r1, r3
	blt	.L41
	cmp	r0, #0
	beq	.L45
.L42:
	ldrsb	r1, [r4]
	b	.L44
.L54:
	ldrsb	r3, [r4]
	mov	r2, r4
	mov	r0, #0
	b	.L32
.L55:
	ldrsb	r3, [r4]
	mov	r2, r4
	mov	r0, #0
	b	.L34
.L56:
	ldrsb	r3, [r4]
	mov	r2, r4
	mov	r0, #0
	b	.L36
.L57:
	ldrsb	r3, [r4]
	mov	r2, r4
	mov	r0, #0
	b	.L38
.L46:
	mov	r2, r4
	mov	r0, #0
	b	.L39
	.size	selectionSort, .-selectionSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d\012\000"
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
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r0, #0
	bl	time
	movw	r8, #34079
	bl	srand
	mov	r1, #1
	mov	r0, #10
	movt	r8, 20971
	bl	calloc
	mov	r7, #100
	sub	r5, r0, #1
	add	r6, r0, #9
	mov	r4, r0
	mov	r9, r5
.L59:
	bl	rand
	smull	r3, r2, r8, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r7, r3, r0
	strb	r0, [r9, #1]!
	cmp	r9, r6
	bne	.L59
	mov	r1, #10
	mov	r0, r4
	bl	selectionSort
	movw	r7, #:lower16:.LC0
	movt	r7, #:upper16:.LC0
.L60:
	ldrsb	r2, [r5, #1]!
	mov	r1, r7
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r6
	bne	.L60
	mov	r0, r4
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
