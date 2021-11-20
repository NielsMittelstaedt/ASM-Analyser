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
	.file	"miller_rabin.c"
	.text
	.global	__aeabi_idivmod
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	Miller.part.0, %function
Miller.part.0:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	tst	r0, #1
	sub	sp, sp, #12
	sub	r8, r0, #1
	mov	fp, r0
	mov	r9, r8
	str	r1, [sp, #4]
	beq	.L2
.L3:
	asr	r9, r9, #1
	tst	r9, #1
	beq	.L3
.L2:
	ldr	r3, [sp, #4]
	cmp	r3, #0
	movgt	r3, #0
	strgt	r3, [sp]
	ble	.L14
.L4:
	bl	rand
	mov	r1, r8
	bl	__aeabi_idivmod
	mov	r6, r9
	mov	r5, #1
	add	r4, r1, #1
.L7:
	tst	r6, #1
	mov	r1, fp
	mul	r0, r4, r5
	beq	.L6
	bl	__aeabi_idivmod
	mov	r5, r1
.L6:
	mul	r0, r4, r4
	mov	r1, fp
	bl	__aeabi_idivmod
	asrs	r6, r6, #1
	mov	r4, r1
	bne	.L7
	mov	r0, r5
	mov	r1, fp
	bl	__aeabi_idivmod
	cmp	r8, r9
	mov	r10, r1
	beq	.L18
	cmp	r1, #1
	beq	.L19
	cmp	r8, r1
	beq	.L9
	mov	r7, r9
.L13:
	mov	r1, fp
	mov	r0, r10
	bl	__aeabi_idivmod
	cmp	r10, #0
	lsl	r7, r7, #1
	mov	r4, r1
	ble	.L10
	mov	r5, #0
.L12:
	tst	r10, #1
	add	r0, r5, r4
	mov	r1, fp
	beq	.L11
	bl	__aeabi_idivmod
	mov	r5, r1
.L11:
	lsl	r0, r4, #1
	mov	r1, fp
	bl	__aeabi_idivmod
	asrs	r10, r10, #1
	mov	r4, r1
	bne	.L12
	mov	r0, r5
	mov	r1, fp
	bl	__aeabi_idivmod
	cmp	r8, r7
	mov	r10, r1
	beq	.L8
	cmp	r1, #1
	beq	.L8
	cmp	r8, r1
	bne	.L13
.L9:
	ldr	r3, [sp]
	ldr	r2, [sp, #4]
	add	r3, r3, #1
	str	r3, [sp]
	cmp	r3, r2
	bne	.L4
.L14:
	mov	r6, #1
.L1:
	mov	r0, r6
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L41:
	lsl	r7, r7, #1
.L10:
	cmp	r8, r7
	bne	.L41
	tst	r7, #1
	bne	.L9
	b	.L1
.L19:
	mov	r7, r9
.L8:
	cmp	r8, r10
	beq	.L9
.L42:
	tst	r7, #1
	bne	.L9
	b	.L1
.L18:
	cmp	r8, r10
	mov	r7, r8
	bne	.L42
	b	.L9
	.size	Miller.part.0, .-Miller.part.0
	.align	2
	.global	mulmod
	.syntax unified
	.arm
	.fpu softvfp
	.type	mulmod, %function
mulmod:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r5, r1
	mov	r1, r2
	mov	r7, r2
	bl	__aeabi_idivmod
	cmp	r5, #0
	ble	.L47
	mov	r4, r1
	mov	r6, #0
.L46:
	tst	r5, #1
	add	r0, r6, r4
	mov	r1, r7
	beq	.L45
	bl	__aeabi_idivmod
	mov	r6, r1
.L45:
	lsl	r0, r4, #1
	mov	r1, r7
	bl	__aeabi_idivmod
	asrs	r5, r5, #1
	mov	r4, r1
	bne	.L46
	mov	r1, r7
	mov	r0, r6
	bl	__aeabi_idivmod
	mov	r0, r1
	pop	{r4, r5, r6, r7, r8, pc}
.L47:
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	mulmod, .-mulmod
	.align	2
	.global	modulo
	.syntax unified
	.arm
	.fpu softvfp
	.type	modulo, %function
modulo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	subs	r5, r1, #0
	mov	r7, r2
	ble	.L57
	mov	r4, r0
	mov	r6, #1
.L56:
	tst	r5, #1
	mov	r1, r7
	mul	r0, r4, r6
	beq	.L55
	bl	__aeabi_idivmod
	mov	r6, r1
.L55:
	mul	r0, r4, r4
	mov	r1, r7
	bl	__aeabi_idivmod
	asrs	r5, r5, #1
	mov	r4, r1
	bne	.L56
.L54:
	mov	r1, r7
	mov	r0, r6
	bl	__aeabi_idivmod
	mov	r0, r1
	pop	{r4, r5, r6, r7, r8, pc}
.L57:
	mov	r6, #1
	b	.L54
	.size	modulo, .-modulo
	.align	2
	.global	Miller
	.syntax unified
	.arm
	.fpu softvfp
	.type	Miller, %function
Miller:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r0, #1
	ble	.L63
	cmp	r0, #2
	beq	.L65
	tst	r0, #1
	beq	.L63
.L65:
	b	Miller.part.0
.L63:
	mov	r0, #0
	bx	lr
	.size	Miller, .-Miller
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"\012%d is prime\012\000"
	.align	2
.LC1:
	.ascii	"\012%d is not prime\012\000"
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
	mov	r1, #5
	mov	r0, #131
	push	{r4, lr}
	bl	Miller.part.0
	cmp	r0, #0
	mov	r0, #1
	movwne	r1, #:lower16:.LC0
	movweq	r1, #:lower16:.LC1
	movtne	r1, #:upper16:.LC0
	movteq	r1, #:upper16:.LC1
	movne	r2, #131
	moveq	r2, #131
	bl	__printf_chk
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
