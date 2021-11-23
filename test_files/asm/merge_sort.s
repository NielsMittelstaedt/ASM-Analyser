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
	.global	swap
	.syntax unified
	.arm
	.fpu softvfp
	.type	swap, %function
swap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, [r0]
	ldr	r2, [r1]
	str	r2, [r0]
	str	r3, [r1]
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	merge
	.syntax unified
	.arm
	.fpu softvfp
	.type	merge, %function
merge:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r5, r0
	lsl	r0, r3, #2
	mov	r8, r1
	mov	r4, r2
	bl	malloc
	add	r2, r8, r4
	add	r2, r2, r2, lsr #31
	asr	r2, r2, #1
	add	r10, r2, #1
	cmp	r2, r8
	mov	r3, r10
	mov	r9, r0
	add	r0, r4, #1
	blt	.L16
	cmp	r4, r10
	blt	.L5
	sub	r1, r9, #4
	mov	lr, r8
	mov	ip, r8
	b	.L8
.L23:
	cmp	r3, r4
	bgt	.L22
.L8:
	ldr	r7, [r5, lr, lsl #2]
	add	ip, ip, #1
	ldr	r6, [r5, r3, lsl #2]
	cmp	r7, r6
	strle	r7, [r1, ip, lsl #2]
	addle	lr, lr, #1
	addgt	r3, r3, #1
	strgt	r6, [r1, ip, lsl #2]
	cmp	r2, lr
	bge	.L23
.L4:
	cmp	r3, r0
	beq	.L13
	cmp	r4, r3
	blt	.L13
	sub	r2, r0, r3
	add	r1, r5, r3, lsl #2
	add	r0, r9, ip, lsl #2
	lsl	r2, r2, #2
	bl	memcpy
.L13:
	sub	r4, r4, r8
	cmp	r8, r4
	bgt	.L12
	sub	r4, r4, r8
	lsl	r1, r8, #2
	add	r2, r4, #1
	add	r0, r5, r1
	add	r1, r9, r1
	lsl	r2, r2, #2
	bl	memcpy
.L12:
	mov	r0, r9
	pop	{r4, r5, r6, r7, r8, r9, r10, lr}
	b	free
.L22:
	cmp	r3, r0
	bne	.L13
.L15:
	cmp	r2, lr
	sub	r10, r10, lr
	add	r0, r9, ip, lsl #2
	add	r1, r5, lr, lsl #2
	lslge	r2, r10, #2
	movlt	r2, #4
	bl	memcpy
	b	.L13
.L16:
	mov	ip, r8
	b	.L4
.L5:
	cmp	r2, r4
	bne	.L13
	mov	lr, r8
	mov	ip, r8
	b	.L15
	.size	merge, .-merge
	.align	2
	.global	merge_sort
	.syntax unified
	.arm
	.fpu softvfp
	.type	merge_sort, %function
merge_sort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r4, r3
	sub	r3, r3, r2
	mov	r5, r2
	cmp	r3, #1
	mov	r6, r0
	beq	.L28
	cmp	r4, r2
	popeq	{r4, r5, r6, r7, r8, pc}
	add	r8, r4, r2
	mov	r7, r1
	add	r8, r8, r8, lsr #31
	asr	r8, r8, #1
	mov	r3, r8
	bl	merge_sort
	add	r2, r8, #1
	mov	r3, r4
	mov	r1, r7
	mov	r0, r6
	bl	merge_sort
	mov	r3, r7
	mov	r2, r4
	mov	r1, r5
	mov	r0, r6
	pop	{r4, r5, r6, r7, r8, lr}
	b	merge
.L28:
	ldr	r3, [r0, r2, lsl #2]
	ldr	r2, [r0, r4, lsl #2]
	cmp	r3, r2
	strgt	r2, [r0, r5, lsl #2]
	strgt	r3, [r0, r4, lsl #2]
	pop	{r4, r5, r6, r7, r8, pc}
	.size	merge_sort, .-merge_sort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	" %d\000"
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
	push	{r4, r5, r6, r7, r8, lr}
	mov	r0, #24
	bl	malloc
	mov	r1, #6
	mov	r3, #5
	mov	r2, #4
	movw	r6, #:lower16:.LC0
	movt	r6, #:upper16:.LC0
	str	r2, [r0, #8]
	mov	r2, #3
	str	r1, [r0]
	mov	r5, r0
	str	r2, [r0, #12]
	mov	r2, #2
	str	r3, [r0, #4]
	sub	r4, r5, #4
	str	r2, [r0, #16]
	mov	r2, #1
	str	r2, [r0, #20]
	mov	r2, #0
	bl	merge_sort
	add	r7, r5, #20
.L30:
	ldr	r2, [r4, #4]!
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r7, r4
	bne	.L30
	mov	r0, r5
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
