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
	.file	"partition_sort.c"
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
	.global	partition
	.syntax unified
	.arm
	.fpu softvfp
	.type	partition, %function
partition:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	ip, [r0, r1, lsl #2]
	push	{r4, r5, r6, r7, lr}
	sub	r5, r1, #1
	add	lr, r2, #1
	add	r4, r0, r1, lsl #2
	mov	r7, r0
.L4:
	ldr	r6, [r4], #4
	add	r5, r5, #1
	cmp	r6, ip
	blt	.L4
	sub	r0, lr, #1
	add	r3, r7, r0, lsl #2
	b	.L6
.L12:
	sub	r0, r0, #1
.L6:
	mov	r1, r3
	ldr	r2, [r3], #-4
	mov	lr, r0
	cmp	r2, ip
	bgt	.L12
	cmp	r5, r0
	popge	{r4, r5, r6, r7, pc}
	str	r2, [r4, #-4]
	str	r6, [r1]
	b	.L4
	.size	partition, .-partition
	.align	2
	.global	partitionSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	partitionSort, %function
partitionSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, r2
	bxge	lr
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	add	r6, r2, #1
	mov	r5, r2
	mov	r4, r0
.L19:
	ldr	r10, [r4, r1, lsl #2]
	sub	lr, r1, #1
	add	ip, r4, r1, lsl #2
	mov	r0, r6
.L15:
	ldr	r8, [ip], #4
	add	lr, lr, #1
	cmp	r10, r8
	bgt	.L15
	sub	r2, r0, #1
	add	r3, r4, r2, lsl #2
	b	.L17
.L28:
	sub	r2, r2, #1
.L17:
	mov	fp, r3
	ldr	r9, [r3], #-4
	mov	r7, r0
	mov	r0, r2
	cmp	r10, r9
	blt	.L28
	cmp	lr, r2
	strlt	r9, [ip, #-4]
	strlt	r8, [fp]
	blt	.L15
.L29:
	mov	r0, r4
	bl	partitionSort
	cmp	r5, r7
	pople	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	mov	r1, r7
	b	.L19
	.size	partitionSort, .-partitionSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
	.text
	.align	2
	.global	printArray
	.syntax unified
	.arm
	.fpu softvfp
	.type	printArray, %function
printArray:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r5, r1, #0
	ble	.L31
	movw	r6, #:lower16:.LC0
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC0
	mov	r4, r0
.L32:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L32
.L31:
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	printArray, .-printArray
	.section	.rodata.str1.4
	.align	2
.LC1:
	.ascii	"Array: \000"
	.align	2
.LC2:
	.ascii	"Sorted Array: \000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	sub	sp, sp, #84
	movw	r4, #34079
	sub	r7, sp, #4
	movt	r4, 20971
	add	r6, sp, #76
	mov	r5, #100
.L36:
	bl	rand
	smull	r3, r2, r4, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r5, r3, r0
	add	r0, r0, #1
	str	r0, [r7, #4]!
	cmp	r7, r6
	bne	.L36
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	puts
	mov	r0, sp
	mov	r1, #20
	bl	printArray
	mov	r2, #19
	mov	r0, sp
	mov	r1, #0
	bl	partitionSort
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	puts
	mov	r0, sp
	mov	r1, #20
	bl	printArray
	mov	r0, #0
	add	sp, sp, #84
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
