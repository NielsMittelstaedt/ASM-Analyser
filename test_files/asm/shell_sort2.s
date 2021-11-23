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
	.file	"shell_sort2.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"%3d \000"
	.text
	.align	2
	.global	show_data
	.syntax unified
	.arm
	.fpu softvfp
	.type	show_data, %function
show_data:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r5, r1, #0
	ble	.L2
	movw	r6, #:lower16:.LC1
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC1
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
	.size	show_data, .-show_data
	.align	2
	.global	shell_sort
	.syntax unified
	.arm
	.fpu softvfp
	.type	shell_sort, %function
shell_sort:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r4, r0
	mov	r7, r1
	sub	sp, sp, #44
	ldmia	ip!, {r0, r1, r2, r3}
	add	lr, sp, #8
	sub	r5, r4, #4
	add	r6, sp, #4
	add	r5, r5, r7, lsl #2
	str	r4, [sp, #4]
	stmia	lr!, {r0, r1, r2, r3}
	ldm	ip, {r0, r1, r2, r3}
	stm	lr, {r0, r1, r2, r3}
.L9:
	ldr	r4, [r6, #4]!
	cmp	r4, r7
	bge	.L15
	ldr	r3, [sp, #4]
	sub	r10, r4, #-1073741823
	lsl	lr, r4, #2
	mov	fp, r4
	rsb	lr, lr, #0
	add	r10, r3, r10, lsl #2
.L14:
	ldr	r9, [r10, #4]!
	mov	r2, fp
	mov	ip, r10
.L11:
	ldr	r1, [ip, lr]
	add	r0, ip, lr
	mov	r3, ip
	sub	r2, r2, r4
	sub	r8, r1, r9
	mov	ip, r0
	cmp	r8, #0
	ble	.L21
	cmp	r2, r4
	str	r1, [r3]
	bge	.L11
	cmp	r5, r10
	add	fp, fp, #1
	str	r9, [r0]
	bne	.L14
.L15:
	add	r3, sp, #36
	cmp	r6, r3
	bne	.L9
	add	sp, sp, #44
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L21:
	cmp	r5, r10
	mov	r0, r3
	add	fp, fp, #1
	str	r9, [r0]
	bne	.L14
	b	.L15
	.size	shell_sort, .-shell_sort
	.section	.rodata.str1.4
	.align	2
.LC2:
	.ascii	"Data Sorted\000"
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
	mov	r0, #40
	bl	malloc
	movw	r4, #19923
	movt	r4, 4194
	mov	r5, #500
	mov	r7, r0
	mov	r0, #0
	bl	time
	sub	r8, r7, #4
	bl	srand
	add	r6, r7, #36
.L23:
	bl	rand
	smull	r3, r2, r4, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r3, r5, r3, r0
	add	r3, r3, #1
	str	r3, [r8, #4]!
	cmp	r8, r6
	bne	.L23
	mov	r0, r7
	mov	r1, #10
	bl	show_data
	mov	r1, #10
	mov	r0, r7
	bl	shell_sort
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	puts
	mov	r1, #10
	mov	r0, r7
	bl	show_data
	mov	r0, r7
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	701
	.word	301
	.word	132
	.word	57
	.word	23
	.word	10
	.word	4
	.word	1
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
