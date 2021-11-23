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
	.file	"cycle_sort.c"
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
	.global	cycleSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	cycleSort, %function
cycleSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r4, #0
	sub	r8, r1, #1
	add	lr, r0, r1, lsl #2
	mov	r7, r4
	mov	r5, r0
.L20:
	mov	r6, r7
	add	r7, r7, #1
	cmp	r1, r7
	ldr	r9, [r5], #4
	ble	.L10
	mov	r3, r5
	mov	r2, r6
.L12:
	ldr	ip, [r3], #4
	cmp	r9, ip
	addgt	r2, r2, #1
	cmp	lr, r3
	bne	.L12
	cmp	r4, r2
	beq	.L10
	ldr	ip, [r0, r2, lsl #2]
	lsl	r3, r2, #2
	add	r10, r0, r3
	cmp	r9, ip
	bne	.L13
	add	r3, r3, #4
	add	r3, r0, r3
.L14:
	ldr	ip, [r3]
	mov	r10, r3
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r9, ip
	beq	.L14
	cmp	r4, r2
	beq	.L10
.L13:
	str	r9, [r10]
.L15:
	mov	r3, r5
	mov	r2, r6
.L17:
	ldr	r9, [r3], #4
	cmp	ip, r9
	addgt	r2, r2, #1
	cmp	r3, lr
	bne	.L17
	ldr	r9, [r0, r2, lsl #2]
	lsl	r3, r2, #2
	add	r10, r0, r3
	cmp	r9, ip
	bne	.L18
	add	r3, r3, #4
	add	r3, r0, r3
.L19:
	mov	r10, r3
	ldr	r9, [r3], #4
	add	r2, r2, #1
	cmp	r9, ip
	beq	.L19
.L18:
	cmp	r4, r2
	str	ip, [r10]
	movne	ip, r9
	bne	.L15
.L10:
	cmp	r8, r7
	add	r4, r4, #1
	bne	.L20
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	cycleSort, .-cycleSort
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
	push	{r4, r5, r6, lr}
	mov	r0, #24
	bl	malloc
	mov	r6, #1
	mov	r5, #6
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	mov	r2, #3
	mov	r3, #5
	mov	r4, r0
	mov	r0, r6
	str	r3, [r4, #4]
	mov	r3, #4
	str	r5, [r4]
	str	r3, [r4, #8]
	mov	r3, #2
	str	r6, [r4, #20]
	strd	r2, [r4, #12]
	bl	__printf_chk
	mov	r1, r5
	mov	r0, r4
	bl	display
	mov	r1, r5
	mov	r0, r4
	bl	cycleSort
	mov	r0, r6
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	mov	r1, r5
	mov	r0, r4
	bl	display
	mov	r0, r4
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
