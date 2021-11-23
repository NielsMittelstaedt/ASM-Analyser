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
	.file	"bubble_sort_recursion.c"
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
	.global	bubbleSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	bubbleSort, %function
bubbleSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, lr}
	add	lr, r0, r1, lsl #2
	sub	lr, lr, #4
	popeq	{r4, pc}
.L15:
	sub	r1, r1, #1
	cmp	r1, #0
	pople	{r4, pc}
	mov	r3, r0
	mov	r4, #0
.L6:
	ldr	r2, [r3]
	ldr	ip, [r3, #4]!
	cmp	r2, ip
	strgt	ip, [r3, #-4]
	movgt	r4, #1
	strgt	r2, [r3]
	cmp	lr, r3
	bne	.L6
	cmp	r4, #0
	sub	lr, lr, #4
	popeq	{r4, pc}
	cmp	r1, #1
	bne	.L15
	pop	{r4, pc}
	.size	bubbleSort, .-bubbleSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"../test_files/c_in/bubble_sort_recursion.c\000"
	.align	2
.LC1:
	.ascii	"arr[i] <= arr[i + 1]\000"
	.text
	.align	2
	.global	test
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r1, #4
	mov	r0, #10
	movw	r5, #34079
	bl	calloc
	movt	r5, 20971
	mov	r6, #100
	sub	r8, r0, #4
	add	r7, r0, #36
	mov	r4, r0
.L17:
	bl	rand
	smull	r3, r2, r5, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r6, r3, r0
	str	r0, [r8, #4]!
	cmp	r8, r7
	bne	.L17
	ldr	lr, [r4]
	mov	r3, #10
	ldr	r1, [r4, #4]
.L18:
	cmp	lr, r1
	sub	r3, r3, #1
	ble	.L20
	cmp	r3, #1
	stm	r4, {r1, lr}
	mov	lr, r1
	beq	.L77
	ldr	r1, [r4, #4]
	mov	r2, #1
	ldr	r0, [r4, #8]
	cmp	r1, r0
	ble	.L21
.L78:
	cmp	r3, #2
	strd	r0, [r4, #4]
	mov	r1, r0
	movne	r2, #1
	ldrne	r0, [r4, #8]
	beq	.L18
	ldr	ip, [r4, #12]
	cmp	r0, ip
	ble	.L25
.L79:
	cmp	r3, #3
	str	ip, [r4, #8]
	str	r0, [r4, #12]
	movne	ip, r0
	movne	r2, #1
	beq	.L18
	ldr	r0, [r4, #16]
	cmp	ip, r0
	ble	.L27
.L80:
	cmp	r3, #4
	str	r0, [r4, #12]
	str	ip, [r4, #16]
	movne	r0, ip
	movne	r2, #1
	beq	.L18
	ldr	ip, [r4, #20]
	cmp	r0, ip
	ble	.L29
.L81:
	cmp	r3, #5
	str	ip, [r4, #16]
	str	r0, [r4, #20]
	movne	ip, r0
	movne	r2, #1
	beq	.L18
	ldr	r0, [r4, #24]
	cmp	ip, r0
	ble	.L31
.L82:
	cmp	r3, #6
	str	r0, [r4, #20]
	str	ip, [r4, #24]
	movne	r0, ip
	movne	r2, #1
	beq	.L18
	ldr	ip, [r4, #28]
	cmp	r0, ip
	ble	.L33
.L83:
	cmp	r3, #7
	str	ip, [r4, #24]
	str	r0, [r4, #28]
	movne	ip, r0
	movne	r2, #1
	beq	.L18
	ldr	r0, [r4, #32]
	cmp	ip, r0
	ble	.L35
.L84:
	cmp	r3, #9
	str	r0, [r4, #28]
	str	ip, [r4, #32]
	moveq	r0, ip
	moveq	r2, #1
	bne	.L18
.L36:
	ldr	ip, [r4, #36]
	cmp	r0, ip
	strgt	r0, [r4, #36]
	strgt	ip, [r4, #32]
	bgt	.L18
.L24:
	eor	r2, r2, #1
	cmp	r3, #1
	orreq	r2, r2, #1
	cmp	r2, #0
	beq	.L18
.L19:
	cmp	r1, lr
	blt	.L37
	ldr	r3, [r4, #8]
	cmp	r1, r3
	bgt	.L37
	ldr	r2, [r4, #12]
	cmp	r3, r2
	bgt	.L37
	ldr	r3, [r4, #16]
	cmp	r2, r3
	bgt	.L37
	ldr	r2, [r4, #20]
	cmp	r3, r2
	bgt	.L37
	ldr	r3, [r4, #24]
	cmp	r2, r3
	bgt	.L37
	ldr	r2, [r4, #28]
	cmp	r3, r2
	bgt	.L37
	ldr	r3, [r4, #32]
	cmp	r2, r3
	bgt	.L37
	ldr	r2, [r4, #36]
	cmp	r2, r3
	blt	.L37
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, lr}
	b	free
.L20:
	cmp	r3, #1
	beq	.L19
	ldr	r0, [r4, #8]
	mov	r2, #0
	cmp	r1, r0
	bgt	.L78
.L21:
	cmp	r3, #2
	beq	.L24
	ldr	ip, [r4, #12]
	cmp	r0, ip
	bgt	.L79
.L25:
	cmp	r3, #3
	beq	.L24
	ldr	r0, [r4, #16]
	cmp	ip, r0
	bgt	.L80
.L27:
	cmp	r3, #4
	beq	.L24
	ldr	ip, [r4, #20]
	cmp	r0, ip
	bgt	.L81
.L29:
	cmp	r3, #5
	beq	.L24
	ldr	r0, [r4, #24]
	cmp	ip, r0
	bgt	.L82
.L31:
	cmp	r3, #6
	beq	.L24
	ldr	ip, [r4, #28]
	cmp	r0, ip
	bgt	.L83
.L33:
	cmp	r3, #7
	beq	.L24
	ldr	r0, [r4, #32]
	cmp	ip, r0
	bgt	.L84
.L35:
	cmp	r3, #9
	beq	.L36
	b	.L24
.L77:
	ldr	r1, [r4, #4]
	b	.L19
.L37:
	movw	r3, #:lower16:.LANCHOR0
	movw	r1, #:lower16:.LC0
	movw	r0, #:lower16:.LC1
	movt	r3, #:upper16:.LANCHOR0
	movt	r1, #:upper16:.LC0
	movt	r0, #:upper16:.LC1
	mov	r2, #66
	bl	__assert_fail
	.size	test, .-test
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
	push	{r4, lr}
	mov	r0, #0
	bl	time
	bl	srand
	bl	test
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
	.type	__PRETTY_FUNCTION__.5581, %object
	.size	__PRETTY_FUNCTION__.5581, 5
__PRETTY_FUNCTION__.5581:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
