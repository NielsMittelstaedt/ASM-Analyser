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
	.file	"radix_sort_2.c"
	.text
	.align	2
	.global	MAX
	.syntax unified
	.arm
	.fpu softvfp
	.type	MAX, %function
MAX:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #0
	mov	r3, r0
	ldr	r0, [r0]
	bxle	lr
	add	r1, r3, r1, lsl #2
.L3:
	ldr	r2, [r3], #4
	cmp	r0, r2
	movlt	r0, r2
	cmp	r1, r3
	bne	.L3
	bx	lr
	.size	MAX, .-MAX
	.global	__aeabi_idiv
	.align	2
	.global	countSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	countSort, %function
countSort:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #52
	lsl	r10, r1, #2
	mov	r6, r1
	str	r1, [sp, #4]
	mov	r5, r0
	mov	r1, #0
	add	r0, sp, #8
	mov	r4, r2
	mov	r2, #40
	bl	memset
	mov	r0, r10
	bl	malloc
	cmp	r6, #0
	mov	r6, r0
	ble	.L7
	movw	r7, #26215
	add	fp, r10, r5
	movt	r7, 26214
	mov	r9, r5
	mov	r8, #10
.L8:
	ldr	r0, [r9], #4
	mov	r1, r4
	bl	__aeabi_idiv
	add	r2, sp, #48
	cmp	fp, r9
	smull	r3, r1, r7, r0
	asr	r3, r0, #31
	rsb	r3, r3, r1, asr #2
	mls	r3, r8, r3, r0
	add	r3, r2, r3, lsl #2
	ldr	r1, [r3, #-40]
	add	r1, r1, #1
	str	r1, [r3, #-40]
	bne	.L8
.L7:
	ldr	r3, [sp, #4]
	ldr	r0, [sp, #8]
	cmp	r3, #0
	ldr	r3, [sp, #12]
	ldr	r1, [sp, #16]
	add	r0, r0, r3
	ldr	r2, [sp, #20]
	add	r1, r0, r1
	ldr	r3, [sp, #24]
	add	r2, r1, r2
	str	r0, [sp, #12]
	ldr	r0, [sp, #28]
	add	r3, r2, r3
	str	r1, [sp, #16]
	ldr	r1, [sp, #32]
	add	r0, r3, r0
	str	r2, [sp, #20]
	ldr	r2, [sp, #36]
	add	r1, r0, r1
	str	r3, [sp, #24]
	ldr	r3, [sp, #40]
	add	r2, r1, r2
	str	r1, [sp, #32]
	ldr	r1, [sp, #44]
	add	r3, r2, r3
	str	r0, [sp, #28]
	strd	r2, [sp, #36]
	add	r3, r1, r3
	str	r3, [sp, #44]
	ble	.L11
	movw	r7, #26215
	add	fp, r5, r10
	movt	r7, 26214
	mov	r8, #10
.L10:
	ldr	r9, [fp, #-4]!
	mov	r1, r4
	mov	r0, r9
	bl	__aeabi_idiv
	add	r2, sp, #48
	cmp	r5, fp
	smull	r3, r1, r7, r0
	asr	r3, r0, #31
	rsb	r3, r3, r1, asr #2
	mls	r3, r8, r3, r0
	add	r3, r2, r3, lsl #2
	ldr	r1, [r3, #-40]
	sub	r0, r1, #-1073741823
	sub	r1, r1, #1
	str	r1, [r3, #-40]
	str	r9, [r6, r0, lsl #2]
	bne	.L10
	ldr	r3, [sp, #4]
	cmp	r3, #0
	ble	.L11
	mov	r2, r10
	mov	r0, r5
	mov	r1, r6
	bl	memcpy
.L11:
	mov	r0, r6
	add	sp, sp, #52
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	free
	.size	countSort, .-countSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"%d, \000"
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
	ble	.L16
	movw	r6, #:lower16:.LC1
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC1
	mov	r4, r0
.L17:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L17
.L16:
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	display, .-display
	.align	2
	.global	radixsort2
	.syntax unified
	.arm
	.fpu softvfp
	.type	radixsort2, %function
radixsort2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	subs	r4, r2, #0
	popeq	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	movw	r8, #:lower16:.LC1
	movw	r10, #26215
	movt	r8, #:upper16:.LC1
	movt	r10, 26214
	add	r9, r0, r1, lsl #2
	mov	r7, r0
	mov	r6, r1
	mov	r5, #1
.L22:
	cmp	r6, #0
	movgt	fp, r7
	ble	.L24
.L23:
	ldr	r2, [fp], #4
	mov	r1, r8
	mov	r0, #1
	bl	__printf_chk
	cmp	r9, fp
	bne	.L23
.L24:
	mov	r0, #10
	bl	putchar
	mov	r2, r5
	mov	r1, r6
	mov	r0, r7
	bl	countSort
	smull	r2, r3, r10, r4
	asr	r4, r4, #31
	mov	r2, #10
	mul	r5, r2, r5
	rsbs	r4, r4, r3, asr #2
	bne	.L22
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	radixsort2, .-radixsort2
	.section	.rodata.str1.4
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
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	str	lr, [sp, #-4]!
	sub	sp, sp, #28
	ldmia	ip!, {r0, r1, r2, r3}
	mov	lr, sp
	stmia	lr!, {r0, r1, r2, r3}
	mov	r2, #6
	ldm	ip, {r0, r1}
	stm	lr, {r0, r1}
	mov	r1, r2
	mov	r0, sp
	bl	radixsort2
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	mov	r0, sp
	mov	r1, #6
	bl	display
	mov	r0, #0
	add	sp, sp, #28
	@ sp needed
	ldr	pc, [sp], #4
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	6
	.word	5
	.word	4
	.word	3
	.word	2
	.word	1
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
