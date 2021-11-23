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
	.file	"merge_sort_nr.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
	.align	2
.LC1:
	.ascii	"\012\000"
	.text
	.align	2
	.global	mergesort
	.syntax unified
	.arm
	.fpu softvfp
	.type	mergesort, %function
mergesort:
	@ args = 0, pretend = 0, frame = 216
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #220
	mov	r10, r1
	mov	r8, r0
	mov	fp, #1
	add	r2, r0, r1, lsl #2
	movw	r3, #:lower16:.LC0
	str	r2, [sp, #8]
	movt	r3, #:upper16:.LC0
	str	r3, [sp, #12]
	sub	r3, r1, #1
	str	r3, [sp, #4]
.L18:
	mov	r4, #0
	mov	r3, fp
	mov	r5, r4
.L13:
	sub	ip, r3, #1
	add	r7, ip, fp
	cmp	r7, r10
	addlt	r9, r7, #1
	ldrge	r7, [sp, #4]
	movge	r9, r10
	cmp	r7, r3
	cmpge	ip, r4
	blt	.L16
	add	r2, sp, #16
	ldr	r0, [r8, r4, lsl #2]
	ldr	r1, [r8, r3, lsl #2]
	add	r2, r2, r5, lsl #2
	mov	r6, r3
.L7:
	cmp	r0, r1
	add	r5, r5, #1
	bge	.L8
.L30:
	cmp	r7, r6
	add	r4, r4, #1
	str	r0, [r2], #4
	movlt	r0, #0
	movge	r0, #1
	cmp	r4, ip
	movgt	r0, #0
	cmp	r0, #0
	beq	.L6
	ldr	r0, [r8, r4, lsl #2]
	add	r5, r5, #1
	cmp	r0, r1
	blt	.L30
.L8:
	add	r6, r6, #1
	str	r1, [r2], #4
	cmp	r6, r7
	movgt	r1, #0
	movle	r1, #1
	cmp	ip, r4
	movlt	r1, #0
	cmp	r1, #0
	beq	.L6
	ldr	r1, [r8, r6, lsl #2]
	b	.L7
.L16:
	mov	r6, r3
.L6:
	cmp	ip, r4
	blt	.L11
	sub	r2, r3, r4
	str	r3, [sp]
	add	r3, sp, #16
	add	r1, r8, r4, lsl #2
	add	r0, r3, r5, lsl #2
	lsl	r2, r2, #2
	bl	memcpy
	ldr	r3, [sp]
	add	r5, r5, r3
	sub	r5, r5, r4
.L11:
	cmp	r7, r6
	blt	.L12
	add	r2, r7, #1
	add	r3, sp, #16
	sub	r2, r2, r6
	add	r0, r3, r5, lsl #2
	add	r1, r8, r6, lsl #2
	add	r5, r5, r2
	lsl	r2, r2, #2
	bl	memcpy
.L12:
	add	r3, fp, r9
	cmp	r3, r10
	movlt	r4, r9
	blt	.L13
.L31:
	add	r2, r7, #1
	add	r1, sp, #16
	mov	r0, r8
	lsl	fp, fp, #1
	lsl	r2, r2, #2
	mov	r4, r8
	bl	memcpy
	ldr	r5, [sp, #8]
	ldr	r6, [sp, #12]
.L15:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L15
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	puts
	cmp	r10, fp
	bgt	.L18
	add	sp, sp, #220
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	mergesort, .-mergesort
	.align	2
	.global	show
	.syntax unified
	.arm
	.fpu softvfp
	.type	show, %function
show:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r5, r1, #0
	ble	.L33
	movw	r6, #:lower16:.LC0
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC0
	mov	r4, r0
.L34:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L34
.L33:
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	pop	{r4, r5, r6, lr}
	b	puts
	.size	show, .-show
	.section	.rodata.str1.4
	.align	2
.LC2:
	.ascii	"Sorted array is as shown:\000"
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
	push	{r4, r5, r6, lr}
	sub	sp, sp, #80
	mov	r1, #6
	mov	r2, #6
	mov	r0, sp
	mov	r3, #5
	strd	r2, [sp]
	mov	r2, #4
	mov	r3, #3
	strd	r2, [sp, #8]
	mov	r2, #2
	mov	r3, #1
	strd	r2, [sp, #16]
	bl	mergesort
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	puts
	movw	r5, #:lower16:.LC0
	add	r6, sp, #24
	movt	r5, #:upper16:.LC0
	mov	r4, sp
.L38:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L38
	mov	r0, #0
	add	sp, sp, #80
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
