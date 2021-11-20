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
	.file	"merge_sort.c"
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	mergeSort.part.0, %function
mergeSort.part.0:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	lsr	r8, r1, #1
	mov	fp, r0
	sub	r7, r1, r1, lsr #1
	lsl	r4, r8, #2
	lsl	r5, r7, #2
	mov	r0, r4
	bl	malloc
	mov	r9, r0
	mov	r0, r5
	bl	malloc
	cmp	r8, #0
	mov	r1, fp
	movgt	r2, r4
	movle	r2, #4
	mov	r10, r0
	mov	r0, r9
	bl	memcpy
	cmp	r7, #0
	ble	.L5
	add	r1, fp, r4
	mov	r2, r5
	mov	r0, r10
	bl	memcpy
.L5:
	cmp	r8, #1
	beq	.L3
	mov	r1, r8
	mov	r0, r9
	bl	mergeSort.part.0
.L3:
	cmp	r7, #1
	bls	.L6
	mov	r1, r7
	mov	r0, r10
	bl	mergeSort.part.0
.L6:
	cmp	r7, #0
	movle	r4, #0
	movle	r5, r4
	movle	r6, r4
	ble	.L8
	ldr	r2, [r9]
	mov	r4, #0
	ldr	r3, [r10]
	mov	r6, r4
	mov	r5, r4
.L7:
	cmp	r2, r3
	bhi	.L10
.L26:
	add	r5, r5, #1
	str	r2, [fp, r4, lsl #2]
	cmp	r8, r5
	cmpgt	r7, r6
	add	r4, r4, #1
	ble	.L12
	ldr	r2, [r9, r5, lsl #2]
	cmp	r2, r3
	bls	.L26
.L10:
	add	r6, r6, #1
	str	r3, [fp, r4, lsl #2]
	cmp	r8, r5
	cmpgt	r7, r6
	add	r4, r4, #1
	ldrgt	r3, [r10, r6, lsl #2]
	bgt	.L7
.L12:
	cmp	r8, r5
	ble	.L9
.L8:
	sub	r2, r8, r5
	add	r0, fp, r4, lsl #2
	add	r1, r9, r5, lsl #2
	add	r4, r8, r4
	lsl	r2, r2, #2
	sub	r4, r4, r5
	bl	memcpy
.L9:
	cmp	r7, r6
	ble	.L14
	sub	r2, r7, r6
	add	r1, r10, r6, lsl #2
	add	r0, fp, r4, lsl #2
	lsl	r2, r2, #2
	bl	memcpy
.L14:
	mov	r0, r9
	bl	free
	mov	r0, r10
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	free
	.size	mergeSort.part.0, .-mergeSort.part.0
	.align	2
	.global	mergeSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	mergeSort, %function
mergeSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #1
	bxls	lr
	b	mergeSort.part.0
	.size	mergeSort, .-mergeSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"%d \000"
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
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #24
	ldmia	ip!, {r0, r1, r2, r3}
	mov	lr, sp
	movw	r5, #:lower16:.LC1
	add	r6, sp, #24
	movt	r5, #:upper16:.LC1
	mov	r4, sp
	stmia	lr!, {r0, r1, r2, r3}
	ldm	ip, {r0, r1}
	stm	lr, {r0, r1}
	mov	r0, sp
	mov	r1, #6
	bl	mergeSort.part.0
.L30:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L30
	mov	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	5
	.word	3
	.word	0
	.word	2
	.word	6
	.word	1
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
