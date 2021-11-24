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
	.file	"random_quick_sort.c"
	.text
	.align	2
	.global	getBig
	.syntax unified
	.arm
	.fpu softvfp
	.type	getBig, %function
getBig:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, r2
	bgt	.L2
	add	ip, r0, r1, lsl #2
	mov	r0, r1
.L4:
	ldr	r1, [ip], #4
	cmp	r1, r3
	bxgt	lr
	add	r0, r0, #1
	cmp	r2, r0
	bge	.L4
.L2:
	add	r0, r2, #1
	bx	lr
	.size	getBig, .-getBig
	.align	2
	.global	getSmall
	.syntax unified
	.arm
	.fpu softvfp
	.type	getSmall, %function
getSmall:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, r2
	blt	.L10
	add	ip, r0, r1, lsl #2
	mov	r0, r1
.L9:
	ldr	r1, [ip], #-4
	cmp	r1, r3
	bxlt	lr
	sub	r0, r0, #1
	cmp	r2, r0
	ble	.L9
.L10:
	mvn	r0, #0
	bx	lr
	.size	getSmall, .-getSmall
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
	.global	__aeabi_idivmod
	.align	2
	.global	random_quick
	.syntax unified
	.arm
	.fpu softvfp
	.type	random_quick, %function
random_quick:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, r2
	bxge	lr
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	add	r6, r0, r2, lsl #2
	mov	r5, r1
	mov	r4, r2
	mov	r7, r0
.L15:
	bl	rand
	sub	r1, r4, r5
	bl	__aeabi_idivmod
	add	r3, r7, r5, lsl #2
	mov	ip, r5
	add	r8, r1, r5
	ldr	r1, [r7, r8, lsl #2]
.L17:
	ldr	r2, [r3], #4
	cmp	r1, r2
	blt	.L16
	add	ip, ip, #1
	cmp	r4, ip
	bge	.L17
	add	ip, r4, #1
.L16:
	mov	r2, r6
	mov	r3, r4
.L21:
	ldr	r0, [r2], #-4
	lsl	r9, r3, #2
	cmp	r1, r0
	bgt	.L26
	sub	r3, r3, #1
	cmp	r3, r5
	bge	.L21
.L31:
	mvn	r9, #3
	mvn	r3, #0
.L26:
	cmp	r3, ip
	blt	.L44
.L19:
	ldr	r9, [r7, ip, lsl #2]
	cmp	r4, ip
	ldr	r10, [r7, r3, lsl #2]
	lsl	r0, r3, #2
	add	lr, r7, r0
	add	r2, r7, ip, lsl #2
	str	r10, [r7, ip, lsl #2]
	str	r9, [r7, r3, lsl #2]
	bge	.L25
	b	.L23
.L45:
	add	ip, ip, #1
	cmp	r4, ip
	blt	.L23
.L25:
	ldr	r9, [r2], #4
	cmp	r1, r9
	bge	.L45
.L24:
	cmp	r3, r5
	bge	.L27
	b	.L31
.L46:
	sub	r3, r3, #1
	cmp	r3, r5
	lsl	r0, r3, #2
	blt	.L31
.L27:
	ldr	r2, [lr], #-4
	mov	r9, r0
	cmp	r1, r2
	ble	.L46
	cmp	r3, ip
	bge	.L19
.L44:
	cmp	ip, r3
	movge	r2, ip
	movlt	r2, r3
	cmp	r8, r2
	bgt	.L47
	cmp	ip, r3
	movge	ip, r3
	cmp	r8, ip
	bge	.L30
	ldr	ip, [r7, r9]
	mov	r1, r5
	ldr	lr, [r7, r8, lsl #2]
	add	r5, r3, #1
	sub	r2, r3, #1
	mov	r0, r7
	str	lr, [r7, r9]
	str	ip, [r7, r8, lsl #2]
	bl	random_quick
	cmp	r4, r5
	bgt	.L15
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L23:
	add	ip, r4, #1
	b	.L24
.L47:
	ldr	r3, [r7, ip, lsl #2]
	mov	r1, r5
	ldr	lr, [r7, r8, lsl #2]
	add	r5, ip, #1
	sub	r2, ip, #1
	mov	r0, r7
	str	lr, [r7, ip, lsl #2]
	str	r3, [r7, r8, lsl #2]
	bl	random_quick
	cmp	r4, r5
	bgt	.L15
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L30:
	mov	r1, r5
	sub	r2, r8, #1
	add	r5, r8, #1
	mov	r0, r7
	bl	random_quick
	cmp	r4, r5
	bgt	.L15
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	random_quick, .-random_quick
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
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
	push	{r4, r5, r6, r7, r8, lr}
	mov	r0, #0
	bl	time
	movw	r6, #:lower16:.LC0
	bl	srand
	mov	r0, #24
	bl	malloc
	mov	r2, #5
	mov	r3, #6
	mov	r1, #0
	movt	r6, #:upper16:.LC0
	str	r3, [r0]
	mov	r3, #4
	str	r2, [r0, #4]
	mov	r5, r0
	str	r3, [r0, #8]
	mov	r3, #3
	str	r3, [r0, #12]
	mov	r3, #2
	str	r3, [r0, #16]
	mov	r3, #1
	str	r3, [r0, #20]
	sub	r4, r5, #4
	bl	random_quick
	add	r7, r5, #20
.L49:
	ldr	r2, [r4, #4]!
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r7, r4
	bne	.L49
	mov	r0, r5
	bl	free
	mov	r0, #10
	bl	putchar
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
