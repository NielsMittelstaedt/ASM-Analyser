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
	.file	"ternary_search.c"
	.text
	.align	2
	.global	ternarySearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	ternarySearch, %function
ternarySearch:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r0, r1
	bgt	.L10
	push	{r4, r5, r6, r7, lr}
	movw	r7, #43691
	movw	r6, #21846
	movt	r7, 43690
	movt	r6, 21845
	mov	lr, r0
	b	.L2
.L16:
	cmp	r4, r2
	subgt	r1, r0, #1
	bgt	.L5
	cmp	r5, r2
	add	lr, ip, #1
	subge	r1, ip, #1
	addge	lr, r0, #1
.L5:
	cmp	r1, lr
	blt	.L7
.L2:
	sub	r4, r1, lr
	umull	ip, r0, r7, r4
	smull	r5, ip, r6, r4
	add	r0, lr, r0, lsr #1
	rsb	ip, ip, r4, asr #31
	add	ip, ip, r1
	ldr	r4, [r3, r0, lsl #2]
	cmp	r4, r2
	popeq	{r4, r5, r6, r7, pc}
	ldr	r5, [r3, ip, lsl #2]
	cmp	r5, r2
	bne	.L16
	mov	r0, ip
	pop	{r4, r5, r6, r7, pc}
.L7:
	mvn	r0, #0
	pop	{r4, r5, r6, r7, pc}
.L10:
	mvn	r0, #0
	bx	lr
	.size	ternarySearch, .-ternarySearch
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"Index of %d is \000"
	.align	2
.LC2:
	.ascii	"%d\012\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #40
	ldmia	ip!, {r0, r1, r2, r3}
	mov	lr, sp
	movw	r5, #:lower16:.LC1
	movt	r5, #:upper16:.LC1
	movw	r4, #:lower16:.LC2
	movt	r4, #:upper16:.LC2
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	mov	r3, sp
	ldm	ip, {r0, r1}
	mov	r2, #5
	stm	lr, {r0, r1}
	mov	r1, #9
	mov	r0, #0
	bl	ternarySearch
	mov	r1, r5
	mov	r2, #5
	mov	r6, r0
	mov	r0, #1
	bl	__printf_chk
	mov	r2, r6
	mov	r1, r4
	mov	r0, #1
	bl	__printf_chk
	mov	r3, sp
	mov	r2, #50
	mov	r1, #9
	mov	r0, #0
	bl	ternarySearch
	mov	r1, r5
	mov	r2, #50
	mov	r5, r0
	mov	r0, #1
	bl	__printf_chk
	mov	r2, r5
	mov	r1, r4
	mov	r0, #1
	bl	__printf_chk
	mov	r0, #0
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
