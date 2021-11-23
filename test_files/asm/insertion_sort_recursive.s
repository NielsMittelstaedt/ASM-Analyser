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
	.file	"insertion_sort_recursive.c"
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	RecursionInsertionSort.part.0, %function
RecursionInsertionSort.part.0:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	subs	r5, r1, #1
	sub	r7, r1, #-1073741823
	mov	r6, r0
	ldreq	ip, [r0, r7, lsl #2]
	beq	.L3
	mov	r4, r1
	mov	r1, r5
	bl	RecursionInsertionSort.part.0
	cmp	r4, #1
	ldr	ip, [r6, r7, lsl #2]
	sub	r3, r4, #2
	beq	.L3
	add	r1, r6, r5, lsl #2
	b	.L4
.L5:
	cmn	r3, #1
	str	r2, [r1], #-4
	beq	.L3
.L4:
	ldr	r2, [r1, #-4]
	sub	r3, r3, #1
	cmp	ip, r2
	blt	.L5
	mov	r6, r1
.L3:
	str	ip, [r6]
	pop	{r4, r5, r6, r7, r8, pc}
	.size	RecursionInsertionSort.part.0, .-RecursionInsertionSort.part.0
	.align	2
	.global	RecursionInsertionSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	RecursionInsertionSort, %function
RecursionInsertionSort:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	subs	r4, r1, #0
	sub	sp, sp, #44
	ble	.L16
	sub	r2, r4, #-1073741823
	cmp	r4, #1
	mov	r8, r0
	lsl	fp, r2, #2
	ldreq	r2, [r0, r2, lsl #2]
	add	r3, r0, fp
	beq	.L40
	sub	r5, r4, #2
	cmp	r4, #2
	sub	r2, fp, #4
	add	r1, r0, r2
	mov	r6, r5
	str	r1, [sp, #4]
	beq	.L19
	cmp	r4, #3
	sub	r2, fp, #8
	sub	r7, r4, #3
	add	r1, r0, r2
	str	r7, [sp, #12]
	str	r1, [sp, #8]
	beq	.L20
	cmp	r4, #4
	sub	r2, fp, #12
	sub	r9, r4, #4
	add	r1, r0, r2
	str	r9, [sp, #20]
	str	r1, [sp, #16]
	beq	.L21
	cmp	r4, #5
	sub	r2, fp, #16
	sub	r10, r4, #5
	add	r1, r0, r2
	str	r10, [sp, #28]
	str	r1, [sp, #24]
	beq	.L22
	subs	r1, r4, #6
	sub	fp, fp, #20
	beq	.L23
	str	r3, [sp, #36]
	str	r1, [sp, #32]
	bl	RecursionInsertionSort.part.0
	ldr	r1, [sp, #32]
	ldr	r3, [sp, #36]
	add	r2, r8, r1, lsl #2
	ldr	fp, [r0, fp]
	sub	r0, r4, #7
	b	.L24
.L26:
	cmn	r0, #1
	str	ip, [r2]
	sub	r2, lr, #4
	beq	.L42
.L24:
	ldr	ip, [r2, #-4]
	sub	r0, r0, #1
	mov	lr, r2
	cmp	ip, fp
	bgt	.L26
.L25:
	ldr	r0, [sp, #24]
	ldr	r2, [sp, #28]
	str	fp, [lr]
	ldr	lr, [r0]
	add	r2, r8, r2, lsl #2
.L27:
	ldr	r0, [r2, #-4]
	sub	r1, r1, #1
	mov	ip, r2
	cmp	r0, lr
	ble	.L28
	cmn	r1, #1
	str	r0, [r2]
	sub	r2, ip, #4
	bne	.L27
	mov	ip, r8
	b	.L28
.L19:
	ldr	r0, [r0, r2]
	mov	r1, r8
.L37:
	sub	r4, r4, #1
	str	r0, [r1]
	ldr	r2, [r3]
	add	r4, r8, r4, lsl #2
	b	.L39
.L41:
	cmn	r5, #1
	str	r3, [r4], #-4
	beq	.L40
.L39:
	ldr	r3, [r4, #-4]
	sub	r5, r5, #1
	cmp	r3, r2
	bgt	.L41
	mov	r8, r4
.L40:
	str	r2, [r8]
.L16:
	add	sp, sp, #44
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L22:
	ldr	lr, [r0, r2]
	mov	ip, r0
.L28:
	ldr	r2, [sp, #20]
	ldr	r1, [sp, #16]
	str	lr, [ip]
	add	r2, r8, r2, lsl #2
	ldr	ip, [r1]
	b	.L30
.L32:
	cmn	r10, #1
	str	r1, [r2]
	sub	r2, r0, #4
	beq	.L44
.L30:
	ldr	r1, [r2, #-4]
	sub	r10, r10, #1
	mov	r0, r2
	cmp	r1, ip
	bgt	.L32
.L31:
	ldr	r2, [sp, #12]
	ldr	r1, [sp, #8]
	str	ip, [r0]
	add	r2, r8, r2, lsl #2
	ldr	ip, [r1]
	b	.L33
.L35:
	cmn	r9, #1
	str	r1, [r2]
	sub	r2, r0, #4
	beq	.L45
.L33:
	ldr	r1, [r2, #-4]
	sub	r9, r9, #1
	mov	r0, r2
	cmp	r1, ip
	bgt	.L35
.L34:
	ldr	r2, [sp, #4]
	add	r6, r8, r6, lsl #2
	str	ip, [r0]
	ldr	r0, [r2]
.L36:
	ldr	r2, [r6, #-4]
	sub	r7, r7, #1
	mov	r1, r6
	cmp	r2, r0
	ble	.L37
	cmn	r7, #1
	str	r2, [r6]
	sub	r6, r1, #4
	bne	.L36
	mov	r1, r8
	b	.L37
.L45:
	mov	r0, r8
	b	.L34
.L44:
	mov	r0, r8
	b	.L31
.L42:
	mov	lr, r8
	b	.L25
.L20:
	ldr	ip, [r0, r2]
	b	.L34
.L21:
	ldr	ip, [r0, r2]
	b	.L31
.L23:
	ldr	fp, [r0, fp]
	mov	lr, r0
	b	.L25
	.size	RecursionInsertionSort, .-RecursionInsertionSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	" %d\000"
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
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r0, #0
	bl	time
	movw	r4, #19923
	bl	srand
	movt	r4, 4194
	bl	rand
	mov	r3, #500
	mov	r1, #4
	smull	r2, r4, r4, r0
	asr	r2, r0, #31
	rsb	r4, r2, r4, asr #5
	mls	r4, r3, r4, r0
	mov	r0, r4
	bl	calloc
	cmp	r4, #0
	mov	r5, r0
	ble	.L63
	movw	r10, #34079
	add	r7, r0, r4, lsl #2
	movt	r10, 20971
	mov	r6, r0
	mov	r9, r0
	mov	r8, #100
.L60:
	bl	rand
	smull	r3, r2, r10, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r3, r8, r3, r0
	sub	r3, r3, #50
	str	r3, [r9], #4
	cmp	r9, r7
	bne	.L60
	mov	r1, r4
	mov	r0, r5
	bl	RecursionInsertionSort.part.0
	movw	r4, #:lower16:.LC0
	movt	r4, #:upper16:.LC0
.L62:
	ldr	r2, [r6], #4
	mov	r1, r4
	mov	r0, #1
	bl	__printf_chk
	cmp	r7, r6
	bne	.L62
.L63:
	mov	r0, #10
	bl	putchar
	mov	r0, r5
	bl	free
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
