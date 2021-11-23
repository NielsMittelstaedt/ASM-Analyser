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
	.file	"cocktail_sort.c"
	.text
	.align	2
	.global	cocktailSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	cocktailSort, %function
cocktailSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r4, #0
	sub	r3, r1, #1
	mov	r6, r4
	mov	r1, r4
.L2:
	cmp	r1, r3
	sub	r5, r3, #1
	bge	.L20
.L5:
	add	r2, r0, r1, lsl #2
.L3:
	ldr	ip, [r2]
	add	r1, r1, #1
	ldr	lr, [r2, #4]!
	cmp	ip, lr
	ble	.L2
	cmp	r3, r1
	mov	r6, #1
	str	lr, [r2, #-4]
	str	ip, [r2]
	bgt	.L3
.L4:
	sub	r2, r3, #2
	cmp	r2, r4
	poplt	{r4, r5, r6, pc}
	sub	r3, r3, #1
	add	ip, r0, r4, lsl #2
	mov	lr, #0
	add	r3, r0, r3, lsl #2
.L8:
	ldr	r2, [r3]
	ldr	r1, [r3, #-4]!
	cmp	r2, r1
	strlt	r1, [r3, #4]
	movlt	lr, #1
	strlt	r2, [r3]
	cmp	ip, r3
	bne	.L8
	cmp	lr, #0
	add	r1, r4, #1
	popeq	{r4, r5, r6, pc}
	cmp	r1, r5
	popge	{r4, r5, r6, pc}
	mov	r3, r5
	mov	r4, r1
	sub	r5, r5, #1
	mov	r6, #0
	b	.L5
.L20:
	cmp	r6, #0
	popeq	{r4, r5, r6, pc}
	b	.L4
	.size	cocktailSort, .-cocktailSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"You entered:  \000"
	.align	2
.LC1:
	.ascii	"%d \000"
	.align	2
.LC2:
	.ascii	"\012Sorted array: \000"
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
	mov	r3, #1
	movw	r1, #:lower16:.LC0
	movt	r1, #:upper16:.LC0
	mov	ip, #6
	mov	r2, #5
	movw	r8, #:lower16:.LC1
	movt	r8, #:upper16:.LC1
	mov	r7, r0
	mov	r0, r3
	str	r3, [r7, #20]
	mov	r3, #4
	str	r2, [r7, #4]
	mov	r2, #3
	str	r3, [r7, #8]
	mov	r3, #2
	str	ip, [r7]
	sub	r4, r7, #4
	str	r2, [r7, #12]
	add	r6, r7, #20
	str	r3, [r7, #16]
	bl	__printf_chk
	mov	r5, r4
.L22:
	ldr	r2, [r5, #4]!
	mov	r1, r8
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r6
	bne	.L22
	mov	r1, #6
	mov	r0, r7
	bl	cocktailSort
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	movw	r5, #:lower16:.LC1
	movt	r5, #:upper16:.LC1
.L23:
	ldr	r2, [r4, #4]!
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L23
	mov	r0, #10
	bl	putchar
	mov	r0, r7
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
