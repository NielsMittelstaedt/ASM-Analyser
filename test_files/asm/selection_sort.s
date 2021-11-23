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
	.file	"selection_sort.c"
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
	.global	selectionSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	selectionSort, %function
selectionSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	add	r7, r0, #4
	sub	r10, r1, #1
	mov	r6, #0
.L8:
	mov	r8, r6
	add	r6, r6, #1
	cmp	r1, r6
	ble	.L5
	ldr	r9, [r7, #-4]
	mov	r2, r7
	mov	r3, r6
	mov	r5, r8
	mov	lr, r9
.L7:
	mov	r4, r2
	ldr	ip, [r2], #4
	cmp	ip, lr
	addge	r4, r0, r5, lsl #2
	movlt	r5, r3
	add	r3, r3, #1
	movlt	lr, ip
	cmp	r3, r1
	bne	.L7
	cmp	r8, r5
	strne	lr, [r7, #-4]
	strne	r9, [r4]
.L5:
	cmp	r6, r10
	add	r7, r7, #4
	bne	.L8
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	selectionSort, .-selectionSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"../test_files/c_in/selection_sort.c\000"
	.align	2
.LC1:
	.ascii	"arr[i] <= arr[i + 1]\000"
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
	movw	r4, #19923
	bl	srand
	movt	r4, 4194
	bl	rand
	mov	r3, #500
	mov	r1, #4
	smull	r2, r4, r4, r0
	asr	r2, r0, #31
	rsb	r4, r2, r4, asr #5
	mls	r4, r3, r4, r0
	mov	r0, r4
	bl	calloc
	cmp	r4, #0
	mov	r5, r0
	ble	.L18
	movw	r9, #34079
	add	r7, r0, r4, lsl #2
	movt	r9, 20971
	mov	r8, r0
	mov	r6, #100
.L19:
	bl	rand
	smull	r3, r2, r9, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r6, r3, r0
	sub	r0, r0, #50
	str	r0, [r8], #4
	cmp	r8, r7
	bne	.L19
.L18:
	mov	r1, r4
	mov	r0, r5
	bl	selectionSort
	cmp	r4, #1
	ble	.L20
	mov	r3, r5
	add	r4, r5, r4, lsl #2
	ldr	r2, [r3], #4
.L22:
	mov	r1, r2
	ldr	r2, [r3], #4
	cmp	r2, r1
	blt	.L26
	cmp	r4, r3
	bne	.L22
.L20:
	mov	r0, r5
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L26:
	movw	r3, #:lower16:.LANCHOR0
	movw	r1, #:lower16:.LC0
	movw	r0, #:lower16:.LC1
	movt	r3, #:upper16:.LANCHOR0
	movt	r1, #:upper16:.LC0
	movt	r0, #:upper16:.LC1
	mov	r2, #63
	bl	__assert_fail
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
	.type	__PRETTY_FUNCTION__.5585, %object
	.size	__PRETTY_FUNCTION__.5585, 5
__PRETTY_FUNCTION__.5585:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
