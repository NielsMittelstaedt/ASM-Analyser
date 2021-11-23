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
	.file	"stooge_sort.c"
	.text
	.align	2
	.global	stoogesort
	.syntax unified
	.arm
	.fpu softvfp
	.type	stoogesort, %function
stoogesort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	movw	r9, #21846
	add	r7, r0, r1, lsl #2
	add	r8, r1, #1
	movt	r9, 21845
	mov	r6, r1
	mov	r5, r0
	mov	r4, r2
.L4:
	sub	r3, r4, r6
	ldr	r2, [r7]
	add	r3, r3, #1
	ldr	ip, [r5, r4, lsl #2]
	mov	r1, r6
	mov	r0, r5
	smull	lr, r10, r9, r3
	cmp	r2, ip
	strgt	ip, [r7]
	sub	r10, r10, r3, asr #31
	strgt	r2, [r5, r4, lsl #2]
	sub	fp, r4, r10
	cmp	r4, r8
	mov	r2, fp
	pople	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	bl	stoogesort
	mov	r2, r4
	add	r1, r6, r10
	mov	r0, r5
	mov	r4, fp
	bl	stoogesort
	b	.L4
	.size	stoogesort, .-stoogesort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Sorted array : \000"
	.align	2
.LC1:
	.ascii	"%d \000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #400
	mov	r2, #5
	mov	r1, #0
	mov	r0, sp
	mov	r4, #6
	mov	r5, #5
	strd	r4, [sp]
	mov	r4, #4
	mov	r5, #3
	strd	r4, [sp, #8]
	mov	r4, #2
	mov	r5, #1
	strd	r4, [sp, #16]
	bl	stoogesort
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	movw	r5, #:lower16:.LC1
	bl	puts
	movt	r5, #:upper16:.LC1
	add	r6, sp, #24
	mov	r4, sp
.L9:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L9
	mov	r0, #10
	bl	putchar
	mov	r0, #0
	add	sp, sp, #400
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
