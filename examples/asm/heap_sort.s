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
	.file	"heap_sort.c"
	.text
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
	ldr	r3, [r0, r1, lsl #2]
	ldr	ip, [r0, r2, lsl #2]
	str	ip, [r0, r1, lsl #2]
	str	r3, [r0, r2, lsl #2]
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	heapify
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapify, %function
heapify:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	b	.L7
.L12:
	ldr	r4, [r0, lr, lsl #2]
	ldr	r5, [r0, r2, lsl #2]
	cmp	r5, r4
	bcs	.L4
	cmp	r1, r3
	bhi	.L11
.L9:
	mov	ip, lr
	mov	r3, lr
.L5:
	cmp	r3, r2
	popeq	{r4, r5, pc}
.L13:
	ldr	r4, [r0, r2, lsl #2]
	ldr	lr, [r0, ip, lsl #2]
	str	r4, [r0, ip, lsl #2]
	str	lr, [r0, r2, lsl #2]
	mov	r2, r3
.L7:
	lsl	r3, r2, #1
	add	lr, r3, #1
	add	r3, r3, #2
	cmp	lr, r1
	mov	ip, r3
	bcc	.L12
.L4:
	cmp	r1, r3
	popls	{r4, r5, pc}
	ldr	r4, [r0, r2, lsl #2]
	ldr	lr, [r0, r3, lsl #2]
	cmp	r4, lr
	popcs	{r4, r5, pc}
	cmp	r3, r2
	bne	.L13
	pop	{r4, r5, pc}
.L11:
	ldr	r5, [r0, r3, lsl #2]
	cmp	r4, r5
	bcs	.L9
	b	.L5
	.size	heapify, .-heapify
	.align	2
	.global	heapSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapSort, %function
heapSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	lsr	r4, r1, #1
	cmp	r4, #0
	beq	.L15
	sub	r4, r4, #1
.L16:
	mov	r2, r4
	sub	r4, r4, #1
	bl	heapify
	cmn	r4, #1
	bne	.L16
.L15:
	subs	r5, r1, #1
	popeq	{r4, r5, r6, pc}
	add	r4, r0, r1, lsl #2
	add	r6, r0, #4
.L18:
	ldr	ip, [r4, #-4]!
	mov	r1, r5
	ldr	r3, [r0]
	mov	r2, #0
	sub	r5, r5, #1
	str	ip, [r0]
	str	r3, [r4]
	bl	heapify
	cmp	r6, r4
	bne	.L18
	pop	{r4, r5, r6, pc}
	.size	heapSort, .-heapSort
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
	bl	heapSort
.L29:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L29
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
