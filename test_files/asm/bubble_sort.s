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
	.file	"bubble_sort.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
	.text
	.align	2
	.global	display
	.syntax unified
	.arm
	.fpu softvfp
	.type	display, %function
display:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r5, r1, #0
	ble	.L2
	movw	r6, #:lower16:.LC0
	add	r5, r0, r5, lsl #2
	movt	r6, #:upper16:.LC0
	mov	r4, r0
.L3:
	ldr	r2, [r4], #4
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L3
.L2:
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	display, .-display
	.align	2
	.global	swap
	.syntax unified
	.arm
	.fpu softvfp
	.type	swap, %function
swap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, [r0]
	ldr	r2, [r1]
	str	r2, [r0]
	str	r3, [r1]
	bx	lr
	.size	swap, .-swap
	.align	2
	.global	bubbleSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	bubbleSort, %function
bubbleSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	sub	r6, r1, #1
	cmp	r6, #0
	pople	{r4, r5, r6, pc}
	mov	r5, #0
	mov	lr, r6
	mov	r2, r5
	mov	r4, r5
.L9:
	lsl	r3, r2, #2
	ldr	r1, [r0, r2, lsl #2]
	add	r3, r3, #4
	ldr	ip, [r0, r3]
	cmp	r1, ip
	ble	.L10
	str	ip, [r0, r2, lsl #2]
	add	r2, r2, #1
	cmp	lr, r2
	mov	r4, #1
	str	r1, [r0, r3]
	bgt	.L9
.L12:
	add	r5, r5, #1
	mov	r2, #0
	cmp	r5, r6
	sub	lr, r6, r5
	mov	r4, r2
	popge	{r4, r5, r6, pc}
	cmp	lr, r2
	bgt	.L9
	pop	{r4, r5, r6, pc}
.L10:
	add	r2, r2, #1
	cmp	r2, lr
	blt	.L9
	cmp	r4, #0
	bne	.L12
	pop	{r4, r5, r6, pc}
	.size	bubbleSort, .-bubbleSort
	.section	.rodata.str1.4
	.align	2
.LC1:
	.ascii	"%d\012\000"
	.text
	.align	2
	.global	test
	.syntax unified
	.arm
	.fpu softvfp
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r1, #4
	mov	r0, #10
	movw	r7, #34079
	bl	calloc
	movt	r7, 20971
	mov	r8, #100
	sub	r5, r0, #4
	add	r6, r0, #36
	mov	r4, r0
	mov	r9, r5
.L22:
	bl	rand
	smull	r3, r2, r7, r0
	asr	r3, r0, #31
	rsb	r3, r3, r2, asr #5
	mls	r0, r8, r3, r0
	str	r0, [r9, #4]!
	cmp	r9, r6
	bne	.L22
	mov	r3, #9
.L23:
	ldm	r4, {r1, r2}
	cmp	r1, r2
	ble	.L27
.L89:
	cmp	r3, #1
	str	r2, [r4]
	str	r1, [r4, #4]
	beq	.L28
	mov	r2, r1
	ldr	r1, [r4, #8]
	mov	r0, #1
	cmp	r2, r1
	ble	.L29
.L90:
	cmp	r3, #2
	stmib	r4, {r1, r2}
	movne	r0, #1
	movne	r1, r2
	beq	.L31
.L30:
	ldr	r2, [r4, #12]
	cmp	r1, r2
	ble	.L32
	cmp	r3, #3
	str	r2, [r4, #8]
	str	r1, [r4, #12]
	movne	r2, r1
	movne	r0, #1
	beq	.L31
	ldr	r1, [r4, #16]
	cmp	r2, r1
	ble	.L34
.L91:
	cmp	r3, #4
	str	r1, [r4, #12]
	str	r2, [r4, #16]
	movne	r1, r2
	movne	r0, #1
	beq	.L31
	ldr	r2, [r4, #20]
	cmp	r1, r2
	ble	.L36
.L92:
	cmp	r3, #5
	str	r2, [r4, #16]
	str	r1, [r4, #20]
	movne	r2, r1
	movne	r0, #1
	beq	.L31
	ldr	r1, [r4, #24]
	cmp	r2, r1
	ble	.L38
.L93:
	cmp	r3, #6
	str	r1, [r4, #20]
	str	r2, [r4, #24]
	movne	r1, r2
	movne	r0, #1
	beq	.L31
	ldr	r2, [r4, #28]
	cmp	r1, r2
	ble	.L40
.L94:
	cmp	r3, #7
	str	r2, [r4, #24]
	str	r1, [r4, #28]
	movne	r2, r1
	movne	r0, #1
	beq	.L31
	ldr	r1, [r4, #32]
	cmp	r2, r1
	ble	.L42
.L95:
	cmp	r3, #9
	str	r1, [r4, #28]
	str	r2, [r4, #32]
	bne	.L28
	ldr	ip, [r4, #36]
	cmp	ip, r2
	bge	.L25
	mov	r1, r2
.L43:
	str	ip, [r4, #32]
	str	r1, [r6]
.L25:
	ldm	r4, {r1, r2}
	mov	r3, #8
	cmp	r1, r2
	bgt	.L89
.L27:
	cmp	r3, #1
	beq	.L26
	ldr	r1, [r4, #8]
	mov	r0, #0
	cmp	r2, r1
	bgt	.L90
.L29:
	cmp	r3, #2
	bne	.L30
.L24:
	cmp	r0, #0
	beq	.L26
.L31:
	sub	r3, r3, #1
	b	.L23
.L28:
	subs	r3, r3, #1
	bne	.L23
.L26:
	movw	r7, #:lower16:.LC1
	movt	r7, #:upper16:.LC1
.L45:
	ldr	r2, [r5, #4]!
	mov	r1, r7
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r6
	bne	.L45
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, r9, r10, lr}
	b	free
.L32:
	cmp	r3, #3
	beq	.L24
	ldr	r1, [r4, #16]
	cmp	r2, r1
	bgt	.L91
.L34:
	cmp	r3, #4
	beq	.L24
	ldr	r2, [r4, #20]
	cmp	r1, r2
	bgt	.L92
.L36:
	cmp	r3, #5
	beq	.L24
	ldr	r1, [r4, #24]
	cmp	r2, r1
	bgt	.L93
.L38:
	cmp	r3, #6
	beq	.L24
	ldr	r2, [r4, #28]
	cmp	r1, r2
	bgt	.L94
.L40:
	cmp	r3, #7
	beq	.L24
	ldr	r1, [r4, #32]
	cmp	r2, r1
	bgt	.L95
.L42:
	cmp	r3, #9
	bne	.L24
	ldr	ip, [r4, #36]
	cmp	ip, r1
	blt	.L43
	cmp	r0, #0
	bne	.L31
	b	.L26
	.size	test, .-test
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
	push	{r4, lr}
	mov	r0, #0
	bl	time
	bl	srand
	bl	test
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
