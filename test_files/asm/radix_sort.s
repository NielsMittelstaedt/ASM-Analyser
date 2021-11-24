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
	.file	"radix_sort.c"
	.text
	.align	2
	.global	largest
	.syntax unified
	.arm
	.fpu softvfp
	.type	largest, %function
largest:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #1
	mov	r3, r0
	ldr	r0, [r0]
	bxle	lr
	add	r1, r3, r1, lsl #2
	add	r3, r3, #4
.L3:
	ldr	r2, [r3], #4
	cmp	r0, r2
	movlt	r0, r2
	cmp	r1, r3
	bne	.L3
	bx	lr
	.size	largest, .-largest
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"The large element %d\012\000"
	.global	__aeabi_idiv
	.align	2
.LC1:
	.ascii	"%d  \000"
	.text
	.align	2
	.global	RadixSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	RadixSort, %function
RadixSort:
	@ args = 0, pretend = 0, frame = 456
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	cmp	r1, #1
	sub	sp, sp, #460
	ldr	r4, [r0]
	mov	r9, r0
	str	r1, [sp]
	ble	.L7
	add	r3, r0, #4
	add	r1, r0, r1, lsl #2
.L8:
	ldr	r2, [r3], #4
	cmp	r4, r2
	movlt	r4, r2
	cmp	r3, r1
	bne	.L8
.L7:
	movw	r1, #:lower16:.LC0
	mov	r2, r4
	movt	r1, #:upper16:.LC0
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, #0
	ble	.L6
	movw	r1, #52429
	movt	r1, 52428
	mov	r3, #0
.L10:
	umull	r0, r2, r1, r4
	cmp	r4, #9
	add	r3, r3, #1
	lsr	r4, r2, #3
	bgt	.L10
	ldr	r2, [sp]
	mov	fp, #1
	mov	r7, #10
	str	r3, [sp, #8]
	movw	r3, #26215
	movt	r3, 26214
	add	r8, r9, r2, lsl #2
	str	r3, [sp, #12]
	mov	r3, #0
	str	r3, [sp, #4]
.L11:
	ldr	r3, [sp]
	mov	r2, #0
	cmp	r3, #0
	mov	r3, #0
	strd	r2, [sp, #16]
	ldrgt	r5, [sp, #12]
	movgt	r4, r9
	strd	r2, [sp, #24]
	strd	r2, [sp, #32]
	strd	r2, [sp, #40]
	strd	r2, [sp, #48]
	ble	.L19
.L12:
	ldr	r6, [r4], #4
	mov	r1, fp
	mov	r0, r6
	bl	__aeabi_idiv
	cmp	r8, r4
	smull	r3, r2, r5, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #2
	add	r2, sp, #456
	mls	r3, r7, r3, r0
	add	r1, r2, r3, lsl #2
	ldr	r2, [r1, #-440]
	add	r0, r2, #1
	str	r0, [r1, #-440]
	mla	r3, r7, r3, r2
	add	r2, sp, #456
	add	r3, r2, r3, lsl #2
	str	r6, [r3, #-400]
	bne	.L12
.L19:
	add	r10, sp, #16
	add	r4, sp, #56
	mov	r6, #0
.L13:
	ldr	r5, [r10], #4
	add	r0, r9, r6, lsl #2
	mov	r1, r4
	cmp	r5, #0
	lsl	r2, r5, #2
	ble	.L16
	bl	memcpy
	add	r6, r6, r5
.L16:
	add	r4, r4, #40
	add	r3, sp, #456
	cmp	r3, r4
	bne	.L13
	ldr	r3, [sp]
	mul	fp, r7, fp
	cmp	r3, #0
	ble	.L17
	movw	r5, #:lower16:.LC1
	movt	r5, #:upper16:.LC1
	mov	r4, r9
.L18:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r8, r4
	bne	.L18
.L17:
	ldr	r3, [sp, #4]
	mov	r0, #10
	add	r3, r3, #1
	str	r3, [sp, #4]
	mov	r4, r3
	bl	putchar
	ldr	r2, [sp, #8]
	cmp	r2, r4
	bne	.L11
.L6:
	add	sp, sp, #460
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	RadixSort, .-RadixSort
	.section	.rodata.str1.4
	.align	2
.LC2:
	.ascii	"The sorted elements are ::  \000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #40
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
	bl	RadixSort
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	movw	r5, #:lower16:.LC1
	bl	__printf_chk
	movt	r5, #:upper16:.LC1
	add	r6, sp, #24
	mov	r4, sp
.L27:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L27
	mov	r0, #10
	bl	putchar
	mov	r0, #0
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
