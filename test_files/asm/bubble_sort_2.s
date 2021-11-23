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
	.file	"bubble_sort_2.c"
	.text
	.align	2
	.global	bubble_sort
	.syntax unified
	.arm
	.fpu softvfp
	.type	bubble_sort, %function
bubble_sort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	add	ip, r0, #76
	str	lr, [sp, #-4]!
.L2:
	mov	r3, r0
	mov	lr, #1
.L4:
	ldr	r2, [r3]
	ldr	r1, [r3, #4]!
	cmp	r2, r1
	stmdagt	r3, {r1, r2}
	movgt	lr, #0
	cmp	r3, ip
	bne	.L4
	cmp	lr, #0
	beq	.L2
	ldr	pc, [sp], #4
	.size	bubble_sort, .-bubble_sort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"../test_files/c_in/bubble_sort_2.c\000"
	.align	2
.LC1:
	.ascii	"array_sort[i] <= array_sort[i+1]\000"
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
	push	{r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #80
	mov	r2, #80
	mov	r1, #0
	mov	r0, sp
	movw	r7, #61643
	bl	memset
	movt	r7, 10381
	sub	r6, sp, #4
	add	r5, sp, #76
	mov	r4, sp
	mov	r8, #101
.L12:
	bl	rand
	smull	r3, r2, r7, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #4
	mls	r0, r8, r3, r0
	str	r0, [r6, #4]!
	cmp	r6, r5
	bne	.L12
.L13:
	mov	r3, sp
	mov	r2, #1
.L15:
	ldr	r1, [r3]
	ldr	r0, [r3, #4]!
	cmp	r1, r0
	strdgt	r0, [r3, #-4]
	movgt	r2, #0
	cmp	r3, r5
	bne	.L15
	cmp	r2, #0
	beq	.L13
	ldr	r3, [sp]
.L17:
	mov	r2, r3
	ldr	r3, [r4, #4]!
	cmp	r2, r3
	bgt	.L25
	cmp	r4, r5
	bne	.L17
	mov	r0, #0
	add	sp, sp, #80
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L25:
	movw	r3, #:lower16:.LANCHOR0
	movw	r1, #:lower16:.LC0
	movw	r0, #:lower16:.LC1
	movt	r3, #:upper16:.LANCHOR0
	movt	r1, #:upper16:.LC0
	movt	r0, #:upper16:.LC1
	mov	r2, #75
	bl	__assert_fail
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
	.type	__PRETTY_FUNCTION__.4927, %object
	.size	__PRETTY_FUNCTION__.4927, 5
__PRETTY_FUNCTION__.4927:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
