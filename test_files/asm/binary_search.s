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
	.file	"binary_search.c"
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
	cmp	r1, r2
	str	lr, [sp, #-4]!
	mov	lr, r0
	bgt	.L8
.L2:
	sub	r0, r2, r1
	add	r0, r1, r0, asr #1
	ldr	ip, [lr, r0, lsl #2]
	cmp	ip, r3
	ldreq	pc, [sp], #4
	ble	.L4
	sub	r2, r0, #1
	cmp	r2, r1
	bge	.L2
.L8:
	mvn	r0, #0
	ldr	pc, [sp], #4
.L4:
	add	r1, r0, #1
	cmp	r1, r2
	ble	.L2
	b	.L8
	.size	binarySearch, .-binarySearch
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"Result: %d\012\000"
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
	mov	lr, #5
	ldr	r4, [r4]
	stmia	r5!, {r0, r1, r2, r3}
	str	r4, [r5]
.L11:
	sub	r2, lr, ip
	add	r3, sp, #24
	add	r2, ip, r2, asr #1
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #-20]
	cmp	r3, #40
	beq	.L12
	ble	.L13
	sub	lr, r2, #1
	cmp	lr, ip
	bge	.L11
.L19:
	mvn	r2, #0
.L12:
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	bl	__printf_chk
	mov	r0, #0
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, pc}
.L13:
	add	ip, r2, #1
	cmp	ip, lr
	ble	.L11
	b	.L19
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	2
	.word	3
	.word	4
	.word	10
	.word	40
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
