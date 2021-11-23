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
	.file	"shell_sort.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
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
	movw	r6, #:lower16:.LC0
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC0
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
	.global	swap
	.syntax unified
	.arm
	.fpu softvfp
	.type	swap, %function
swap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, [r0]
	ldr	r2, [r1]
	str	r2, [r0]
	str	r3, [r1]
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	shellSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	shellSort, %function
shellSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, r7, r8, lr}
	add	lr, r1, r1, lsr #31
	pople	{r4, r5, r6, r7, r8, pc}
	asr	lr, lr, #1
	mov	r7, r1
	mov	r8, r0
.L9:
	cmp	r7, lr
	ble	.L13
	lsl	ip, lr, #2
	sub	r6, r7, lr
	add	r5, r8, ip
	rsb	ip, ip, #0
	mov	r4, #0
.L12:
	mov	r2, r4
	mov	r3, r5
	b	.L11
.L15:
	subs	r2, r2, lr
	str	r1, [r3, ip]
	str	r0, [r3], ip
	bmi	.L14
.L11:
	ldr	r0, [r3, ip]
	ldr	r1, [r3]
	cmp	r0, r1
	bgt	.L15
.L14:
	add	r4, r4, #1
	add	r5, r5, #4
	cmp	r4, r6
	bne	.L12
.L13:
	asrs	lr, lr, #1
	bne	.L9
	pop	{r4, r5, r6, r7, r8, pc}
	.size	shellSort, .-shellSort
	.section	.rodata.str1.4
	.align	2
.LC1:
	.ascii	"Data Sorted\000"
	.global	__aeabi_i2d
	.global	__aeabi_ddiv
	.global	__aeabi_dmul
	.align	2
.LC2:
	.ascii	"Time spent sorting: %.4g ms\012\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 80000
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #79872
	sub	sp, sp, #128
	mov	r0, #0
	bl	time
	movw	r5, #19923
	bl	srand
	add	r3, sp, #128
	add	r4, r3, #78848
	movt	r5, 4194
	sub	r7, r3, #128
	add	r4, r4, #1020
	sub	r8, r3, #132
	mov	r6, #500
.L26:
	bl	rand
	smull	r3, r2, r5, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r6, r3, r0
	add	r0, r0, #1
	str	r0, [r8, #4]!
	cmp	r8, r4
	bne	.L26
	movw	r1, #20000
	mov	r0, r7
	bl	show_data
	bl	clock
	movw	r1, #20000
	mov	r4, r0
	mov	r0, r7
	bl	shellSort
	bl	clock
	mov	r5, r0
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	puts
	mov	r0, r7
	movw	r1, #20000
	bl	show_data
	movw	r3, #:lower16:.LANCHOR0
	movt	r3, #:upper16:.LANCHOR0
	ldr	r0, [r3]
	bl	puts
	sub	r0, r5, r4
	bl	__aeabi_i2d
	mov	r2, #0
	movw	r3, #33920
	movt	r3, 16686
	bl	__aeabi_ddiv
	mov	r2, #0
	mov	r3, #16384
	movt	r3, 16527
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	mov	r0, #1
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	mov	r0, #0
	add	sp, sp, #79872
	add	sp, sp, #128
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.global	notation
	.section	.rodata.str1.4
	.align	2
.LC3:
	.ascii	"Shell Sort Big O Notation:\011\011\011\011\011\011\012"
	.ascii	"--> Best Case: O(n log(n)) \011\011\011\011\011\011"
	.ascii	"\012--> Average Case: depends on gap sequence \011\011"
	.ascii	"\011\011\011\011\012--> Worst Case: O(n)\000"
	.data
	.align	2
	.set	.LANCHOR0,. + 0
	.type	notation, %object
	.size	notation, 4
notation:
	.word	.LC3
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
