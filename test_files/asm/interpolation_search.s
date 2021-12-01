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
	.file	"interpolation_search.c"
	.text
	.global	__aeabi_uidiv
	.global	__aeabi_idiv
	.align	2
	.global	interpolationSearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	interpolationSearch, %function
interpolationSearch:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	subs	r6, r1, #1
	movpl	r7, r0
	movpl	r5, r2
	movpl	r4, #0
	bpl	.L2
	b	.L9
.L12:
	ldr	r3, [r7, r6, lsl #2]
	cmp	r3, r5
	sub	r1, r3, r1
	blt	.L9
	bl	__aeabi_idiv
	add	r0, r0, r4
	ldr	r3, [r7, r0, lsl #2]
	cmp	r3, r5
	addlt	r4, r0, #1
	blt	.L5
	sub	r6, r0, #1
	pople	{r4, r5, r6, r7, r8, pc}
.L5:
	cmp	r6, r4
	blt	.L9
.L2:
	ldr	r1, [r7, r4, lsl #2]
	sub	r3, r6, r4
	sub	r0, r5, r1
	cmp	r1, r5
	mul	r0, r3, r0
	ble	.L12
.L9:
	mvn	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	interpolationSearch, .-interpolationSearch
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"Array: \000"
	.align	2
.LC2:
	.ascii	"%d \000"
	.align	2
.LC3:
	.ascii	"\012Enter the number to be searched: \000"
	.align	2
.LC4:
	.ascii	"Element found at position: %d\012\000"
	.align	2
.LC5:
	.ascii	"Element not found.\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #64
	ldmia	ip!, {r0, r1, r2, r3}
	add	lr, sp, #4
	movw	r5, #:lower16:.LC2
	add	r6, sp, #60
	movt	r5, #:upper16:.LC2
	mov	r4, sp
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldm	ip, {r0, r1, r2}
	stm	lr, {r0, r1, r2}
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	bl	__printf_chk
.L14:
	ldr	r2, [r4, #4]!
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L14
	movw	r1, #:lower16:.LC3
	mov	r0, #1
	movt	r1, #:upper16:.LC3
	bl	__printf_chk
	mov	r2, #42
	add	r0, sp, #4
	mov	r1, #15
	bl	interpolationSearch
	cmn	r0, #1
	mov	r2, r0
	beq	.L15
	movw	r1, #:lower16:.LC4
	mov	r0, #1
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
.L16:
	mov	r0, #0
	add	sp, sp, #64
	@ sp needed
	pop	{r4, r5, r6, pc}
.L15:
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	puts
	b	.L16
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	10
	.word	12
	.word	13
	.word	16
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	33
	.word	35
	.word	42
	.word	47
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
