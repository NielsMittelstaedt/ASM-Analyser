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
	.file	"odd_even_sort.c"
	.text
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
	.global	oddEvenSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	oddEvenSort, %function
oddEvenSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	add	r2, r0, #4
	sub	lr, r1, #1
	sub	r6, r0, #8
	sub	r5, r0, #4
	mov	r3, #0
	mov	r4, #1
.L4:
	cmp	lr, r3
	ble	.L23
.L5:
	ldr	r1, [r0, r3, lsl #2]
	ldr	ip, [r2, r3, lsl #2]
	add	r3, r3, #2
	cmp	r1, ip
	ble	.L4
	cmp	lr, r3
	str	ip, [r6, r3, lsl #2]
	mov	r4, #0
	str	r1, [r5, r3, lsl #2]
	bgt	.L5
	cmp	lr, #1
	ble	.L12
.L6:
	mov	r3, #1
.L11:
	ldr	r1, [r0, r3, lsl #2]
	ldr	ip, [r2, r3, lsl #2]
	cmp	r1, ip
	strgt	ip, [r0, r3, lsl #2]
	strgt	r1, [r2, r3, lsl #2]
	add	r3, r3, #2
	movgt	r4, #0
	cmp	lr, r3
	bgt	.L11
	cmp	r4, #0
	popne	{r4, r5, r6, pc}
.L12:
	cmp	lr, #0
	mov	r4, #1
	mov	r3, #0
	bgt	.L5
	pop	{r4, r5, r6, pc}
.L23:
	cmp	lr, #1
	bgt	.L6
	cmp	r4, #0
	beq	.L12
	pop	{r4, r5, r6, pc}
	.size	oddEvenSort, .-oddEvenSort
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC4:
	.ascii	"../test_files/c_in/odd_even_sort.c\000"
	.align	2
.LC5:
	.ascii	"arr1[i] == arr1Soln[i]\000"
	.align	2
.LC6:
	.ascii	"arr2[i] == arr2Soln[i]\000"
	.align	2
.LC7:
	.ascii	"All tests have passed!\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR0
	movt	ip, #:upper16:.LANCHOR0
	push	{r4, r5, r6, r7, lr}
	sub	sp, sp, #116
	ldm	ip, {r0, r1, r2, r3}
	add	lr, ip, #16
	mov	r6, sp
	add	r5, ip, #32
	add	r7, sp, #16
	add	r4, sp, #32
	add	ip, ip, #72
	stm	r6, {r0, r1, r2, r3}
	ldm	lr, {r0, r1, r2, r3}
	add	lr, sp, #72
	stm	r7, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldm	r5, {r0, r1}
	stm	r4, {r0, r1}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldm	ip, {r0, r1}
	stm	lr, {r0, r1}
	mov	r0, r6
	mov	r1, #4
	bl	oddEvenSort
	add	r0, sp, #32
	mov	r1, #10
	bl	oddEvenSort
	ldr	r2, [sp]
	ldr	r3, [sp, #16]
	cmp	r2, r3
	bne	.L25
	ldr	r2, [sp, #4]
	ldr	r3, [sp, #20]
	cmp	r2, r3
	bne	.L25
	ldr	r2, [sp, #8]
	ldr	r3, [sp, #24]
	cmp	r2, r3
	bne	.L25
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #28]
	cmp	r2, r3
	bne	.L25
	ldr	r2, [sp, #32]
	ldr	r3, [sp, #72]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #36]
	ldr	r3, [sp, #76]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #40]
	ldr	r3, [sp, #80]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #44]
	ldr	r3, [sp, #84]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #48]
	ldr	r3, [sp, #88]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #52]
	ldr	r3, [sp, #92]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #56]
	ldr	r3, [sp, #96]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #60]
	ldr	r3, [sp, #100]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #64]
	ldr	r3, [sp, #104]
	cmp	r2, r3
	bne	.L27
	ldr	r2, [sp, #68]
	ldr	r3, [sp, #108]
	cmp	r2, r3
	bne	.L27
	movw	r0, #:lower16:.LC7
	movt	r0, #:upper16:.LC7
	bl	puts
	mov	r0, #0
	add	sp, sp, #116
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L27:
	movw	r1, #:lower16:.LC4
	movw	r0, #:lower16:.LC6
	ldr	r3, .L30
	movt	r1, #:upper16:.LC4
	movt	r0, #:upper16:.LC6
	mov	r2, #107
	bl	__assert_fail
.L25:
	movw	r1, #:lower16:.LC4
	movw	r0, #:lower16:.LC5
	ldr	r3, .L30
	movt	r1, #:upper16:.LC4
	movt	r0, #:upper16:.LC5
	mov	r2, #102
	bl	__assert_fail
.L31:
	.align	2
.L30:
	.word	.LANCHOR0+112
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	-9
	.word	2
	.word	3
	.word	1
.LC1:
	.word	-9
	.word	1
	.word	2
	.word	3
.LC2:
	.word	9
	.word	7
	.word	5
	.word	3
	.word	8
	.word	2
	.word	1
	.word	4
	.word	0
	.word	6
.LC3:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.type	__PRETTY_FUNCTION__.5675, %object
	.size	__PRETTY_FUNCTION__.5675, 5
__PRETTY_FUNCTION__.5675:
	.ascii	"test\000"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
