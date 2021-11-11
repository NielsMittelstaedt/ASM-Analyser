	.arch armv7-a
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"test.c"
	.text
	.global	__aeabi_ldivmod
	.align	2
	.global	mulmod
	.syntax unified
	.arm
	.fpu softvfp
	.type	mulmod, %function
mulmod:
	@ args = 8, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, fp, lr}
	add	fp, sp, #28
	sub	sp, sp, #72
	strd	r0, [fp, #-52]
	strd	r2, [fp, #-60]
	mov	r2, #0
	mov	r3, #0
	strd	r2, [fp, #-36]
	ldrd	r0, [fp, #-52]
	ldrd	r2, [fp, #4]
	bl	__aeabi_ldivmod
	strd	r2, [fp, #-44]
	b	.L2
.L4:
	ldrd	r0, [fp, #-60]
	asr	r3, r1, #31
	mov	r2, r3
	asr	r3, r2, #31
	eor	ip, r0, r2
	str	ip, [fp, #-84]
	eor	r1, r1, r3
	str	r1, [fp, #-80]
	ldrd	r0, [fp, #-84]
	mov	ip, r0
	subs	ip, ip, r2
	str	ip, [fp, #-68]
	sbc	r1, r1, r3
	str	r1, [fp, #-64]
	mov	r0, #1
	mov	r1, #0
	ldr	ip, [fp, #-68]
	and	r8, ip, r0
	ldr	ip, [fp, #-64]
	and	r9, ip, r1
	eor	r6, r8, r2
	eor	r7, r9, r3
	subs	r1, r6, r2
	str	r1, [fp, #-92]
	sbc	r3, r7, r3
	str	r3, [fp, #-88]
	ldrd	r2, [fp, #-92]
	cmp	r3, #0
	cmpeq	r2, #1
	bne	.L3
	ldrd	r0, [fp, #-36]
	ldrd	r2, [fp, #-44]
	adds	ip, r0, r2
	str	ip, [fp, #-76]
	adc	r3, r1, r3
	str	r3, [fp, #-72]
	ldrd	r2, [fp, #4]
	ldrd	r0, [fp, #-76]
	bl	__aeabi_ldivmod
	strd	r2, [fp, #-36]
.L3:
	ldrd	r2, [fp, #-44]
	adds	r1, r2, r2
	str	r1, [fp, #-100]
	adc	r3, r3, r3
	str	r3, [fp, #-96]
	ldrd	r0, [fp, #-100]
	ldrd	r2, [fp, #4]
	bl	__aeabi_ldivmod
	strd	r2, [fp, #-44]
	ldrd	r0, [fp, #-60]
	lsr	r3, r1, #31
	mov	r2, r3
	mov	r3, #0
	adds	r4, r2, r0
	adc	r5, r3, r1
	mov	r2, #0
	mov	r3, #0
	lsr	r2, r4, #1
	orr	r2, r2, r5, lsl #31
	asr	r3, r5, #1
	strd	r2, [fp, #-60]
.L2:
	ldrd	r2, [fp, #-60]
	cmp	r2, #1
	sbcs	r3, r3, #0
	bge	.L4
	ldrd	r0, [fp, #-36]
	ldrd	r2, [fp, #4]
	bl	__aeabi_ldivmod
	mov	r0, r2
	mov	r1, r3
	sub	sp, fp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, fp, pc}
	.size	mulmod, .-mulmod
	.align	2
	.global	modulo
	.syntax unified
	.arm
	.fpu softvfp
	.type	modulo, %function
modulo:
	@ args = 8, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, fp, lr}
	add	fp, sp, #28
	sub	sp, sp, #56
	strd	r0, [fp, #-52]
	strd	r2, [fp, #-60]
	mov	r2, #1
	mov	r3, #0
	strd	r2, [fp, #-36]
	ldrd	r2, [fp, #-52]
	strd	r2, [fp, #-44]
	b	.L7
.L9:
	ldrd	r0, [fp, #-60]
	asr	r3, r1, #31
	mov	r2, r3
	asr	r3, r2, #31
	eor	ip, r0, r2
	str	ip, [fp, #-68]
	eor	r1, r1, r3
	str	r1, [fp, #-64]
	ldrd	r0, [fp, #-68]
	mov	ip, r0
	subs	r6, ip, r2
	sbc	r7, r1, r3
	mov	r0, #1
	mov	r1, #0
	and	ip, r6, r0
	str	ip, [fp, #-76]
	and	r1, r7, r1
	str	r1, [fp, #-72]
	ldrd	r0, [fp, #-76]
	mov	ip, r0
	eor	r8, ip, r2
	eor	r9, r1, r3
	subs	r1, r8, r2
	str	r1, [fp, #-84]
	sbc	r3, r9, r3
	str	r3, [fp, #-80]
	ldrd	r2, [fp, #-84]
	cmp	r3, #0
	cmpeq	r2, #1
	bne	.L8
	ldr	r3, [fp, #-32]
	ldr	r2, [fp, #-44]
	mul	r1, r2, r3
	ldr	r2, [fp, #-40]
	ldr	r3, [fp, #-36]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldr	r2, [fp, #-36]
	ldr	r3, [fp, #-44]
	umull	r0, r1, r2, r3
	add	r3, ip, r1
	mov	r1, r3
	ldrd	r2, [fp, #4]
	bl	__aeabi_ldivmod
	strd	r2, [fp, #-36]
.L8:
	ldr	r3, [fp, #-40]
	ldr	r2, [fp, #-44]
	mul	r1, r2, r3
	ldr	r2, [fp, #-40]
	ldr	r3, [fp, #-44]
	mul	r3, r3, r2
	add	r2, r1, r3
	ldr	r3, [fp, #-44]
	umull	r0, r1, r3, r3
	add	r3, r2, r1
	mov	r1, r3
	ldrd	r2, [fp, #4]
	bl	__aeabi_ldivmod
	strd	r2, [fp, #-44]
	ldrd	r0, [fp, #-60]
	lsr	r3, r1, #31
	mov	r2, r3
	mov	r3, #0
	adds	r4, r2, r0
	adc	r5, r3, r1
	mov	r2, #0
	mov	r3, #0
	lsr	r2, r4, #1
	orr	r2, r2, r5, lsl #31
	asr	r3, r5, #1
	strd	r2, [fp, #-60]
.L7:
	ldrd	r2, [fp, #-60]
	cmp	r2, #1
	sbcs	r3, r3, #0
	bge	.L9
	ldrd	r0, [fp, #-36]
	ldrd	r2, [fp, #4]
	bl	__aeabi_ldivmod
	mov	r0, r2
	mov	r1, r3
	sub	sp, fp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, fp, pc}
	.size	modulo, .-modulo
	.align	2
	.global	Miller
	.syntax unified
	.arm
	.fpu softvfp
	.type	Miller, %function
Miller:
	@ args = 0, pretend = 0, frame = 120
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, fp, lr}
	add	fp, sp, #28
	sub	sp, sp, #128
	strd	r0, [fp, #-76]
	str	r2, [fp, #-80]
	ldrd	r2, [fp, #-76]
	cmp	r2, #2
	sbcs	r3, r3, #0
	bge	.L12
	mov	r3, #0
	b	.L13
.L12:
	ldrd	r2, [fp, #-76]
	cmp	r3, #0
	cmpeq	r2, #2
	beq	.L14
	ldrd	r0, [fp, #-76]
	mov	r2, #1
	mov	r3, #0
	and	r4, r0, r2
	and	r5, r1, r3
	orrs	r3, r4, r5
	bne	.L14
	mov	r3, #0
	b	.L13
.L14:
	ldrd	r2, [fp, #-76]
	subs	r8, r2, #1
	sbc	r9, r3, #0
	strd	r8, [fp, #-44]
	b	.L15
.L16:
	ldrd	r0, [fp, #-44]
	lsr	r3, r1, #31
	mov	r2, r3
	mov	r3, #0
	adds	r6, r2, r0
	adc	r7, r3, r1
	mov	r2, #0
	mov	r3, #0
	lsr	r2, r6, #1
	orr	r2, r2, r7, lsl #31
	asr	r3, r7, #1
	strd	r2, [fp, #-44]
.L15:
	ldrd	r0, [fp, #-44]
	mov	r2, #1
	mov	r3, #0
	and	ip, r0, r2
	str	ip, [fp, #-92]
	and	r3, r1, r3
	str	r3, [fp, #-88]
	ldrd	r2, [fp, #-92]
	orrs	r3, r2, r3
	beq	.L16
	mov	r3, #0
	str	r3, [fp, #-32]
	b	.L17
.L22:
	bl	rand
	mov	r3, r0
	mov	r0, r3
	asr	r1, r0, #31
	ldrd	r2, [fp, #-76]
	subs	ip, r2, #1
	str	ip, [fp, #-100]
	sbc	r3, r3, #0
	str	r3, [fp, #-96]
	ldrd	r2, [fp, #-100]
	bl	__aeabi_ldivmod
	adds	r1, r2, #1
	str	r1, [fp, #-140]
	adc	r3, r3, #0
	str	r3, [fp, #-136]
	ldrd	r2, [fp, #-140]
	strd	r2, [fp, #-68]
	ldrd	r2, [fp, #-44]
	strd	r2, [fp, #-52]
	ldrd	r2, [fp, #-76]
	strd	r2, [sp]
	ldrd	r2, [fp, #-52]
	ldrd	r0, [fp, #-68]
	bl	modulo
	strd	r0, [fp, #-60]
	b	.L18
.L20:
	ldrd	r2, [fp, #-76]
	strd	r2, [sp]
	ldrd	r2, [fp, #-60]
	ldrd	r0, [fp, #-60]
	bl	mulmod
	strd	r0, [fp, #-60]
	ldrd	r2, [fp, #-52]
	adds	r1, r2, r2
	str	r1, [fp, #-148]
	adc	r3, r3, r3
	str	r3, [fp, #-144]
	ldrd	r2, [fp, #-148]
	strd	r2, [fp, #-52]
.L18:
	ldrd	r2, [fp, #-76]
	subs	r1, r2, #1
	str	r1, [fp, #-108]
	sbc	r3, r3, #0
	str	r3, [fp, #-104]
	ldrd	r2, [fp, #-52]
	ldrd	r0, [fp, #-108]
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L19
	ldrd	r2, [fp, #-60]
	cmp	r3, #0
	cmpeq	r2, #1
	beq	.L19
	ldrd	r2, [fp, #-76]
	subs	r1, r2, #1
	str	r1, [fp, #-116]
	sbc	r3, r3, #0
	str	r3, [fp, #-112]
	ldrd	r2, [fp, #-60]
	ldrd	r0, [fp, #-116]
	cmp	r3, r1
	cmpeq	r2, r0
	bne	.L20
.L19:
	ldrd	r2, [fp, #-76]
	subs	r1, r2, #1
	str	r1, [fp, #-124]
	sbc	r3, r3, #0
	str	r3, [fp, #-120]
	ldrd	r2, [fp, #-60]
	ldrd	r0, [fp, #-124]
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L21
	ldrd	r0, [fp, #-52]
	mov	r2, #1
	mov	r3, #0
	and	ip, r0, r2
	str	ip, [fp, #-132]
	and	r3, r1, r3
	str	r3, [fp, #-128]
	ldrd	r2, [fp, #-132]
	orrs	r3, r2, r3
	bne	.L21
	mov	r3, #0
	b	.L13
.L21:
	ldr	r3, [fp, #-32]
	add	r3, r3, #1
	str	r3, [fp, #-32]
.L17:
	ldr	r2, [fp, #-32]
	ldr	r3, [fp, #-80]
	cmp	r2, r3
	blt	.L22
	mov	r3, #1
.L13:
	mov	r0, r3
	sub	sp, fp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, fp, pc}
	.size	Miller, .-Miller
	.section	.rodata
	.align	2
.LC0:
	.ascii	"\012%lld is prime\012\000"
	.align	2
.LC1:
	.ascii	"\012%lld is not prime\012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	mov	r3, #5
	str	r3, [fp, #-8]
	mov	r2, #117
	mov	r3, #0
	strd	r2, [fp, #-20]
	ldr	r2, [fp, #-8]
	ldrd	r0, [fp, #-20]
	bl	Miller
	mov	r3, r0
	cmp	r3, #0
	beq	.L24
	ldrd	r2, [fp, #-20]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	b	.L25
.L24:
	ldrd	r2, [fp, #-20]
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	printf
.L25:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
