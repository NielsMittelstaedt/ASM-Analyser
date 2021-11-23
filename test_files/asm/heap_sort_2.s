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
	.file	"heap_sort_2.c"
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapSort.part.0, %function
heapSort.part.0:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, r7, lr}
	movhi	r4, #1
	bls	.L5
.L2:
	mov	r3, r4
	b	.L4
.L6:
	cmp	r3, #0
	strb	ip, [r0, r3]
	strb	r2, [r0, lr]
	beq	.L7
.L4:
	mov	lr, r3
	ubfx	r3, r3, #1, #8
	ldrsb	ip, [r0, lr]
	ldrsb	r2, [r0, r3]
	cmp	ip, r2
	bgt	.L6
.L7:
	add	r4, r4, #1
	uxtb	r4, r4
	cmp	r4, r1
	bne	.L2
.L5:
	sub	r1, r1, #1
	uxtb	r6, r1
.L3:
	ldrsb	r1, [r0, r6]
	cmp	r6, #1
	ldrsb	r2, [r0]
	sub	r3, r6, #1
	mov	r4, r6
	strb	r1, [r0]
	strb	r2, [r0, r6]
	uxtb	r6, r3
	beq	.L8
	ldrsb	r5, [r0]
	mov	r1, #0
	mov	r3, r1
	mov	lr, r1
.L11:
	lsl	r2, lr, #1
	add	r3, r3, #1
	add	r1, r0, r1
	uxtb	r2, r2
	cmp	r4, r3, lsl #1
	add	ip, r2, #1
	uxtb	r3, ip
	uxtab	ip, r0, ip
	ldrsb	r7, [r0, r3]
	ble	.L9
	ldrsb	r1, [r1, #2]
	add	r2, r2, #2
	cmp	r1, r7
	uxtbgt	r3, r2
	addgt	ip, r0, r3
	ldrsbgt	r7, [r0, r3]
.L9:
	cmp	r5, r7
	lsl	r1, r3, #1
	add	r2, r1, #1
	bge	.L3
	cmp	r2, r4
	strb	r7, [r0, lr]
	mov	lr, r3
	strb	r5, [ip]
	blt	.L11
	b	.L3
.L8:
	cmp	r6, #0
	popeq	{r4, r5, r6, r7, pc}
	b	.L3
	.size	heapSort.part.0, .-heapSort.part.0
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
	.global	heapifyDown
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapifyDown, %function
heapifyDown:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	push	{r4, r5, r6, lr}
	mov	r4, #0
	ldrsb	r5, [r0]
	mov	lr, r4
	mov	r3, r4
.L24:
	lsl	r2, r4, #1
	add	r3, r3, #1
	add	lr, r0, lr
	uxtb	r2, r2
	cmp	r1, r3, lsl #1
	add	ip, r2, #1
	uxtb	r3, ip
	uxtab	ip, r0, ip
	ldrsb	r6, [r0, r3]
	ble	.L22
	ldrsb	lr, [lr, #2]
	add	r2, r2, #2
	cmp	lr, r6
	uxtbgt	r3, r2
	addgt	ip, r0, r3
	ldrsbgt	r6, [r0, r3]
.L22:
	cmp	r5, r6
	lsl	lr, r3, #1
	add	r2, lr, #1
	popge	{r4, r5, r6, pc}
	cmp	r2, r1
	strb	r6, [r0, r4]
	mov	r4, r3
	strb	r5, [ip]
	blt	.L24
	pop	{r4, r5, r6, pc}
	.size	heapifyDown, .-heapifyDown
	.align	2
	.global	heapifyUp
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapifyUp, %function
heapifyUp:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #0
	bxeq	lr
.L31:
	mov	ip, r1
	lsr	r1, r1, #1
	ldrsb	r3, [r0, ip]
	ldrsb	r2, [r0, r1]
	cmp	r2, r3
	bxge	lr
	cmp	r1, #0
	strb	r3, [r0, r1]
	strb	r2, [r0, ip]
	bne	.L31
	bx	lr
	.size	heapifyUp, .-heapifyUp
	.align	2
	.global	heapSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapSort, %function
heapSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #1
	bxls	lr
	b	heapSort.part.0
	.size	heapSort, .-heapSort
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
.L42:
	bl	rand
	smull	r3, r2, r8, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r7, r3, r0
	strb	r0, [r9, #1]!
	cmp	r9, r6
	bne	.L42
	mov	r1, #10
	mov	r0, r4
	bl	heapSort.part.0
	movw	r7, #:lower16:.LC0
	movt	r7, #:upper16:.LC0
.L43:
	ldrsb	r2, [r5, #1]!
	mov	r1, r7
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r6
	bne	.L43
	mov	r0, r4
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
