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
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	mergeSort.part.0, %function
mergeSort.part.0:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	lsr	r4, r1, #1
	mov	r9, r0
	sub	r5, r1, r1, lsr #1
	lsl	r10, r4, #2
	lsl	r7, r5, #2
	mov	r0, r10
	bl	malloc
	mov	r8, r0
	mov	r0, r7
	bl	malloc
	sub	r1, r9, #4
	sub	r2, r8, #4
	mov	r3, #0
	mov	r6, r0
.L5:
	ldr	r0, [r1, #4]!
	add	r3, r3, #1
	cmp	r4, r3
	str	r0, [r2, #4]!
	bgt	.L5
	cmp	r5, #0
	ble	.L6
	add	r2, r9, r10
	add	r0, r7, r6
	mov	r3, r6
.L7:
	ldr	r1, [r2], #4
	str	r1, [r3], #4
	cmp	r0, r3
	bne	.L7
	mov	r1, r4
	mov	r0, r8
	bl	mergeSort
	mov	r0, r6
	mov	r1, r5
	bl	mergeSort
	mov	r0, #0
	mov	r3, r0
	mov	r2, r0
.L11:
	ldr	ip, [r8, r2, lsl #2]
	ldr	r1, [r6, r3, lsl #2]
	cmp	ip, r1
	strls	ip, [r9, r0, lsl #2]
	addls	r2, r2, #1
	addhi	r3, r3, #1
	strhi	r1, [r9, r0, lsl #2]
	cmp	r4, r2
	cmpgt	r5, r3
	add	r0, r0, #1
	bgt	.L11
	cmp	r4, r2
	ble	.L12
.L17:
	add	r10, r8, r10
	add	r1, r8, r2, lsl #2
	add	ip, r9, r0, lsl #2
.L13:
	ldr	lr, [r1], #4
	cmp	r10, r1
	str	lr, [ip], #4
	bne	.L13
	add	r0, r4, r0
	sub	r0, r0, r2
.L12:
	cmp	r5, r3
	ble	.L16
	add	r3, r6, r3, lsl #2
	add	r0, r9, r0, lsl #2
	add	r7, r6, r7
.L15:
	ldr	r2, [r3], #4
	cmp	r7, r3
	str	r2, [r0], #4
	bne	.L15
.L16:
	mov	r0, r8
	bl	free
	mov	r0, r6
	pop	{r4, r5, r6, r7, r8, r9, r10, lr}
	b	free
.L6:
	mov	r1, r4
	mov	r0, r8
	bl	mergeSort
	mov	r0, r6
	mov	r1, r5
	bl	mergeSort
	mov	r0, #0
	mov	r3, r0
	mov	r2, r0
	b	.L17
	.size	mergeSort.part.0, .-mergeSort.part.0
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
.L26:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L26
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
	.word	9
	.word	2
	.word	6
	.word	1
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
