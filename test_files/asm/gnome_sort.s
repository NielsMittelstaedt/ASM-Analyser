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
	.file	"gnome_sort.c"
	.text
	.align	2
	.global	sort
	.syntax unified
	.arm
	.fpu softvfp
	.type	sort, %function
sort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #0
	bxle	lr
	mov	r3, #0
	str	lr, [sp, #-4]!
.L5:
	lsl	r2, r3, #2
	sub	r2, r2, #4
	ldr	lr, [r0, r3, lsl #2]
	ldr	ip, [r0, r2]
	cmp	lr, ip
	addge	r3, r3, #1
	bge	.L4
	str	lr, [r0, r2]
	str	ip, [r0, r3, lsl #2]
	subs	r3, r3, #1
	moveq	r3, #1
.L4:
	cmp	r3, r1
	blt	.L5
	ldr	pc, [sp], #4
	.size	sort, .-sort
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
	ble	.L14
	movw	r6, #:lower16:.LC0
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC0
	mov	r4, r0
.L15:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L15
.L14:
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	display, .-display
	.section	.rodata.str1.4
	.align	2
.LC1:
	.ascii	"Initial array: \000"
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
	mov	r3, #1
	mov	r6, #6
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	mov	r2, #5
	mov	ip, #4
	mov	r4, #0
	mov	r5, r0
	mov	r0, r3
	str	r2, [r5, #4]
	mov	r2, #3
	str	r3, [r5, #20]
	mov	r3, #2
	str	r6, [r5]
	str	ip, [r5, #8]
	str	r2, [r5, #12]
	str	r3, [r5, #16]
	bl	__printf_chk
	mov	r1, r6
	mov	r0, r5
	bl	display
.L22:
	lsl	r3, r4, #2
	ldr	r1, [r5, r4, lsl #2]
	sub	r3, r3, #4
	sub	r0, r4, #1
	ldr	r2, [r5, r3]
	cmp	r1, r2
	blt	.L19
	add	r4, r4, #1
	cmp	r4, #6
	bne	.L22
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	mov	r1, r4
	mov	r0, r5
	bl	display
	mov	r0, r5
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, pc}
.L19:
	cmp	r0, #0
	str	r1, [r5, r3]
	str	r2, [r5, r4, lsl #2]
	movne	r4, r0
	moveq	r4, #1
	b	.L22
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
