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
	.file	"pancake_sort.c"
	.text
	.align	2
	.global	flip
	.syntax unified
	.arm
	.fpu softvfp
	.type	flip, %function
flip:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #0
	bxle	lr
	sub	r2, r0, #4
	add	r0, r0, r1, lsl #2
	mov	r3, #0
	push	{r4, lr}
.L3:
	add	r3, r3, #1
	ldr	ip, [r2, #4]!
	sub	r4, r1, r3
	ldr	lr, [r0]
	cmp	r3, r4
	str	lr, [r2]
	str	ip, [r0], #-4
	blt	.L3
	pop	{r4, pc}
	.size	flip, .-flip
	.align	2
	.global	findMax
	.syntax unified
	.arm
	.fpu softvfp
	.type	findMax, %function
findMax:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #0
	ble	.L14
	str	lr, [sp, #-4]!
	mov	lr, r0
	ldr	r2, [lr], #-4
	mov	r3, #0
	mov	r0, r3
.L13:
	ldr	ip, [lr, #4]!
	cmp	r2, ip
	movlt	r0, r3
	add	r3, r3, #1
	movlt	r2, ip
	cmp	r3, r1
	bne	.L13
	ldr	pc, [sp], #4
.L14:
	mov	r0, #0
	bx	lr
	.size	findMax, .-findMax
	.align	2
	.global	pancakeSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	pancakeSort, %function
pancakeSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	push	{r4, r5, r6, r7, r8, r9, lr}
	sub	r7, r0, #4
.L22:
	ldr	ip, [r0]
	mov	r2, #0
	mov	r3, r2
	mov	r6, r7
	mov	r5, r7
.L24:
	ldr	lr, [r5, #4]!
	cmp	lr, ip
	movgt	r4, r3
	add	r3, r3, #1
	movle	r4, r2
	movgt	ip, lr
	cmp	r3, r1
	mov	r2, r4
	blt	.L24
	sub	lr, r1, #1
	cmp	lr, r4
	moveq	r1, r4
	bne	.L41
	cmp	r1, #1
	bgt	.L22
	pop	{r4, r5, r6, r7, r8, r9, pc}
.L41:
	cmp	r4, #0
	addgt	r2, r0, r4, lsl #2
	movgt	ip, r7
	movgt	r3, #0
	ble	.L29
.L28:
	add	r3, r3, #1
	ldr	r5, [ip, #4]!
	ldr	r8, [r2]
	sub	r9, r4, r3
	cmp	r3, r9
	str	r8, [ip]
	str	r5, [r2], #-4
	blt	.L28
.L29:
	add	ip, r0, r1, lsl #2
	mov	r3, #0
.L27:
	add	r3, r3, #1
	ldr	r4, [r6, #4]!
	ldr	r5, [ip, #-4]!
	mvn	r2, r3
	add	r2, r2, r1
	cmp	r3, r2
	str	r5, [r6]
	str	r4, [ip]
	blt	.L27
	mov	r1, lr
	cmp	r1, #1
	bgt	.L22
	pop	{r4, r5, r6, r7, r8, r9, pc}
	.size	pancakeSort, .-pancakeSort
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
	ble	.L43
	movw	r6, #:lower16:.LC0
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC0
	mov	r4, r0
.L44:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L44
.L43:
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	display, .-display
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
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	sub	sp, sp, #204
	movw	r4, #34079
	sub	r7, sp, #4
	movt	r4, 20971
	add	r6, sp, #196
	mov	r5, #100
.L48:
	bl	rand
	smull	r3, r2, r4, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r5, r3, r0
	str	r0, [r7, #4]!
	cmp	r7, r6
	bne	.L48
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	bl	__printf_chk
	mov	r0, sp
	mov	r1, #50
	bl	display
	mov	r0, sp
	mov	r1, #50
	bl	pancakeSort
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	mov	r0, sp
	mov	r1, #50
	bl	display
	mov	r0, #0
	add	sp, sp, #204
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
