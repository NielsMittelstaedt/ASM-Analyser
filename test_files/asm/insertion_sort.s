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
	.file	"insertion_sort.c"
	.text
	.align	2
	.global	insertionSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	insertionSort, %function
insertionSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	push	{r4, r5, r6, lr}
	sub	r6, r1, #1
	mov	r5, r0
	mov	r4, #0
.L6:
	ldr	lr, [r5, #4]!
	mov	r2, r4
	mov	r3, r5
.L3:
	ldr	r1, [r3, #-4]
	sub	r2, r2, #1
	mov	ip, r3
	cmp	r1, lr
	ble	.L4
	cmn	r2, #1
	str	r1, [r3]
	sub	r3, ip, #4
	bne	.L3
	mov	ip, r0
.L4:
	add	r4, r4, #1
	str	lr, [ip]
	cmp	r6, r4
	bne	.L6
	pop	{r4, r5, r6, pc}
	.size	insertionSort, .-insertionSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"../test_files/c_in/insertion_sort.c\000"
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
	ble	.L17
	movw	r9, #34079
	add	r7, r0, r4, lsl #2
	movt	r9, 20971
	mov	r8, r0
	mov	r6, #100
.L18:
	bl	rand
	smull	r3, r2, r9, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r6, r3, r0
	sub	r0, r0, #50
	str	r0, [r8], #4
	cmp	r8, r7
	bne	.L18
.L17:
	mov	r1, r4
	mov	r0, r5
	bl	insertionSort
	cmp	r4, #1
	ble	.L19
	mov	r3, r5
	add	r4, r5, r4, lsl #2
	ldr	r2, [r3], #4
.L21:
	mov	r1, r2
	ldr	r2, [r3], #4
	cmp	r2, r1
	blt	.L25
	cmp	r4, r3
	bne	.L21
.L19:
	mov	r0, r5
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L25:
	movw	r3, #:lower16:.LANCHOR0
	movw	r1, #:lower16:.LC0
	movw	r0, #:lower16:.LC1
	movt	r3, #:upper16:.LANCHOR0
	movt	r1, #:upper16:.LC0
	movt	r0, #:upper16:.LC1
	mov	r2, #49
	bl	__assert_fail
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
	.type	__PRETTY_FUNCTION__.5580, %object
	.size	__PRETTY_FUNCTION__.5580, 5
__PRETTY_FUNCTION__.5580:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
