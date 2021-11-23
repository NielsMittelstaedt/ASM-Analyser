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
	.file	"quick_sort.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
	.text
	.align	2
	.global	display
	.syntax unified
	.arm
	.fpu softvfp
	.type	display, %function
display:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r5, r1, #0
	ble	.L2
	movw	r6, #:lower16:.LC0
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC0
	mov	r4, r0
.L3:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L3
.L2:
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	display, .-display
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
	.global	partition
	.syntax unified
	.arm
	.fpu softvfp
	.type	partition, %function
partition:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, r2
	push	{r4, r5, r6, r7, r8, lr}
	add	r7, r0, r2, lsl #2
	ldr	r6, [r0, r2, lsl #2]
	mov	lr, r0
	bge	.L12
	sub	r4, r1, #1
	add	r3, r0, r1, lsl #2
.L11:
	ldr	ip, [r3], #4
	add	r5, r4, #2
	mov	r0, r1
	cmp	ip, r6
	bgt	.L10
	ldr	r8, [lr, r1, lsl #2]
	mov	r4, r1
	str	ip, [lr, r1, lsl #2]
	add	r1, r1, #1
	mov	r0, r5
	str	r8, [r3, #-4]
.L10:
	cmp	r7, r3
	bne	.L11
	ldr	r6, [lr, r2, lsl #2]
.L9:
	ldr	r3, [lr, r1, lsl #2]
	str	r6, [lr, r1, lsl #2]
	str	r3, [lr, r2, lsl #2]
	pop	{r4, r5, r6, r7, r8, pc}
.L12:
	mov	r0, r1
	b	.L9
	.size	partition, .-partition
	.align	2
	.global	quickSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	quickSort, %function
quickSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, r2
	bxge	lr
	push	{r4, r5, r6, r7, r8, lr}
	add	r7, r0, r2, lsl #2
	mov	r6, r2
	mov	r5, r0
.L19:
	ldr	lr, [r7]
	sub	r4, r1, #1
	add	r0, r5, r1, lsl #2
	mov	r3, r1
.L18:
	ldr	ip, [r0], #4
	add	r3, r3, #1
	cmp	lr, ip
	addge	r4, r4, #1
	ldrge	r2, [r5, r4, lsl #2]
	strge	ip, [r5, r4, lsl #2]
	strge	r2, [r0, #-4]
	cmp	r6, r3
	bgt	.L18
	add	r3, r4, #1
	ldr	lr, [r7]
	mov	r2, r4
	mov	r0, r5
	ldr	ip, [r5, r3, lsl #2]
	str	lr, [r5, r3, lsl #2]
	str	ip, [r7]
	bl	quickSort
	add	r1, r4, #2
	cmp	r1, r6
	blt	.L19
	pop	{r4, r5, r6, r7, r8, pc}
	.size	quickSort, .-quickSort
	.section	.rodata.str1.4
	.align	2
.LC1:
	.ascii	"Original array: \000"
	.align	2
.LC2:
	.ascii	"Sorted array: \000"
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
	mov	r6, #1
	mov	r5, #6
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	mov	r2, #3
	mov	r7, #5
	mov	r3, #4
	mov	r4, r0
	mov	r0, r6
	str	r2, [r4, #12]
	str	r3, [r4, #8]
	mov	r3, #2
	str	r5, [r4]
	str	r3, [r4, #16]
	str	r7, [r4, #4]
	str	r6, [r4, #20]
	bl	__printf_chk
	mov	r1, r5
	mov	r0, r4
	bl	display
	mov	r2, r7
	mov	r0, r4
	mov	r1, #0
	bl	quickSort
	mov	r0, r6
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	mov	r0, r4
	mov	r1, r5
	bl	display
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
