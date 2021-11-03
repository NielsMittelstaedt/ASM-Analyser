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
	.file	"insertion_sort.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"Sorted array:\000"
	.align	2
.LC2:
	.ascii	" %d\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #24
	ldmia	ip!, {r0, r1, r2, r3}
	add	lr, sp, #4
	stmia	lr!, {r0, r1, r2, r3}
	mov	r1, r0
	ldr	r3, [sp, #8]
	ldr	r2, [ip]
	cmp	r0, r3
	str	r2, [lr]
	movgt	r1, r3
	strgt	r3, [sp, #4]
	movgt	r3, r0
	strgt	r0, [sp, #8]
.L5:
	ldr	r2, [sp, #12]
	cmp	r3, r2
	ble	.L4
	mov	r0, r3
	str	r3, [sp, #12]
	str	r2, [sp, #8]
	mov	r3, r2
	mov	r2, r0
.L4:
	cmp	r1, r3
	ble	.L9
	mov	r0, r1
	str	r1, [sp, #8]
	str	r3, [sp, #4]
	mov	r1, r3
	mov	r3, r0
.L9:
	ldr	r0, [sp, #16]
	cmp	r2, r0
	bgt	.L7
.L8:
	cmp	r3, r2
	ble	.L15
	mov	ip, r3
	str	r3, [sp, #12]
	str	r2, [sp, #8]
	mov	r3, r2
	mov	r2, ip
.L15:
	cmp	r1, r3
	bgt	.L11
.L14:
	ldr	ip, [sp, #20]
	cmp	r0, ip
	strgt	r0, [sp, #20]
	movgt	r0, ip
	strgt	ip, [sp, #16]
.L13:
	cmp	r2, r0
	strgt	r0, [sp, #12]
	strgt	r2, [sp, #16]
	movw	r5, #:lower16:.LC2
	movgt	r2, r0
	cmp	r3, r2
	mov	r0, #1
	strgt	r3, [sp, #12]
	strgt	r2, [sp, #8]
	movgt	r3, r2
	cmp	r1, r3
	strgt	r1, [sp, #8]
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	strgt	r3, [sp, #4]
	bl	__printf_chk
	movt	r5, #:upper16:.LC2
	add	r4, sp, #4
	add	r6, sp, #24
.L19:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L19
	mov	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, pc}
.L7:
	mov	ip, r2
	str	r2, [sp, #16]
	str	r0, [sp, #12]
	mov	r2, r0
	mov	r0, ip
	b	.L8
.L11:
	mov	ip, r1
	mov	r1, r3
	stmib	sp, {r3, ip}
	mov	r3, ip
	b	.L14
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	9
	.word	1
	.word	3
	.word	7
	.word	2
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
