0 	.arch armv7-a
0 	.eabi_attribute 20, 1
0 	.eabi_attribute 21, 1
0 	.eabi_attribute 23, 3
0 	.eabi_attribute 24, 1
0 	.eabi_attribute 25, 1
0 	.eabi_attribute 26, 2
0 	.eabi_attribute 30, 6
0 	.eabi_attribute 34, 1
0 	.eabi_attribute 18, 4
0 	.file	"simplex.c"
0 	.text
0 	.comm	SimplexTable,120,8
0 	.comm	TempState,40,8
0 	.align	2
0 	.global	main
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	main, %function
0 main:
0 	@ args = 0, pretend = 0, frame = 0
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	bl	Input
1 	bl	X2Calc
1 	bl	X1Calc
1 	bl	Result
1 	mov	r3, #0
1 	mov	r0, r3
1 	pop	{fp, pc}
0 	.size	main, .-main
0 	.global	__aeabi_ddiv
0 	.global	__aeabi_dcmplt
0 	.align	2
0 	.global	X2Calc
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	X2Calc, %function
0 X2Calc:
0 	@ args = 0, pretend = 0, frame = 56
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #56
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r0, [r3, #72]
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r2, [r3, #48]
1 	bl	__aeabi_ddiv
1 	mov	r2, r0
1 	mov	r3, r1
1 	strd	r2, [fp, #-20]
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r0, [r3, #112]
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r2, [r3, #88]
1 	bl	__aeabi_ddiv
1 	mov	r2, r0
1 	mov	r3, r1
1 	strd	r2, [fp, #-28]
1 	ldrd	r2, [fp, #-28]
1 	ldrd	r0, [fp, #-20]
1 	bl	__aeabi_dcmplt
1 	mov	r3, r0
1 	cmp	r3, #0
1 	beq	.L12
1 	mov	r3, #1
1 	str	r3, [fp, #-32]
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r2, [r3, #48]
1 	strd	r2, [fp, #-60]
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	b	.L6
0 .L7:
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-32]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-8]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r0, [r3]
5 	ldrd	r2, [fp, #-60]
5 	bl	__aeabi_ddiv
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r2
5 	mov	r1, r3
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	ip, [fp, #-32]
5 	mov	r3, ip
5 	lsl	r3, r3, #2
5 	add	r3, r3, ip
5 	ldr	ip, [fp, #-8]
5 	add	r3, r3, ip
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	strd	r0, [r3]
5 	ldr	r3, [fp, #-8]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-8]
0 .L6:
6 	ldr	r3, [fp, #-8]
6 	cmp	r3, #4
6 	ble	.L7
1 	mov	r0, #1
1 	bl	ShowTable
1 	mov	r3, #1
1 	str	r3, [fp, #-48]
1 	mov	r3, #1
1 	str	r3, [fp, #-52]
1 	ldr	r1, [fp, #-52]
1 	ldr	r0, [fp, #-48]
1 	bl	GaussCalc
1 	mov	r0, #2
1 	bl	ShowTable
1 	ldr	r1, [fp, #-52]
1 	ldr	r0, [fp, #-48]
1 	bl	Exchange
1 	ldr	r1, [fp, #-52]
1 	ldr	r0, [fp, #-48]
1 	bl	Maxim
1 	mov	r0, #3
1 	bl	ShowTable
1 	b	.L13
0 .L12:
0 	mov	r3, #2
0 	str	r3, [fp, #-32]
0 	movw	r3, #:lower16:SimplexTable
0 	movt	r3, #:upper16:SimplexTable
0 	ldrd	r2, [r3, #88]
0 	strd	r2, [fp, #-44]
0 	mov	r3, #0
0 	str	r3, [fp, #-8]
0 	b	.L9
0 .L10:
0 	movw	r2, #:lower16:SimplexTable
0 	movt	r2, #:upper16:SimplexTable
0 	ldr	r1, [fp, #-32]
0 	mov	r3, r1
0 	lsl	r3, r3, #2
0 	add	r3, r3, r1
0 	ldr	r1, [fp, #-8]
0 	add	r3, r3, r1
0 	lsl	r3, r3, #3
0 	add	r3, r2, r3
0 	ldrd	r0, [r3]
0 	ldrd	r2, [fp, #-44]
0 	bl	__aeabi_ddiv
0 	mov	r2, r0
0 	mov	r3, r1
0 	mov	r0, r2
0 	mov	r1, r3
0 	movw	r2, #:lower16:SimplexTable
0 	movt	r2, #:upper16:SimplexTable
0 	ldr	ip, [fp, #-32]
0 	mov	r3, ip
0 	lsl	r3, r3, #2
0 	add	r3, r3, ip
0 	ldr	ip, [fp, #-8]
0 	add	r3, r3, ip
0 	lsl	r3, r3, #3
0 	add	r3, r2, r3
0 	strd	r0, [r3]
0 	ldr	r3, [fp, #-8]
0 	add	r3, r3, #1
0 	str	r3, [fp, #-8]
0 .L9:
0 	ldr	r3, [fp, #-8]
0 	cmp	r3, #4
0 	ble	.L10
0 	mov	r0, #1
0 	bl	ShowTable
0 	mov	r3, #2
0 	str	r3, [fp, #-48]
0 	mov	r3, #1
0 	str	r3, [fp, #-52]
0 	ldr	r1, [fp, #-52]
0 	ldr	r0, [fp, #-48]
0 	bl	GaussCalc
0 	mov	r0, #2
0 	bl	ShowTable
0 	ldr	r1, [fp, #-52]
0 	ldr	r0, [fp, #-48]
0 	bl	Exchange
0 	ldr	r1, [fp, #-52]
0 	ldr	r0, [fp, #-48]
0 	bl	Maxim
0 	mov	r0, #3
0 	bl	ShowTable
0 .L13:
1 	nop
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
0 	.size	X2Calc, .-X2Calc
0 	.align	2
0 	.global	X1Calc
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	X1Calc, %function
0 X1Calc:
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #24
1 	mov	r3, #2
1 	str	r3, [fp, #-12]
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r2, [r3, #80]
1 	strd	r2, [fp, #-20]
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	b	.L15
0 .L16:
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-12]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-8]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r0, [r3]
5 	ldrd	r2, [fp, #-20]
5 	bl	__aeabi_ddiv
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r2
5 	mov	r1, r3
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	ip, [fp, #-12]
5 	mov	r3, ip
5 	lsl	r3, r3, #2
5 	add	r3, r3, ip
5 	ldr	ip, [fp, #-8]
5 	add	r3, r3, ip
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	strd	r0, [r3]
5 	ldr	r3, [fp, #-8]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-8]
0 .L15:
6 	ldr	r3, [fp, #-8]
6 	cmp	r3, #4
6 	ble	.L16
1 	mov	r0, #4
1 	bl	ShowTable
1 	mov	r3, #2
1 	str	r3, [fp, #-24]
1 	mov	r3, #0
1 	str	r3, [fp, #-28]
1 	ldr	r1, [fp, #-28]
1 	ldr	r0, [fp, #-24]
1 	bl	GaussCalc
1 	mov	r0, #5
1 	bl	ShowTable
1 	ldr	r1, [fp, #-28]
1 	ldr	r0, [fp, #-24]
1 	bl	Exchange
1 	ldr	r1, [fp, #-28]
1 	ldr	r0, [fp, #-24]
1 	bl	Maxim
1 	mov	r0, #6
1 	bl	ShowTable
1 	nop
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
0 	.size	X1Calc, .-X1Calc
0 	.global	__aeabi_dcmpeq
0 	.section	.rodata
0 	.align	2
0 .LC1:
0 	.ascii	"\012***** Result *****\000"
0 	.align	2
0 .LC2:
0 	.ascii	"x1 = %lf, \000"
0 	.align	2
0 .LC3:
0 	.ascii	"x2 = %lf, \000"
0 	.align	2
0 .LC4:
0 	.ascii	"f = %lf\012\000"
0 	.text
0 	.align	2
0 	.global	Result
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	Result, %function
0 Result:
0 	@ args = 0, pretend = 0, frame = 40
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #40
1 	mov	r3, #0
1 	str	r3, [fp, #-16]
1 	mov	r3, #1
1 	str	r3, [fp, #-8]
1 	b	.L18
0 .L23:
2 	mov	r3, #0
2 	str	r3, [fp, #-12]
2 	b	.L19
0 .L22:
10 	movw	r2, #:lower16:SimplexTable
10 	movt	r2, #:upper16:SimplexTable
10 	ldr	r1, [fp, #-8]
10 	mov	r3, r1
10 	lsl	r3, r3, #2
10 	add	r3, r3, r1
10 	ldr	r1, [fp, #-12]
10 	add	r3, r3, r1
10 	lsl	r3, r3, #3
10 	add	r3, r2, r3
10 	ldrd	r0, [r3]
10 	mov	r2, #0
10 	mov	r3, #0
10 	movt	r3, 16368
10 	bl	__aeabi_dcmpeq
10 	mov	r3, r0
10 	cmp	r3, #0
10 	beq	.L20
2 	movw	r3, #:lower16:SimplexTable
2 	movt	r3, #:upper16:SimplexTable
2 	ldr	r2, [fp, #-8]
2 	mov	r1, #40
2 	mul	r2, r1, r2
2 	add	r3, r3, r2
2 	add	r3, r3, #32
2 	ldrd	r2, [r3]
2 	ldr	r1, [fp, #-16]
2 	lsl	r1, r1, #3
2 	sub	r0, fp, #4
2 	add	r1, r0, r1
2 	sub	r1, r1, #40
2 	strd	r2, [r1]
2 	ldr	r3, [fp, #-16]
2 	add	r3, r3, #1
2 	str	r3, [fp, #-16]
0 .L20:
10 	ldr	r3, [fp, #-12]
10 	add	r3, r3, #1
10 	str	r3, [fp, #-12]
0 .L19:
12 	ldr	r3, [fp, #-12]
12 	cmp	r3, #4
12 	ble	.L22
2 	ldr	r3, [fp, #-8]
2 	add	r3, r3, #1
2 	str	r3, [fp, #-8]
0 .L18:
3 	ldr	r3, [fp, #-8]
3 	cmp	r3, #2
3 	ble	.L23
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r2, [r3, #32]
1 	ldr	r1, [fp, #-16]
1 	lsl	r1, r1, #3
1 	sub	r0, fp, #4
1 	add	r1, r0, r1
1 	sub	r1, r1, #40
1 	strd	r2, [r1]
1 	movw	r0, #:lower16:.LC1
1 	movt	r0, #:upper16:.LC1
1 	bl	puts
1 	ldrd	r2, [fp, #-44]
1 	movw	r0, #:lower16:.LC2
1 	movt	r0, #:upper16:.LC2
1 	bl	printf
1 	ldrd	r2, [fp, #-36]
1 	movw	r0, #:lower16:.LC3
1 	movt	r0, #:upper16:.LC3
1 	bl	printf
1 	ldrd	r2, [fp, #-28]
1 	movw	r0, #:lower16:.LC4
1 	movt	r0, #:upper16:.LC4
1 	bl	printf
1 	nop
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
0 	.size	Result, .-Result
0 	.global	__aeabi_dmul
0 	.global	__aeabi_dadd
0 	.align	2
0 	.global	Maxim
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	Maxim, %function
0 Maxim:
0 	@ args = 0, pretend = 0, frame = 56
0 	@ frame_needed = 1, uses_anonymous_args = 0
2 	push	{fp, lr}
2 	add	fp, sp, #4
2 	sub	sp, sp, #56
2 	str	r0, [fp, #-56]
2 	str	r1, [fp, #-60]
2 	movw	r3, #:lower16:SimplexTable
2 	movt	r3, #:upper16:SimplexTable
2 	ldr	r2, [fp, #-60]
2 	lsl	r2, r2, #3
2 	add	r3, r3, r2
2 	ldrd	r2, [r3]
2 	strd	r2, [fp, #-20]
2 	movw	r3, #:lower16:SimplexTable
2 	movt	r3, #:upper16:SimplexTable
2 	ldrd	r2, [r3, #32]
2 	strd	r2, [fp, #-28]
2 	ldr	r3, [fp, #-56]
2 	cmp	r3, #1
2 	bne	.L26
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r2, [r3]
1 	strd	r2, [fp, #-52]
1 	mov	r3, #1
1 	str	r3, [fp, #-40]
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	b	.L27
0 .L28:
5 	movw	r3, #:lower16:TempState
5 	movt	r3, #:upper16:TempState
5 	ldr	r2, [fp, #-8]
5 	lsl	r2, r2, #3
5 	add	r3, r3, r2
5 	ldrd	r0, [r3]
5 	ldrd	r2, [fp, #-20]
5 	bl	__aeabi_dmul
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r2
5 	mov	r1, r3
5 	movw	r3, #:lower16:SimplexTable
5 	movt	r3, #:upper16:SimplexTable
5 	ldr	r2, [fp, #-8]
5 	lsl	r2, r2, #3
5 	add	r3, r3, r2
5 	strd	r0, [r3]
5 	ldr	r3, [fp, #-8]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-8]
0 .L27:
6 	ldr	r3, [fp, #-8]
6 	cmp	r3, #4
6 	ble	.L28
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r0, [r3]
1 	ldrd	r2, [fp, #-52]
1 	bl	__aeabi_dadd
1 	mov	r2, r0
1 	mov	r3, r1
1 	mov	r0, r2
1 	mov	r1, r3
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	strd	r0, [r3]
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldr	r2, [fp, #-60]
1 	lsl	r2, r2, #3
1 	add	r1, r3, r2
1 	mov	r2, #0
1 	mov	r3, #0
1 	strd	r2, [r1]
1 	b	.L29
0 .L26:
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r2, [r3, #16]
1 	strd	r2, [fp, #-36]
1 	mov	r3, #2
1 	str	r3, [fp, #-40]
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	b	.L30
0 .L31:
5 	movw	r3, #:lower16:TempState
5 	movt	r3, #:upper16:TempState
5 	ldr	r2, [fp, #-8]
5 	lsl	r2, r2, #3
5 	add	r3, r3, r2
5 	ldrd	r0, [r3]
5 	ldrd	r2, [fp, #-20]
5 	bl	__aeabi_dmul
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r2
5 	mov	r1, r3
5 	movw	r3, #:lower16:SimplexTable
5 	movt	r3, #:upper16:SimplexTable
5 	ldr	r2, [fp, #-8]
5 	lsl	r2, r2, #3
5 	add	r3, r3, r2
5 	strd	r0, [r3]
5 	ldr	r3, [fp, #-8]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-8]
0 .L30:
6 	ldr	r3, [fp, #-8]
6 	cmp	r3, #4
6 	ble	.L31
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldrd	r0, [r3, #16]
1 	ldrd	r2, [fp, #-36]
1 	bl	__aeabi_dadd
1 	mov	r2, r0
1 	mov	r3, r1
1 	mov	r0, r2
1 	mov	r1, r3
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	strd	r0, [r3, #16]
1 	movw	r3, #:lower16:SimplexTable
1 	movt	r3, #:upper16:SimplexTable
1 	ldr	r2, [fp, #-60]
1 	lsl	r2, r2, #3
1 	add	r1, r3, r2
1 	mov	r2, #0
1 	mov	r3, #0
1 	strd	r2, [r1]
0 .L29:
2 	movw	r3, #:lower16:SimplexTable
2 	movt	r3, #:upper16:SimplexTable
2 	ldrd	r0, [r3, #32]
2 	mov	r2, #0
2 	mov	r3, #0
2 	bl	__aeabi_dcmpeq
2 	mov	r3, r0
2 	cmp	r3, #0
2 	beq	.L34
0 	b	.L35
0 .L34:
2 	movw	r3, #:lower16:SimplexTable
2 	movt	r3, #:upper16:SimplexTable
2 	ldrd	r0, [r3, #32]
2 	ldrd	r2, [fp, #-28]
2 	bl	__aeabi_dadd
2 	mov	r2, r0
2 	mov	r3, r1
2 	mov	r0, r2
2 	mov	r1, r3
2 	movw	r3, #:lower16:SimplexTable
2 	movt	r3, #:upper16:SimplexTable
2 	strd	r0, [r3, #32]
0 .L35:
2 	nop
2 	sub	sp, fp, #4
0 	@ sp needed
2 	pop	{fp, pc}
0 	.size	Maxim, .-Maxim
0 	.global	__aeabi_dsub
0 	.align	2
0 	.global	GaussCalc
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	GaussCalc, %function
0 GaussCalc:
0 	@ args = 0, pretend = 0, frame = 32
0 	@ frame_needed = 1, uses_anonymous_args = 0
2 	push	{r4, r5, fp, lr}
2 	add	fp, sp, #12
2 	sub	sp, sp, #32
2 	str	r0, [fp, #-40]
2 	str	r1, [fp, #-44]
2 	ldr	r3, [fp, #-40]
2 	cmp	r3, #1
2 	bne	.L37
1 	mov	r3, #2
1 	str	r3, [fp, #-20]
1 	movw	r2, #:lower16:SimplexTable
1 	movt	r2, #:upper16:SimplexTable
1 	ldr	r1, [fp, #-20]
1 	mov	r3, r1
1 	lsl	r3, r3, #2
1 	add	r3, r3, r1
1 	ldr	r1, [fp, #-44]
1 	add	r3, r3, r1
1 	lsl	r3, r3, #3
1 	add	r3, r2, r3
1 	ldrd	r0, [r3]
1 	movw	r2, #:lower16:SimplexTable
1 	movt	r2, #:upper16:SimplexTable
1 	ldr	ip, [fp, #-40]
1 	mov	r3, ip
1 	lsl	r3, r3, #2
1 	add	r3, r3, ip
1 	ldr	ip, [fp, #-44]
1 	add	r3, r3, ip
1 	lsl	r3, r3, #3
1 	add	r3, r2, r3
1 	ldrd	r2, [r3]
1 	bl	__aeabi_ddiv
1 	mov	r2, r0
1 	mov	r3, r1
1 	strd	r2, [fp, #-36]
1 	mov	r3, #0
1 	str	r3, [fp, #-16]
1 	b	.L38
0 .L39:
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-20]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-16]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r4, [r3]
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-40]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-16]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r0, [r3]
5 	ldrd	r2, [fp, #-36]
5 	bl	__aeabi_dmul
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r4
5 	mov	r1, r5
5 	bl	__aeabi_dsub
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r2
5 	mov	r1, r3
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	ip, [fp, #-20]
5 	mov	r3, ip
5 	lsl	r3, r3, #2
5 	add	r3, r3, ip
5 	ldr	ip, [fp, #-16]
5 	add	r3, r3, ip
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	strd	r0, [r3]
5 	ldr	r3, [fp, #-16]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-16]
0 .L38:
6 	ldr	r3, [fp, #-16]
6 	cmp	r3, #4
6 	ble	.L39
1 	b	.L43
0 .L37:
1 	mov	r3, #1
1 	str	r3, [fp, #-20]
1 	movw	r2, #:lower16:SimplexTable
1 	movt	r2, #:upper16:SimplexTable
1 	ldr	r1, [fp, #-20]
1 	mov	r3, r1
1 	lsl	r3, r3, #2
1 	add	r3, r3, r1
1 	ldr	r1, [fp, #-44]
1 	add	r3, r3, r1
1 	lsl	r3, r3, #3
1 	add	r3, r2, r3
1 	ldrd	r0, [r3]
1 	movw	r2, #:lower16:SimplexTable
1 	movt	r2, #:upper16:SimplexTable
1 	ldr	ip, [fp, #-40]
1 	mov	r3, ip
1 	lsl	r3, r3, #2
1 	add	r3, r3, ip
1 	ldr	ip, [fp, #-44]
1 	add	r3, r3, ip
1 	lsl	r3, r3, #3
1 	add	r3, r2, r3
1 	ldrd	r2, [r3]
1 	bl	__aeabi_ddiv
1 	mov	r2, r0
1 	mov	r3, r1
1 	strd	r2, [fp, #-28]
1 	mov	r3, #0
1 	str	r3, [fp, #-16]
1 	b	.L41
0 .L42:
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-20]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-16]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r4, [r3]
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-40]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-16]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r0, [r3]
5 	ldrd	r2, [fp, #-28]
5 	bl	__aeabi_dmul
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r4
5 	mov	r1, r5
5 	bl	__aeabi_dsub
5 	mov	r2, r0
5 	mov	r3, r1
5 	mov	r0, r2
5 	mov	r1, r3
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	ip, [fp, #-20]
5 	mov	r3, ip
5 	lsl	r3, r3, #2
5 	add	r3, r3, ip
5 	ldr	ip, [fp, #-16]
5 	add	r3, r3, ip
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	strd	r0, [r3]
5 	ldr	r3, [fp, #-16]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-16]
0 .L41:
6 	ldr	r3, [fp, #-16]
6 	cmp	r3, #4
6 	ble	.L42
0 .L43:
2 	nop
2 	sub	sp, fp, #12
0 	@ sp needed
2 	pop	{r4, r5, fp, pc}
0 	.size	GaussCalc, .-GaussCalc
0 	.align	2
0 	.global	Exchange
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	Exchange, %function
0 Exchange:
0 	@ args = 0, pretend = 0, frame = 24
0 	@ frame_needed = 1, uses_anonymous_args = 0
0 	@ link register save eliminated.
2 	push	{r4, r5, r6, r7, r8, r9, fp}
2 	add	fp, sp, #24
2 	sub	sp, sp, #28
2 	str	r0, [fp, #-40]
2 	str	r1, [fp, #-44]
2 	ldr	r3, [fp, #-40]
2 	cmp	r3, #1
2 	bne	.L45
1 	mov	r3, #1
1 	str	r3, [fp, #-36]
1 	mov	r3, #0
1 	str	r3, [fp, #-32]
1 	b	.L46
0 .L47:
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-36]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-32]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r2, [r3]
5 	str	r2, [fp, #-52]
5 	eor	r3, r3, #-2147483648
5 	str	r3, [fp, #-48]
5 	movw	r3, #:lower16:TempState
5 	movt	r3, #:upper16:TempState
5 	ldr	r2, [fp, #-32]
5 	lsl	r2, r2, #3
5 	add	r3, r3, r2
5 	ldrd	r0, [fp, #-52]
5 	strd	r0, [r3]
5 	ldr	r3, [fp, #-32]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-32]
0 .L46:
6 	ldr	r3, [fp, #-32]
6 	cmp	r3, #4
6 	ble	.L47
1 	movw	r3, #:lower16:TempState
1 	movt	r3, #:upper16:TempState
1 	ldrd	r2, [r3, #32]
1 	mov	r8, r2
1 	eor	r9, r3, #-2147483648
1 	movw	r3, #:lower16:TempState
1 	movt	r3, #:upper16:TempState
1 	strd	r8, [r3, #32]
1 	b	.L51
0 .L45:
1 	mov	r3, #2
1 	str	r3, [fp, #-36]
1 	mov	r3, #0
1 	str	r3, [fp, #-32]
1 	b	.L49
0 .L50:
5 	movw	r2, #:lower16:SimplexTable
5 	movt	r2, #:upper16:SimplexTable
5 	ldr	r1, [fp, #-36]
5 	mov	r3, r1
5 	lsl	r3, r3, #2
5 	add	r3, r3, r1
5 	ldr	r1, [fp, #-32]
5 	add	r3, r3, r1
5 	lsl	r3, r3, #3
5 	add	r3, r2, r3
5 	ldrd	r2, [r3]
5 	mov	r6, r2
5 	eor	r7, r3, #-2147483648
5 	movw	r3, #:lower16:TempState
5 	movt	r3, #:upper16:TempState
5 	ldr	r2, [fp, #-32]
5 	lsl	r2, r2, #3
5 	add	r3, r3, r2
5 	strd	r6, [r3]
5 	ldr	r3, [fp, #-32]
5 	add	r3, r3, #1
5 	str	r3, [fp, #-32]
0 .L49:
6 	ldr	r3, [fp, #-32]
6 	cmp	r3, #4
6 	ble	.L50
1 	movw	r3, #:lower16:TempState
1 	movt	r3, #:upper16:TempState
1 	ldrd	r2, [r3, #32]
1 	mov	r4, r2
1 	eor	r5, r3, #-2147483648
1 	movw	r3, #:lower16:TempState
1 	movt	r3, #:upper16:TempState
1 	strd	r4, [r3, #32]
0 .L51:
2 	nop
2 	sub	sp, fp, #24
0 	@ sp needed
2 	pop	{r4, r5, r6, r7, r8, r9, fp}
2 	bx	lr
0 	.size	Exchange, .-Exchange
0 	.section	.rodata
0 	.align	2
0 .LC5:
0 	.ascii	"\012------------------Simplex Table Step = %d------"
0 	.ascii	"-----------\012\000"
0 	.align	2
0 .LC6:
0 	.ascii	"%10lf \000"
0 	.text
0 	.align	2
0 	.global	ShowTable
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	ShowTable, %function
0 ShowTable:
0 	@ args = 0, pretend = 0, frame = 16
0 	@ frame_needed = 1, uses_anonymous_args = 0
7 	push	{fp, lr}
7 	add	fp, sp, #4
7 	sub	sp, sp, #16
7 	mov	r3, r0
7 	strh	r3, [fp, #-14]	@ movhi
7 	ldrsh	r3, [fp, #-14]
7 	mov	r1, r3
7 	movw	r0, #:lower16:.LC5
7 	movt	r0, #:upper16:.LC5
7 	bl	printf
7 	mov	r3, #0
7 	str	r3, [fp, #-8]
7 	b	.L53
0 .L56:
21 	mov	r3, #0
21 	str	r3, [fp, #-12]
21 	b	.L54
0 .L55:
105 	movw	r2, #:lower16:SimplexTable
105 	movt	r2, #:upper16:SimplexTable
105 	ldr	r1, [fp, #-8]
105 	mov	r3, r1
105 	lsl	r3, r3, #2
105 	add	r3, r3, r1
105 	ldr	r1, [fp, #-12]
105 	add	r3, r3, r1
105 	lsl	r3, r3, #3
105 	add	r3, r2, r3
105 	ldrd	r2, [r3]
105 	movw	r0, #:lower16:.LC6
105 	movt	r0, #:upper16:.LC6
105 	bl	printf
105 	ldr	r3, [fp, #-12]
105 	add	r3, r3, #1
105 	str	r3, [fp, #-12]
0 .L54:
126 	ldr	r3, [fp, #-12]
126 	cmp	r3, #4
126 	ble	.L55
21 	mov	r0, #10
21 	bl	putchar
21 	ldr	r3, [fp, #-8]
21 	add	r3, r3, #1
21 	str	r3, [fp, #-8]
0 .L53:
28 	ldr	r3, [fp, #-8]
28 	cmp	r3, #2
28 	ble	.L56
7 	nop
7 	nop
7 	sub	sp, fp, #4
0 	@ sp needed
7 	pop	{fp, pc}
0 	.size	ShowTable, .-ShowTable
0 	.section	.rodata
0 	.align	3
0 .LC0:
0 	.word	0
0 	.word	1077739520
0 	.word	0
0 	.word	1078362112
0 	.word	0
0 	.word	0
0 	.word	0
0 	.word	0
0 	.word	0
0 	.word	0
0 	.word	0
0 	.word	1073741824
0 	.word	0
0 	.word	1075838976
0 	.word	0
0 	.word	1072693248
0 	.word	0
0 	.word	0
0 	.word	0
0 	.word	1078853632
0 	.word	0
0 	.word	1074790400
0 	.word	0
0 	.word	1074790400
0 	.word	0
0 	.word	0
0 	.word	0
0 	.word	1072693248
0 	.word	0
0 	.word	1078853632
0 	.text
0 	.align	2
0 	.global	Input
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	Input, %function
0 Input:
0 	@ args = 0, pretend = 0, frame = 128
0 	@ frame_needed = 1, uses_anonymous_args = 0
1 	push	{fp, lr}
1 	add	fp, sp, #4
1 	sub	sp, sp, #128
1 	movw	r3, #:lower16:.LC0
1 	movt	r3, #:upper16:.LC0
1 	sub	r0, fp, #132
1 	mov	r1, r3
1 	mov	r3, #120
1 	mov	r2, r3
1 	bl	memcpy
1 	mov	r3, #0
1 	str	r3, [fp, #-8]
1 	b	.L58
0 .L61:
3 	mov	r3, #0
3 	str	r3, [fp, #-12]
3 	b	.L59
0 .L60:
15 	ldr	r2, [fp, #-8]
15 	mov	r3, r2
15 	lsl	r3, r3, #2
15 	add	r3, r3, r2
15 	ldr	r2, [fp, #-12]
15 	add	r3, r3, r2
15 	lsl	r3, r3, #3
15 	sub	r2, fp, #4
15 	add	r3, r2, r3
15 	sub	r3, r3, #128
15 	ldrd	r0, [r3]
15 	movw	r2, #:lower16:SimplexTable
15 	movt	r2, #:upper16:SimplexTable
15 	ldr	ip, [fp, #-8]
15 	mov	r3, ip
15 	lsl	r3, r3, #2
15 	add	r3, r3, ip
15 	ldr	ip, [fp, #-12]
15 	add	r3, r3, ip
15 	lsl	r3, r3, #3
15 	add	r3, r2, r3
15 	strd	r0, [r3]
15 	ldr	r3, [fp, #-12]
15 	add	r3, r3, #1
15 	str	r3, [fp, #-12]
0 .L59:
18 	ldr	r3, [fp, #-12]
18 	cmp	r3, #4
18 	ble	.L60
3 	ldr	r3, [fp, #-8]
3 	add	r3, r3, #1
3 	str	r3, [fp, #-8]
0 .L58:
4 	ldr	r3, [fp, #-8]
4 	cmp	r3, #2
4 	ble	.L61
1 	mov	r0, #0
1 	bl	ShowTable
1 	nop
1 	sub	sp, fp, #4
0 	@ sp needed
1 	pop	{fp, pc}
