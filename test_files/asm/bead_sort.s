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
	.file	"bead_sort.c"
	.text
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
	.size	display, .-display
	.align	2
	.global	bead_sort
	.syntax unified
	.arm
	.fpu softvfp
	.type	bead_sort, %function
bead_sort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r7, r1
	ldr	r4, [r0]
	mov	r5, r0
	bls	.L8
	add	r3, r0, #4
	add	r1, r0, r1, lsl #2
.L9:
	ldr	r2, [r3], #4
	cmp	r4, r2
	movlt	r4, r2
	cmp	r1, r3
	bne	.L9
	mul	r1, r7, r4
	mov	r0, #1
	bl	calloc
	mov	r6, r0
.L11:
	sub	r10, r5, #4
	mov	r9, r6
	mov	r8, #0
.L13:
	ldr	r2, [r10, #4]!
	mov	r0, r9
	mov	r1, #1
	cmp	r2, #0
	ble	.L15
	bl	memset
.L15:
	add	r8, r8, #1
	add	r9, r9, r4
	cmp	r7, r8
	bhi	.L13
.L12:
	cmp	r4, #0
	movgt	r8, #0
	movgt	r0, #1
	movgt	r1, r8
	ble	.L17
.L16:
	cmp	r7, #0
	addne	ip, r6, r8
	movne	r3, #0
	movne	r2, r3
	beq	.L19
.L18:
	mov	lr, r2
	add	r2, r2, #1
	ldrb	r9, [ip]	@ zero_extendqisi2
	cmp	r2, r7
	strb	r1, [ip], r4
	add	r3, r3, r9
	bne	.L18
	sub	r3, r7, r3
	cmp	r3, r7
	bcs	.L19
	mla	r2, r3, r4, r8
	add	r2, r6, r2
.L20:
	cmp	lr, r3
	mov	ip, r3
	strb	r0, [r2], r4
	add	r3, r3, #1
	bne	.L20
.L19:
	add	r8, r8, #1
	cmp	r4, r8
	bne	.L16
.L17:
	cmp	r7, #0
	beq	.L22
	sub	r0, r6, #1
	add	r7, r5, r7, lsl #2
.L23:
	cmp	r4, #0
	movle	r3, #0
	ble	.L24
	mov	r2, r0
	mov	r3, #0
	b	.L26
.L25:
	add	r3, r3, #1
	cmp	r4, r3
	beq	.L40
.L26:
	ldrb	r1, [r2, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L25
.L24:
	str	r3, [r5], #4
	cmp	r5, r7
	add	r0, r0, r4
	bne	.L23
.L22:
	mov	r0, r6
	pop	{r4, r5, r6, r7, r8, r9, r10, lr}
	b	free
.L40:
	mov	r3, r4
	str	r3, [r5], #4
	cmp	r5, r7
	add	r0, r0, r4
	bne	.L23
	b	.L22
.L8:
	mul	r1, r1, r4
	mov	r0, #1
	bl	calloc
	cmp	r7, #0
	mov	r6, r0
	beq	.L12
	b	.L11
	.size	bead_sort, .-bead_sort
	.section	.rodata.str1.4
	.align	2
.LC1:
	.ascii	"Enter size of array:\000"
	.align	2
.LC2:
	.ascii	"Enter the elements of the array\000"
	.align	2
.LC3:
	.ascii	"Original array: \000"
	.align	2
.LC4:
	.ascii	"Sorted array: \000"
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
	push	{r4, r5, r6, lr}
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	mov	r6, #1
	bl	puts
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	mov	r5, #6
	bl	puts
	mov	r0, #24
	bl	malloc
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	mov	r2, #3
	mov	r3, #5
	mov	r4, r0
	mov	r0, r6
	str	r3, [r4, #4]
	mov	r3, #4
	str	r5, [r4]
	str	r3, [r4, #8]
	mov	r3, #2
	str	r6, [r4, #20]
	strd	r2, [r4, #12]
	bl	__printf_chk
	mov	r1, r5
	mov	r0, r4
	bl	display
	mov	r1, r5
	mov	r0, r4
	bl	bead_sort
	mov	r0, r6
	movw	r1, #:lower16:.LC4
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
	mov	r1, r5
	mov	r0, r4
	bl	display
	mov	r0, r4
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
