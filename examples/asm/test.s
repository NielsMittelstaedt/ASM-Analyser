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
	.file	"test.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"%s\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movw	r4, #:lower16:.LANCHOR0
	movt	r4, #:upper16:.LANCHOR0
	sub	sp, sp, #104
	mov	r6, #0
	add	ip, sp, #52
	ldmia	r4!, {r0, r1, r2, r3}
	mov	lr, sp
	mov	r5, sp
	str	r6, [sp, #30]	@ unaligned
	str	r6, [sp, #34]	@ unaligned
	str	r6, [sp, #38]	@ unaligned
	stmia	lr!, {r0, r1, r2, r3}
	ldm	r4, {r0, r1, r2, r3}
	str	r6, [sp, #42]	@ unaligned
	str	r6, [sp, #46]	@ unaligned
	stmia	lr!, {r0, r1, r2}
	strh	r3, [lr]	@ movhi
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	r5, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2}
	add	r2, sp, #52
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	strh	r3, [ip]	@ movhi
	bl	__printf_chk
	mov	r0, r6
	add	sp, sp, #104
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.ascii	"http://www.tutorialspoint.com\000"
	.space	20
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
