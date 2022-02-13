1.00 0 	.arch armv7-a
1.00 0 	.eabi_attribute 20, 1
1.00 0 	.eabi_attribute 21, 1
1.00 0 	.eabi_attribute 23, 3
1.00 0 	.eabi_attribute 24, 1
1.00 0 	.eabi_attribute 25, 1
1.00 0 	.eabi_attribute 26, 2
1.00 0 	.eabi_attribute 30, 2
1.00 0 	.eabi_attribute 34, 1
1.00 0 	.eabi_attribute 18, 4
1.00 0 	.file	"binary_search.c"
1.00 0 	.text
1.00 0 	.align	2
1.00 0 	.global	binarySearch
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	binarySearch, %function
1.00 0 binarySearch:
1.00 0 	@ args = 0, pretend = 0, frame = 0
1.00 0 	@ frame_needed = 0, uses_anonymous_args = 0
1.00 0 	cmp	r1, r2
1.00 0 	bgt	.L13
1.00 0 	str	lr, [sp, #-4]!
1.00 0 	mov	lr, r0
1.00 0 .L2:
1.00 0 	sub	r0, r2, r1
1.00 0 	add	r0, r1, r0, asr #1
1.00 0 	ldr	ip, [lr, r0, lsl #2]
1.00 0 	cmp	ip, r3
1.00 0 	ldreq	pc, [sp], #4
1.00 0 	subgt	r2, r0, #1
1.00 0 	addle	r1, r0, #1
1.00 0 	cmp	r2, r1
1.00 0 	bge	.L2
1.00 0 	mvn	r0, #0
1.00 0 	ldr	pc, [sp], #4
1.00 0 .L13:
1.00 0 	mvn	r0, #0
1.00 0 	bx	lr
1.00 0 	.size	binarySearch, .-binarySearch
1.00 0 	.section	.rodata.str1.4,"aMS",%progbits,1
1.00 0 	.align	2
1.00 0 .LC1:
1.00 0 	.ascii	"Result: %d\012\000"
1.00 0 	.section	.text.startup,"ax",%progbits
1.00 0 	.align	2
1.00 0 	.global	main
1.00 0 	.syntax unified
1.00 0 	.arm
1.00 0 	.fpu softvfp
1.00 0 	.type	main, %function
1.00 0 main:
1.00 0 	@ args = 0, pretend = 0, frame = 24
1.00 0 	@ frame_needed = 0, uses_anonymous_args = 0
1.00 1 	push	{r4, r5, lr}
1.00 1 	movw	r4, #:lower16:.LANCHOR0
1.00 1 	movt	r4, #:upper16:.LANCHOR0
1.00 1 	sub	sp, sp, #28
1.00 1 	add	r5, sp, #4
1.00 1 	mov	ip, #0
1.00 1 	ldmia	r4!, {r0, r1, r2, r3}
1.00 1 	mov	lr, #5
1.00 1 	ldr	r4, [r4]
1.00 1 	stmia	r5!, {r0, r1, r2, r3}
1.00 1 	str	r4, [r5]
1.00 0 .L15:
1.00 2 	sub	r2, lr, ip
1.00 2 	add	r3, sp, #24
1.00 2 	add	r2, ip, r2, asr #1
1.00 2 	add	r3, r3, r2, lsl #2
1.00 2 	ldr	r3, [r3, #-20]
1.00 2 	cmp	r3, #40
0.50 2 	beq	.L16
1.00 1 	subgt	lr, r2, #1
1.00 1 	addle	ip, r2, #1
1.00 1 	cmp	ip, lr
0.00 1 	ble	.L15
1.00 0 	mvn	r2, #0
1.00 0 .L16:
1.00 1 	movw	r1, #:lower16:.LC1
1.00 1 	mov	r0, #1
1.00 1 	movt	r1, #:upper16:.LC1
1.00 1 	bl	__printf_chk
1.00 1 	mov	r0, #0
1.00 1 	add	sp, sp, #28
1.00 0 	@ sp needed
1.00 1 	pop	{r4, r5, pc}
1.00 0 	.size	main, .-main
1.00 0 	.section	.rodata
1.00 0 	.align	2
1.00 0 	.set	.LANCHOR0,. + 0
1.00 0 .LC0:
1.00 0 	.word	2
1.00 0 	.word	3
1.00 0 	.word	4
1.00 0 	.word	10
1.00 0 	.word	40
1.00 0 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
1.00 0 	.section	.note.GNU-stack,"",%progbits
