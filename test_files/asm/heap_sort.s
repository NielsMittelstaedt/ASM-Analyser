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
	.file	"heap_sort.c"
	.text
	.align	2
	.global	max_heapify
	.syntax unified
	.arm
	.fpu softvfp
	.type	max_heapify, %function
max_heapify:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r2, r1, lsl #1
	push	{r4, r5, lr}
	add	r4, r0, r1, lsl #2
	ldr	r5, [r0, r1, lsl #2]
	blt	.L2
	lsl	r3, r1, #1
	b	.L4
.L9:
	cmp	r2, r3
	str	lr, [r0, r1, lsl #2]
	blt	.L8
.L4:
	cmp	r2, r3
	lsl	r1, r3, #2
	ldr	lr, [r0, r3, lsl #2]
	add	r4, r1, #4
	add	ip, r0, r1
	ble	.L3
	ldr	r1, [r0, r4]
	add	r4, r0, r4
	cmp	r1, lr
	addgt	r3, r3, #1
	movgt	lr, r1
	movgt	ip, r4
.L3:
	add	r1, r3, r3, lsr #31
	cmp	r5, lr
	lsl	r3, r3, #1
	asr	r1, r1, #1
	add	r4, r0, r1, lsl #2
	ble	.L9
.L2:
	str	r5, [r4]
	pop	{r4, r5, pc}
.L8:
	mov	r4, ip
	str	r5, [r4]
	pop	{r4, r5, pc}
	.size	max_heapify, .-max_heapify
	.align	2
	.global	heapsort
	.syntax unified
	.arm
	.fpu softvfp
	.type	heapsort, %function
heapsort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	bxle	lr
	ldr	r3, [r0, #4]
	cmp	r1, #2
	push	{r4, r5, r6, lr}
	sub	ip, r1, #1
	ldr	lr, [r0, r1, lsl #2]
	add	r4, r0, r1, lsl #2
	str	r3, [r0, r1, lsl #2]
	str	lr, [r0, #4]
	popeq	{r4, r5, r6, pc}
	add	r6, r0, #8
.L15:
	mov	r3, #2
	b	.L14
.L26:
	cmp	r3, ip
	str	r2, [r0, r1, lsl #2]
	bgt	.L25
.L14:
	cmp	r3, ip
	lsl	r1, r3, #2
	ldr	r2, [r0, r3, lsl #2]
	add	r1, r0, r1
	bge	.L12
	ldr	r1, [r1, #4]
	cmp	r1, r2
	addgt	r3, r3, #1
	movgt	r2, r1
.L12:
	asr	r1, r3, #1
	cmp	lr, r2
	lsl	r3, r3, #1
	add	r5, r0, r1, lsl #2
	ble	.L26
.L13:
	str	lr, [r5]
	sub	ip, ip, #1
	ldr	lr, [r4, #-4]!
	ldr	r3, [r0, #4]
	cmp	r6, r4
	str	r3, [r4]
	str	lr, [r0, #4]
	bne	.L15
	pop	{r4, r5, r6, pc}
.L25:
	add	r5, r0, r3, lsl #1
	b	.L13
	.size	heapsort, .-heapsort
	.align	2
	.global	build_maxheap
	.syntax unified
	.arm
	.fpu softvfp
	.type	build_maxheap, %function
build_maxheap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, r7, r8, lr}
	add	r5, r1, r1, lsr #31
	pople	{r4, r5, r6, r7, r8, pc}
	asr	r5, r5, #1
	add	r8, r0, r5, lsl #2
	lsl	r4, r5, #1
.L33:
	cmp	r1, r4
	mov	r2, r8
	mov	r3, r4
	ldr	r7, [r8], #-4
	bge	.L32
	b	.L29
.L31:
	lsl	r3, r3, #1
	str	ip, [r0, lr, lsl #2]
	cmp	r1, r3
	blt	.L29
.L32:
	cmp	r1, r3
	lsl	r2, r3, #2
	add	lr, r2, #4
	ldr	ip, [r0, r3, lsl #2]
	add	r2, r0, r2
	ble	.L30
	ldr	r6, [r0, lr]
	add	lr, r0, lr
	cmp	r6, ip
	addgt	r3, r3, #1
	movgt	ip, r6
	movgt	r2, lr
.L30:
	cmp	r7, ip
	asr	lr, r3, #1
	ble	.L31
	add	r2, r0, lr, lsl #2
.L29:
	subs	r5, r5, #1
	sub	r4, r4, #2
	str	r7, [r2]
	bne	.L33
	pop	{r4, r5, r6, r7, r8, pc}
	.size	build_maxheap, .-build_maxheap
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Sorted Output\000"
	.align	2
.LC1:
	.ascii	"%d\012\000"
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
	mov	r0, #5
	mov	r1, #4
	add	r6, sp, #16
	strd	r0, [sp, #4]
	add	r5, sp, #24
	mov	r0, #3
	mov	r1, #2
	mov	lr, #6
	strd	r0, [sp, #12]
	mov	r0, #1
	mov	r1, #0
	strd	r0, [sp, #20]
	b	.L46
.L56:
	ldr	r3, [sp, #24]
	add	r0, sp, #12
	cmp	ip, r3
	ble	.L54
.L45:
	subs	lr, lr, #2
	str	ip, [r0]
	beq	.L55
.L46:
	ldr	ip, [r6, #-4]!
	mov	r2, lr
.L44:
	add	r4, r2, #1
	cmp	r2, #6
	lsl	r0, r4, #2
	beq	.L56
	add	r8, sp, #80
	sub	r1, r0, #4
	add	r8, r8, r0
	add	r7, sp, r1
	ldr	r1, [sp, r1]
	asr	r3, r2, #1
	ldr	r8, [r8, #-80]
	lsl	r3, r3, #2
	cmp	r8, r1
	addgt	r7, sp, r0
	movgt	r2, r4
	asrgt	r3, r2, #1
	ldrgt	r1, [sp, r2, lsl #2]
	lsl	r2, r2, #1
	lslgt	r3, r3, #2
	cmp	ip, r1
	add	r0, sp, r3
	bgt	.L45
	cmp	r2, #6
	str	r1, [sp, r3]
	ble	.L44
	mov	r0, r7
	b	.L45
.L54:
	subs	lr, lr, #2
	mov	r0, r5
	str	r3, [sp, #12]
	str	ip, [r0]
	bne	.L46
.L55:
	mov	r1, #6
	mov	r0, sp
	bl	heapsort
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	movw	r6, #:lower16:.LC1
	bl	puts
	movt	r6, #:upper16:.LC1
	mov	r4, sp
.L47:
	ldr	r2, [r4, #4]!
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L47
	mov	r0, #0
	add	sp, sp, #80
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
