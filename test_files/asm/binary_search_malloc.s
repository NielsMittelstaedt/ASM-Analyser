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
	.file	"binary_search_malloc.c"
	.text
	.align	2
	.global	binarySearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	binarySearch, %function
binarySearch:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, r2
	str	lr, [sp, #-4]!
	mov	lr, r0
	bgt	.L8
.L2:
	sub	r0, r2, r1
	add	r0, r1, r0, asr #1
	ldr	ip, [lr, r0, lsl #2]
	cmp	ip, r3
	ldreq	pc, [sp], #4
	ble	.L4
	sub	r2, r0, #1
	cmp	r2, r1
	bge	.L2
.L8:
	mvn	r0, #0
	ldr	pc, [sp], #4
.L4:
	add	r1, r0, #1
	cmp	r1, r2
	ble	.L2
	b	.L8
	.size	binarySearch, .-binarySearch
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
	mov	r0, #20
	bl	malloc
	mov	r2, #0
	mov	r1, #4
	mov	r4, #2
	mov	r5, #3
	mov	r3, #40
	strd	r4, [r0]
	mov	r4, #4
	mov	r5, #10
	str	r3, [r0, #16]
	strd	r4, [r0, #8]
.L11:
	sub	r3, r1, r2
	add	r3, r2, r3, asr #1
	ldr	ip, [r0, r3, lsl #2]
	cmp	ip, #10
	beq	.L12
	ble	.L13
	sub	r1, r3, #1
	cmp	r1, r2
	bge	.L11
.L12:
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, pc}
.L13:
	add	r2, r3, #1
	cmp	r2, r1
	ble	.L11
	b	.L12
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits