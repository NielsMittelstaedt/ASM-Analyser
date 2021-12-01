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
	.file	"other_binary_search.c"
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
	subs	r1, r1, #1
	bmi	.L6
	str	lr, [sp, #-4]!
	mov	r3, #0
	mov	lr, r0
.L5:
	sub	r0, r1, r3
	add	r0, r3, r0, asr #1
	ldr	ip, [lr, r0, lsl #2]
	cmp	ip, r2
	ldreq	pc, [sp], #4
	ble	.L3
	sub	r1, r0, #1
	cmp	r1, r3
	bge	.L5
.L7:
	mvn	r0, #0
	ldr	pc, [sp], #4
.L3:
	add	r3, r0, #1
	cmp	r3, r1
	ble	.L5
	b	.L7
.L6:
	mvn	r0, #0
	bx	lr
	.size	binarySearch, .-binarySearch
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"The number %d doesnt exist in array\012\000"
	.align	2
.LC2:
	.ascii	"The number %d exist in array at position \000"
	.align	2
.LC3:
	.ascii	": %d \012\000"
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
	push	{r4, r5, lr}
	movw	r4, #:lower16:.LANCHOR0
	movt	r4, #:upper16:.LANCHOR0
	sub	sp, sp, #28
	add	r5, sp, #4
	mov	ip, #0
	ldmia	r4!, {r0, r1, r2, r3}
	mov	lr, #4
	ldr	r4, [r4]
	stmia	r5!, {r0, r1, r2, r3}
	str	r4, [r5]
.L18:
	sub	r4, lr, ip
	add	r3, sp, #24
	add	r4, ip, r4, asr #1
	add	r3, r3, r4, lsl #2
	ldr	r2, [r3, #-20]
	cmp	r2, #5
	beq	.L14
	ble	.L15
	sub	lr, r4, #1
	cmp	lr, ip
	bge	.L18
.L17:
	movw	r1, #:lower16:.LC1
	mov	r2, #5
	movt	r1, #:upper16:.LC1
	mov	r0, #1
	bl	__printf_chk
	b	.L20
.L15:
	add	ip, r4, #1
	cmp	ip, lr
	ble	.L18
	b	.L17
.L14:
	movw	r1, #:lower16:.LC2
	mov	r0, #1
	movt	r1, #:upper16:.LC2
	bl	__printf_chk
	movw	r1, #:lower16:.LC3
	mov	r2, r4
	movt	r1, #:upper16:.LC3
	mov	r0, #1
	bl	__printf_chk
.L20:
	mov	r0, #0
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	5
	.word	8
	.word	10
	.word	14
	.word	16
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
