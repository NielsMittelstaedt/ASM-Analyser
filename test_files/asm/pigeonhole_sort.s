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
	.file	"pigeonhole_sort.c"
	.text
	.align	2
	.global	pigeonholeSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	pigeonholeSort, %function
pigeonholeSort:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r6, r1
	ldr	r4, [r0]
	sub	sp, sp, #12
	mov	r5, r0
	ble	.L2
	add	r1, r0, #4
	add	r0, r0, r6, lsl #2
	mov	r2, r4
.L3:
	ldr	r3, [r1], #4
	cmp	r4, r3
	movge	r4, r3
	cmp	r2, r3
	movlt	r2, r3
	cmp	r1, r0
	bne	.L3
	sub	r2, r2, r4
	add	r7, r2, #1
	lsl	r8, r7, #2
	mov	r9, r7
	mov	r0, r8
	bl	malloc
	cmp	r7, #0
	mov	r7, r0
	ble	.L15
	mov	r2, r8
	mov	r1, #0
	bl	memset
.L15:
	sub	r0, r5, #4
	mov	r1, #0
.L5:
	ldr	r3, [r0, #4]!
	add	r1, r1, #1
	cmp	r6, r1
	sub	r3, r3, r4
	ldr	r2, [r7, r3, lsl #2]
	add	r2, r2, #1
	str	r2, [r7, r3, lsl #2]
	bgt	.L5
	cmp	r9, #0
	ble	.L7
.L6:
	mov	r3, #0
	sub	r8, r7, #4
	mov	r0, r3
	mov	fp, r9
	str	r7, [sp, #4]
.L12:
	ldr	ip, [r8, #4]!
	cmp	ip, #0
	ble	.L14
	sub	r6, ip, #1
	lsl	r7, r3, #2
	cmp	r6, #5
	add	r2, r5, r7
	add	r9, r3, #1
	ubfx	r2, r2, #2, #1
	add	r1, r4, r0
	mov	r10, r6
	mov	lr, ip
	ble	.L8
	cmp	r2, #0
	sub	lr, lr, r2
	add	r2, r3, r2
	strne	r1, [r5, r7]
	moveq	r7, r3
	lsr	r3, lr, #1
	add	r2, r5, r2, lsl #2
	movne	ip, r6
	add	r3, r2, r3, lsl #3
	movne	r7, r9
.L10:
	str	r1, [r2]
	add	r2, r2, #8
	str	r1, [r2, #-4]
	cmp	r2, r3
	bne	.L10
	bic	r3, lr, #1
	cmp	r3, lr
	sub	ip, ip, r3
	add	r3, r3, r7
	beq	.L11
	sub	r10, ip, #1
.L8:
	cmp	r10, #0
	str	r1, [r5, r3, lsl #2]
	lsl	r3, r3, #2
	beq	.L11
	add	r3, r5, r3
	cmp	ip, #2
	str	r1, [r3, #4]
	beq	.L11
	cmp	ip, #3
	str	r1, [r3, #8]
	beq	.L11
	cmp	ip, #4
	str	r1, [r3, #12]
	beq	.L11
	cmp	ip, #5
	str	r1, [r3, #16]
	strne	r1, [r3, #20]
.L11:
	add	r3, r6, r9
	mov	r2, #0
	str	r2, [r8]
.L14:
	add	r0, r0, #1
	cmp	r0, fp
	blt	.L12
	ldr	r7, [sp, #4]
.L7:
	mov	r0, r7
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	free
.L2:
	mov	r0, #4
	bl	malloc
	cmp	r6, #1
	mov	r3, #0
	mov	r7, r0
	str	r3, [r0]
	movne	r3, #1
	movne	r9, r3
	bne	.L6
.L18:
	mov	r9, r6
	b	.L15
	.size	pigeonholeSort, .-pigeonholeSort
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
.L41:
	ldr	r2, [r5, #4]!
	mov	r1, r8
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r6
	bne	.L41
	mov	r1, #6
	mov	r0, r7
	bl	pigeonholeSort
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	movw	r5, #:lower16:.LC1
	movt	r5, #:upper16:.LC1
.L42:
	ldr	r2, [r4, #4]!
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L42
	mov	r0, #10
	bl	putchar
	mov	r0, r7
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
