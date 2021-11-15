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
	.file	"test1.c"
	.text
	.align	2
	.global	ldr
	.syntax unified
	.arm
	.fpu softvfp
	.type	ldr, %function
ldr:
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	movw	ip, #:lower16:.LANCHOR0
	ldrb	r6, [sp, #24]	@ zero_extendqisi2
	movt	ip, #:upper16:.LANCHOR0
	ldr	lr, [r1]
	ldr	r5, [ip]
	cmp	r6, #0
	mov	ip, #0
	ldrb	r7, [sp, #20]	@ zero_extendqisi2
	add	r5, r5, lr
	str	ip, [r0]
	bne	.L2
	cmp	r3, ip
	add	r5, r5, r2
	ble	.L7
.L3:
	sub	r3, r3, #1
	sub	lr, r5, #1
	add	r5, r5, r3
	mov	r3, #0
	mov	ip, r3
.L6:
	ldrb	r4, [lr, #1]!	@ zero_extendqisi2
	cmp	r5, lr
	add	ip, ip, r4, lsl r3
	add	r3, r3, #8
	str	ip, [r0]
	bne	.L6
.L7:
	orrs	r3, r6, r7
	popeq	{r4, r5, r6, r7, pc}
.L4:
	ldr	r3, [r1]
	add	r2, r3, r2
	str	r2, [r1]
	pop	{r4, r5, r6, r7, pc}
.L2:
	cmp	r3, #0
	bgt	.L3
	b	.L4
	.size	ldr, .-ldr
	.align	2
	.global	str
	.syntax unified
	.arm
	.fpu softvfp
	.type	str, %function
str:
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	movw	ip, #:lower16:.LANCHOR0
	ldrb	r6, [sp, #24]	@ zero_extendqisi2
	movt	ip, #:upper16:.LANCHOR0
	ldr	lr, [r1]
	ldr	r4, [ip]
	cmp	r6, #0
	ldrb	r7, [sp, #20]	@ zero_extendqisi2
	add	r4, r4, lr
	bne	.L12
	cmp	r3, #0
	add	r4, r4, r2
	ble	.L17
.L13:
	sub	r4, r4, #1
	mov	ip, #0
.L16:
	ldr	lr, [r0]
	lsl	r5, ip, #3
	add	ip, ip, #1
	cmp	r3, ip
	asr	lr, lr, r5
	strb	lr, [r4, #1]!
	bgt	.L16
.L17:
	orrs	r3, r6, r7
	popeq	{r4, r5, r6, r7, pc}
	ldr	lr, [r1]
.L18:
	add	r2, r2, lr
	str	r2, [r1]
	pop	{r4, r5, r6, r7, pc}
.L12:
	cmp	r3, #0
	bgt	.L13
	b	.L18
	.size	str, .-str
	.align	2
	.global	malloc_start
	.syntax unified
	.arm
	.fpu softvfp
	.type	malloc_start, %function
malloc_start:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r0, #1
	bl	malloc
	movw	r3, #:lower16:.LANCHOR0
	movt	r3, #:upper16:.LANCHOR0
	mov	r4, r0
	mov	r0, #1000
	str	r4, [r3]
	bl	malloc
	movw	r2, #:lower16:sp
	movw	r3, #:lower16:fp
	movt	r2, #:upper16:sp
	movt	r3, #:upper16:fp
	sub	r0, r0, r4
	add	r0, r0, #996
	add	r0, r0, #3
	str	r0, [r2]
	str	r0, [r3]
	pop	{r4, pc}
	.size	malloc_start, .-malloc_start
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"r1: %d\012\000"
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
	push	{r4, r5, r6, r7, r8, lr}
	bl	malloc_start
	movw	r2, #:lower16:fp
	movt	r2, #:upper16:fp
	movw	r4, #:lower16:.LANCHOR0
	movt	r4, #:upper16:.LANCHOR0
	movw	r3, #:lower16:r0
	ldr	lr, [r2]
	movt	r3, #:upper16:r0
	ldr	r0, [r4]
	movw	ip, #:lower16:r1
	sub	r1, lr, #12
	movt	ip, #:upper16:r1
	str	r1, [r3]
	mov	r6, #123
	str	r1, [r2]
	add	lr, r0, lr
	str	r6, [ip]
	mov	r5, #0
	strb	r6, [r0, r1]
	movw	r1, #:lower16:.LC0
	ldr	r6, [ip]
	movt	r1, #:upper16:.LC0
	mov	r0, #1
	asr	r6, r6, #8
	strb	r6, [lr, #-11]
	ldrsh	r6, [ip, #2]
	strb	r6, [lr, #-10]
	ldrsb	r6, [ip, #3]
	strb	r6, [lr, #-9]
	ldr	r7, [r2]
	ldr	lr, [r4]
	ldr	r6, [r3]
	add	lr, lr, r7
	strb	r6, [lr, #4]
	ldr	r6, [r3]
	asr	r6, r6, #8
	strb	r6, [lr, #5]
	ldrsh	r6, [r3, #2]
	strb	r6, [lr, #6]
	ldrsb	r6, [r3, #3]
	strb	r6, [lr, #7]
	ldr	lr, [r4]
	ldr	r4, [r2]
	str	r5, [r3]
	add	r4, lr, r4
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	str	r2, [r3]
	ldrb	r6, [r4, #5]	@ zero_extendqisi2
	add	r2, r2, r6, lsl #8
	str	r2, [r3]
	ldrb	r6, [r4, #6]	@ zero_extendqisi2
	add	r2, r2, r6, lsl #16
	str	r2, [r3]
	ldrb	r4, [r4, #7]	@ zero_extendqisi2
	add	r2, r2, r4, lsl #24
	str	r2, [r3]
	str	r5, [ip]
	ldrb	r2, [lr, r2]!	@ zero_extendqisi2
	str	r2, [ip]
	ldrb	r3, [lr, #1]	@ zero_extendqisi2
	add	r2, r2, r3, lsl #8
	str	r2, [ip]
	ldrb	r3, [lr, #2]	@ zero_extendqisi2
	add	r2, r2, r3, lsl #16
	str	r2, [ip]
	ldrb	r3, [lr, #3]	@ zero_extendqisi2
	pop	{r4, r5, r6, r7, r8, lr}
	add	r2, r2, r3, lsl #24
	str	r2, [ip]
	b	__printf_chk
	.size	main, .-main
	.comm	r0,4,4
	.comm	r3,4,4
	.comm	r2,4,4
	.comm	r1,4,4
	.global	malloc_0
	.comm	v,1,1
	.comm	c,1,1
	.comm	n,1,1
	.comm	z,1,1
	.comm	ip,4,4
	.comm	pc,4,4
	.comm	lr,4,4
	.comm	fp,4,4
	.comm	sp,4,4
	.comm	tmp,4,4
	.bss
	.align	2
	.set	.LANCHOR0,. + 0
	.type	malloc_0, %object
	.size	malloc_0, 4
malloc_0:
	.space	4
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
