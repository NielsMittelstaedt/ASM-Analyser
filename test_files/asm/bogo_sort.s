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
	.file	"bogo_sort.c"
	.text
	.align	2
	.global	check_sorted
	.syntax unified
	.arm
	.fpu softvfp
	.type	check_sorted, %function
check_sorted:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	r3, r1, #-1073741823
	add	r0, r0, r3, lsl #2
	b	.L2
.L4:
	ldr	r2, [r0]
	ldr	r3, [r0, #-4]!
	cmp	r2, r3
	blt	.L5
.L2:
	sub	r1, r1, #1
	cmp	r1, #0
	bgt	.L4
	mov	r0, #1
	bx	lr
.L5:
	mov	r0, #0
	bx	lr
	.size	check_sorted, .-check_sorted
	.global	__aeabi_idivmod
	.align	2
	.global	shuffle
	.syntax unified
	.arm
	.fpu softvfp
	.type	shuffle, %function
shuffle:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	subs	r7, r1, #0
	pople	{r4, r5, r6, r7, r8, pc}
	add	r8, r0, r7, lsl #2
	mov	r5, r0
	mov	r4, r0
.L9:
	ldr	r6, [r4]
	bl	rand
	mov	r1, r7
	bl	__aeabi_idivmod
	ldr	r3, [r5, r1, lsl #2]
	str	r3, [r4], #4
	cmp	r8, r4
	str	r6, [r5, r1, lsl #2]
	bne	.L9
	pop	{r4, r5, r6, r7, r8, pc}
	.size	shuffle, .-shuffle
	.align	2
	.global	sort
	.syntax unified
	.arm
	.fpu softvfp
	.type	sort, %function
sort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	sub	r7, r1, #-1073741823
	mov	r5, r1
	mov	r8, r0
	lsl	r7, r7, #2
	add	r6, r7, #4
	add	r7, r0, r7
	add	r6, r6, r0
.L13:
	mov	r2, r7
	mov	r3, r5
.L15:
	sub	r3, r3, #1
	cmp	r3, #0
	pople	{r4, r5, r6, r7, r8, r9, r10, pc}
	ldr	r0, [r2]
	ldr	r1, [r2, #-4]!
	cmp	r0, r1
	bge	.L15
	cmp	r5, #0
	movgt	r4, r8
	ble	.L13
.L14:
	ldr	r9, [r4]
	bl	rand
	mov	r1, r5
	bl	__aeabi_idivmod
	ldr	r3, [r8, r1, lsl #2]
	str	r3, [r4], #4
	cmp	r6, r4
	str	r9, [r8, r1, lsl #2]
	bne	.L14
	b	.L13
	.size	sort, .-sort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Enter 6 numbers unsorted \012\000"
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
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #24
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	puts
	mov	r0, sp
	mov	r1, #6
	mov	r2, #6
	mov	r3, #5
	strd	r2, [sp]
	mov	r2, #4
	mov	r3, #3
	strd	r2, [sp, #8]
	mov	r2, #2
	mov	r3, #1
	strd	r2, [sp, #16]
	bl	sort
	movw	r5, #:lower16:.LC1
	add	r6, sp, #24
	movt	r5, #:upper16:.LC1
	mov	r4, sp
.L24:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L24
	mov	r0, #10
	bl	putchar
	mov	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
