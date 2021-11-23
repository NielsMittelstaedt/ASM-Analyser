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
	.file	"counting_sort.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
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
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r0, #24
	bl	malloc
	mov	r1, #1
	mov	r3, #6
	mov	r4, #5
	mov	r5, #4
	movw	r7, #:lower16:.LC0
	movt	r7, #:upper16:.LC0
	mov	r9, r0
	mov	r0, #28
	strd	r4, [r9, #4]
	mov	r5, #2
	str	r1, [r9, #20]
	mov	r4, #3
	str	r3, [r9]
	strd	r4, [r9, #12]
	bl	calloc
	ldr	r1, [r9]
	mov	r5, #0
	ldr	r2, [r9, #4]
	ldr	r3, [r0, r1, lsl #2]
	mov	r8, r0
	ldr	r0, [r9, #8]
	sub	r6, r8, #4
	add	r3, r3, #1
	str	r3, [r8, r1, lsl #2]
	ldr	r3, [r8, r2, lsl #2]
	ldr	r1, [r9, #12]
	add	r3, r3, #1
	str	r3, [r8, r2, lsl #2]
	ldr	r3, [r8, r0, lsl #2]
	ldr	r2, [r9, #16]
	add	r3, r3, #1
	str	r3, [r8, r0, lsl #2]
	ldr	r3, [r8, r1, lsl #2]
	add	r3, r3, #1
	str	r3, [r8, r1, lsl #2]
	ldr	r3, [r8, r2, lsl #2]
	add	r3, r3, #1
	str	r3, [r8, r2, lsl #2]
	ldr	r3, [r8, #4]
	add	r3, r3, #1
	str	r3, [r8, #4]
	b	.L4
.L2:
	add	r5, r5, #1
	cmp	r5, #7
	beq	.L9
.L4:
	ldr	r4, [r6, #4]!
	cmp	r4, #0
	ble	.L2
.L3:
	sub	r4, r4, #1
	mov	r2, r5
	mov	r1, r7
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, #0
	str	r4, [r6]
	bne	.L3
	b	.L2
.L9:
	mov	r0, r9
	bl	free
	mov	r0, r8
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
