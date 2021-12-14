0 	.arch armv7-a
0 	.eabi_attribute 20, 1
0 	.eabi_attribute 21, 1
0 	.eabi_attribute 23, 3
0 	.eabi_attribute 24, 1
0 	.eabi_attribute 25, 1
0 	.eabi_attribute 26, 2
0 	.eabi_attribute 30, 2
0 	.eabi_attribute 34, 1
0 	.eabi_attribute 18, 4
0 	.file	"binary_search.c"
0 	.text
0 	.align	2
0 	.global	binarySearch
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	binarySearch, %function
0 binarySearch:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 0, uses_anonymous_args = 0
0 	cmp	r1, r2
0 	str	lr, [sp, #-4]!
0 	mov	lr, r0
0 	bgt	.L8
0 .L2:
0 	sub	r0, r2, r1
0 	add	r0, r1, r0, asr #1
0 	ldr	ip, [lr, r0, lsl #2]
0 	cmp	ip, r3
0 	ldreq	pc, [sp], #4
0 	ble	.L4
0 	sub	r2, r0, #1
0 	cmp	r2, r1
0 	bge	.L2
0 .L8:
0 	mvn	r0, #0
0 	ldr	pc, [sp], #4
0 .L4:
0 	add	r1, r0, #1
0 	cmp	r1, r2
0 	ble	.L2
0 	b	.L8
0 	.size	binarySearch, .-binarySearch
0 	.section	.rodata.str1.4,"aMS",%progbits,1
0 	.align	2
0 .LC1:
0 	.ascii	"Ergebnis: %d\012\000"
0 	.section	.text.startup,"ax",%progbits
0 	.align	2
0 	.global	main
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	main, %function
0 main:
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 0, uses_anonymous_args = 0
1 	push	{r4, r5, lr}
1 	movw	r4, #:lower16:.LANCHOR0
1 	movt	r4, #:upper16:.LANCHOR0
1 	sub	sp, sp, #28
1 	add	r5, sp, #4
1 	mov	ip, #0
1 	ldmia	r4!, {r0, r1, r2, r3}
1 	mov	lr, #4
1 	ldr	r4, [r4]
1 	stmia	r5!, {r0, r1, r2, r3}
1 	str	r4, [r5]
0 .L11:
3 	sub	r2, lr, ip
3 	add	r3, sp, #24
3 	add	r2, ip, r2, asr #1
3 	add	r3, r3, r2, lsl #2
3 	ldr	r3, [r3, #-20]
3 	cmp	r3, #40
3 	beq	.L12
2 	ble	.L13
0 	sub	lr, r2, #1
0 	cmp	lr, ip
0 	bge	.L11
0 .L19:
0 	mvn	r2, #0
0 .L12:
1 	movw	r1, #:lower16:.LC1
1 	mov	r0, #1
1 	movt	r1, #:upper16:.LC1
1 	bl	__printf_chk
1 	mov	r0, #0
1 	add	sp, sp, #28
0 	@ sp needed
1 	pop	{r4, r5, pc}
0 .L13:
2 	add	ip, r2, #1
2 	cmp	ip, lr
2 	ble	.L11
0 	b	.L19
