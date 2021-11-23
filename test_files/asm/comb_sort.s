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
	.file	"comb_sort.c"
	.text
	.global	__aeabi_i2d
	.global	__aeabi_ddiv
	.global	__aeabi_d2iz
	.align	2
	.global	sort
	.syntax unified
	.arm
	.fpu softvfp
	.type	sort, %function
sort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	movw	r6, #52429
	movw	r7, #52428
	movt	r6, 52428
	movt	r7, 16372
	add	r4, r0, r1, lsl #2
	sub	r9, r0, #4
	mov	r8, r0
	mov	r5, r1
	mov	r0, r1
.L6:
	bl	__aeabi_i2d
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_ddiv
	bl	__aeabi_d2iz
	cmp	r5, r0
	ble	.L6
	add	r3, r8, r0, lsl #2
	mov	r2, r9
.L5:
	ldr	ip, [r3], #4
	ldr	r1, [r2, #4]!
	cmp	r1, ip
	strgt	ip, [r2]
	strgt	r1, [r3, #-4]
	cmp	r4, r3
	bne	.L5
	cmp	r0, #1
	bgt	.L6
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
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
	.ascii	"Insert %d unsorted numbers: \012\000"
	.align	2
.LC2:
	.ascii	"Initial array: \000"
	.align	2
.LC3:
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
	mov	r2, #6
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	mov	r5, #6
	mov	r4, r0
	mov	r0, r6
	bl	__printf_chk
	mov	r2, #3
	mov	r0, r6
	mov	r3, #5
	str	r5, [r4]
	movw	r1, #:lower16:.LC2
	str	r3, [r4, #4]
	movt	r1, #:upper16:.LC2
	mov	r3, #4
	str	r6, [r4, #20]
	str	r3, [r4, #8]
	mov	r3, #2
	strd	r2, [r4, #12]
	bl	__printf_chk
	mov	r1, r5
	mov	r0, r4
	bl	display
	mov	r1, r5
	mov	r0, r4
	bl	sort
	mov	r0, r6
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
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
