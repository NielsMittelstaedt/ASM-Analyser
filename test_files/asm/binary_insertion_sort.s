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
	.file	"binary_insertion_sort.c"
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
	.global	binarySearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	binarySearch, %function
binarySearch:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r2, r3
	push	{r4, r5, lr}
	mov	r5, r0
	bge	.L15
	sub	lr, r3, #1
.L9:
	add	ip, lr, lr, lsr #31
	add	ip, r2, ip, asr #1
	ldr	r4, [r5, ip, lsl #2]
	cmp	r4, r1
	beq	.L17
	ble	.L12
	sub	r3, ip, #1
	cmp	r3, r2
	sub	lr, r3, #1
	bgt	.L9
.L15:
	ldr	r3, [r5, r2, lsl #2]
	mov	r0, r2
	cmp	r3, r1
	addlt	r0, r2, #1
	pop	{r4, r5, pc}
.L12:
	add	r2, ip, #1
	cmp	r2, r3
	blt	.L9
	b	.L15
.L17:
	add	r0, ip, #1
	pop	{r4, r5, pc}
	.size	binarySearch, .-binarySearch
	.align	2
	.global	insertionSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	insertionSort, %function
insertionSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #0
	bxle	lr
	push	{r4, r5, r6, r7, r8, lr}
	mvn	r5, #0
	sub	r6, r0, #4
	cmp	r5, #0
	sub	r7, r1, #1
	mov	r8, r5
	ldr	r4, [r6, #4]!
	ble	.L31
.L42:
	sub	lr, r5, #1
	mov	ip, r5
	mov	r2, #0
.L21:
	add	r3, r2, lr, asr #1
	ldr	r1, [r0, r3, lsl #2]
	cmp	r4, r1
	beq	.L41
.L23:
	bge	.L24
	sub	ip, r3, #1
	cmp	ip, r2
	sub	lr, ip, #1
	bgt	.L21
.L25:
	add	r3, r0, r2, lsl #2
.L20:
	ldr	r3, [r3]
	cmp	r4, r3
	addgt	r2, r2, #1
.L22:
	cmp	r5, r2
	addlt	r3, r5, #1
	blt	.L27
	add	ip, r0, r2, lsl #2
	mov	r3, r6
.L28:
	ldr	r1, [r3, #-4]
	str	r1, [r3], #-4
	cmp	ip, r3
	bne	.L28
	add	r3, r5, #1
	sub	r2, r2, r3
	add	r8, r2, r5
.L27:
	add	r2, r8, #1
	cmp	r7, r3
	mov	r5, r3
	str	r4, [r0, r2, lsl #2]
	popeq	{r4, r5, r6, r7, r8, pc}
	cmp	r5, #0
	ldr	r4, [r6, #4]!
	mov	r8, r5
	bgt	.L42
.L31:
	mov	r3, r0
	mov	r2, #0
	b	.L20
.L24:
	add	r2, r3, #1
	cmp	r2, ip
	bge	.L25
	add	r3, r2, lr, asr #1
	ldr	r1, [r0, r3, lsl #2]
	cmp	r4, r1
	bne	.L23
.L41:
	add	r2, r3, #1
	b	.L22
	.size	insertionSort, .-insertionSort
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
	bl	insertionSort
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
