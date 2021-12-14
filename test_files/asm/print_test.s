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
	.file	"print_test.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"\012------------------Simplex Table Step = %d------"
	.ascii	"-----------\012\000"
	.align	2
.LC2:
	.ascii	"%10lf \000"
	.text
	.align	2
	.global	ShowTable
	.syntax unified
	.arm
	.fpu softvfp
	.type	ShowTable, %function
ShowTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r2, r0
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	ldr	r5, .L8
	bl	__printf_chk
	movw	r6, #:lower16:.LC2
	add	r7, r5, #120
	movt	r6, #:upper16:.LC2
.L2:
	sub	r4, r5, #40
.L3:
	ldrd	r2, [r4], #8
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r5
	bne	.L3
	add	r5, r4, #40
	mov	r0, #10
	bl	putchar
	cmp	r5, r7
	bne	.L2
	pop	{r4, r5, r6, r7, r8, pc}
.L9:
	.align	2
.L8:
	.word	SimplexTable+40
	.size	ShowTable, .-ShowTable
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 120
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	sub	sp, sp, #124
	mov	r2, #120
	movw	r1, #:lower16:.LANCHOR0
	mov	r0, sp
	movt	r1, #:upper16:.LANCHOR0
	bl	memcpy
	ldrd	r2, [sp, #8]
	ldrd	r4, [sp, #16]
	movw	ip, #:lower16:SimplexTable
	movt	ip, #:upper16:SimplexTable
	ldrd	r0, [sp]
	strd	r2, [ip, #8]
	strd	r4, [ip, #16]
	ldrd	r2, [sp, #24]
	ldrd	r4, [sp, #32]
	strd	r0, [ip]
	mov	r0, #10
	strd	r2, [ip, #24]
	strd	r4, [ip, #32]
	ldrd	r2, [sp, #40]
	ldrd	r4, [sp, #48]
	strd	r2, [ip, #40]
	strd	r4, [ip, #48]
	ldrd	r2, [sp, #56]
	ldrd	r4, [sp, #64]
	strd	r2, [ip, #56]
	strd	r4, [ip, #64]
	ldrd	r2, [sp, #72]
	ldrd	r4, [sp, #80]
	strd	r2, [ip, #72]
	strd	r4, [ip, #80]
	ldrd	r2, [sp, #88]
	ldrd	r4, [sp, #96]
	strd	r2, [ip, #88]
	strd	r4, [ip, #96]
	ldrd	r2, [sp, #104]
	ldrd	r4, [sp, #112]
	strd	r2, [ip, #104]
	strd	r4, [ip, #112]
	bl	ShowTable
	mov	r0, #0
	add	sp, sp, #124
	@ sp needed
	pop	{r4, r5, pc}
	.size	main, .-main
	.comm	SimplexTable,120,8
	.section	.rodata
	.align	3
	.set	.LANCHOR0,. + 0
.LC0:
	.word	0
	.word	1077739520
	.word	0
	.word	1078362112
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1073741824
	.word	0
	.word	1075838976
	.word	0
	.word	1072693248
	.word	0
	.word	0
	.word	0
	.word	1078853632
	.word	0
	.word	1074790400
	.word	0
	.word	1074790400
	.word	0
	.word	0
	.word	0
	.word	1072693248
	.word	0
	.word	1078853632
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
