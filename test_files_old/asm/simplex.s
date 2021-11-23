	.arch armv7-a
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"simplex.c"
	.text
	.comm	SimplexTable,120,8
	.comm	TempState,40,8
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	bl	Input
	bl	X2Calc
	bl	X1Calc
	bl	Result
	mov	r3, #0
	mov	r0, r3
	pop	{fp, pc}
	.size	main, .-main
	.global	__aeabi_ddiv
	.global	__aeabi_dcmplt
	.align	2
	.global	X2Calc
	.syntax unified
	.arm
	.fpu softvfp
	.type	X2Calc, %function
X2Calc:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #56
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r0, [r3, #72]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #48]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	strd	r2, [fp, #-20]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r0, [r3, #112]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #88]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	strd	r2, [fp, #-28]
	ldrd	r2, [fp, #-28]
	ldrd	r0, [fp, #-20]
	bl	__aeabi_dcmplt
	mov	r3, r0
	cmp	r3, #0
	beq	.L12
	mov	r3, #1
	str	r3, [fp, #-32]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #48]
	strd	r2, [fp, #-60]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L6
.L7:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-32]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-8]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-60]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-32]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-8]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	strd	r0, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L6:
	ldr	r3, [fp, #-8]
	cmp	r3, #4
	ble	.L7
	mov	r0, #1
	bl	ShowTable
	mov	r3, #1
	str	r3, [fp, #-48]
	mov	r3, #1
	str	r3, [fp, #-52]
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-48]
	bl	GaussCalc
	mov	r0, #2
	bl	ShowTable
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-48]
	bl	Exchange
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-48]
	bl	Maxim
	mov	r0, #3
	bl	ShowTable
	b	.L13
.L12:
	mov	r3, #2
	str	r3, [fp, #-32]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #88]
	strd	r2, [fp, #-44]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L9
.L10:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-32]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-8]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-44]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-32]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-8]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	strd	r0, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L9:
	ldr	r3, [fp, #-8]
	cmp	r3, #4
	ble	.L10
	mov	r0, #1
	bl	ShowTable
	mov	r3, #2
	str	r3, [fp, #-48]
	mov	r3, #1
	str	r3, [fp, #-52]
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-48]
	bl	GaussCalc
	mov	r0, #2
	bl	ShowTable
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-48]
	bl	Exchange
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-48]
	bl	Maxim
	mov	r0, #3
	bl	ShowTable
.L13:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	X2Calc, .-X2Calc
	.align	2
	.global	X1Calc
	.syntax unified
	.arm
	.fpu softvfp
	.type	X1Calc, %function
X1Calc:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	mov	r3, #2
	str	r3, [fp, #-12]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #80]
	strd	r2, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L15
.L16:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-12]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-8]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-20]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-12]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-8]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	strd	r0, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L15:
	ldr	r3, [fp, #-8]
	cmp	r3, #4
	ble	.L16
	mov	r0, #4
	bl	ShowTable
	mov	r3, #2
	str	r3, [fp, #-24]
	mov	r3, #0
	str	r3, [fp, #-28]
	ldr	r1, [fp, #-28]
	ldr	r0, [fp, #-24]
	bl	GaussCalc
	mov	r0, #5
	bl	ShowTable
	ldr	r1, [fp, #-28]
	ldr	r0, [fp, #-24]
	bl	Exchange
	ldr	r1, [fp, #-28]
	ldr	r0, [fp, #-24]
	bl	Maxim
	mov	r0, #6
	bl	ShowTable
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	X1Calc, .-X1Calc
	.global	__aeabi_dcmpeq
	.section	.rodata
	.align	2
.LC1:
	.ascii	"\012***** Result *****\000"
	.align	2
.LC2:
	.ascii	"x1 = %lf, \000"
	.align	2
.LC3:
	.ascii	"x2 = %lf, \000"
	.align	2
.LC4:
	.ascii	"f = %lf\012\000"
	.text
	.align	2
	.global	Result
	.syntax unified
	.arm
	.fpu softvfp
	.type	Result, %function
Result:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #40
	mov	r3, #0
	str	r3, [fp, #-16]
	mov	r3, #1
	str	r3, [fp, #-8]
	b	.L18
.L23:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L19
.L22:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-8]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-12]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	mov	r3, r0
	cmp	r3, #0
	beq	.L20
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldr	r2, [fp, #-8]
	mov	r1, #40
	mul	r2, r1, r2
	add	r3, r3, r2
	add	r3, r3, #32
	ldrd	r2, [r3]
	ldr	r1, [fp, #-16]
	lsl	r1, r1, #3
	sub	r0, fp, #4
	add	r1, r0, r1
	sub	r1, r1, #40
	strd	r2, [r1]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L20:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L19:
	ldr	r3, [fp, #-12]
	cmp	r3, #4
	ble	.L22
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L18:
	ldr	r3, [fp, #-8]
	cmp	r3, #2
	ble	.L23
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #32]
	ldr	r1, [fp, #-16]
	lsl	r1, r1, #3
	sub	r0, fp, #4
	add	r1, r0, r1
	sub	r1, r1, #40
	strd	r2, [r1]
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	puts
	ldrd	r2, [fp, #-44]
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	printf
	ldrd	r2, [fp, #-36]
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	printf
	ldrd	r2, [fp, #-28]
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	printf
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	Result, .-Result
	.global	__aeabi_dmul
	.global	__aeabi_dadd
	.align	2
	.global	Maxim
	.syntax unified
	.arm
	.fpu softvfp
	.type	Maxim, %function
Maxim:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #56
	str	r0, [fp, #-56]
	str	r1, [fp, #-60]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldr	r2, [fp, #-60]
	lsl	r2, r2, #3
	add	r3, r3, r2
	ldrd	r2, [r3]
	strd	r2, [fp, #-20]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #32]
	strd	r2, [fp, #-28]
	ldr	r3, [fp, #-56]
	cmp	r3, #1
	bne	.L26
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3]
	strd	r2, [fp, #-52]
	mov	r3, #1
	str	r3, [fp, #-40]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L27
.L28:
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	ldr	r2, [fp, #-8]
	lsl	r2, r2, #3
	add	r3, r3, r2
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-20]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldr	r2, [fp, #-8]
	lsl	r2, r2, #3
	add	r3, r3, r2
	strd	r0, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L27:
	ldr	r3, [fp, #-8]
	cmp	r3, #4
	ble	.L28
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-52]
	bl	__aeabi_dadd
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	strd	r0, [r3]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldr	r2, [fp, #-60]
	lsl	r2, r2, #3
	add	r1, r3, r2
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r1]
	b	.L29
.L26:
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r2, [r3, #16]
	strd	r2, [fp, #-36]
	mov	r3, #2
	str	r3, [fp, #-40]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L30
.L31:
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	ldr	r2, [fp, #-8]
	lsl	r2, r2, #3
	add	r3, r3, r2
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-20]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldr	r2, [fp, #-8]
	lsl	r2, r2, #3
	add	r3, r3, r2
	strd	r0, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L30:
	ldr	r3, [fp, #-8]
	cmp	r3, #4
	ble	.L31
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r0, [r3, #16]
	ldrd	r2, [fp, #-36]
	bl	__aeabi_dadd
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	strd	r0, [r3, #16]
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldr	r2, [fp, #-60]
	lsl	r2, r2, #3
	add	r1, r3, r2
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r1]
.L29:
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r0, [r3, #32]
	mov	r2, #0
	mov	r3, #0
	bl	__aeabi_dcmpeq
	mov	r3, r0
	cmp	r3, #0
	beq	.L34
	b	.L35
.L34:
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	ldrd	r0, [r3, #32]
	ldrd	r2, [fp, #-28]
	bl	__aeabi_dadd
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r3, #:lower16:SimplexTable
	movt	r3, #:upper16:SimplexTable
	strd	r0, [r3, #32]
.L35:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	Maxim, .-Maxim
	.global	__aeabi_dsub
	.align	2
	.global	GaussCalc
	.syntax unified
	.arm
	.fpu softvfp
	.type	GaussCalc, %function
GaussCalc:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, fp, lr}
	add	fp, sp, #12
	sub	sp, sp, #32
	str	r0, [fp, #-40]
	str	r1, [fp, #-44]
	ldr	r3, [fp, #-40]
	cmp	r3, #1
	bne	.L37
	mov	r3, #2
	str	r3, [fp, #-20]
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-20]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-44]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-40]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-44]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r2, [r3]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	strd	r2, [fp, #-36]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L38
.L39:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-20]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-16]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r4, [r3]
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-40]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-16]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-36]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-20]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-16]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	strd	r0, [r3]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L38:
	ldr	r3, [fp, #-16]
	cmp	r3, #4
	ble	.L39
	b	.L43
.L37:
	mov	r3, #1
	str	r3, [fp, #-20]
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-20]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-44]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-40]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-44]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r2, [r3]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	strd	r2, [fp, #-28]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L41
.L42:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-20]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-16]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r4, [r3]
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-40]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-16]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r0, [r3]
	ldrd	r2, [fp, #-28]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r2
	mov	r1, r3
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-20]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-16]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	strd	r0, [r3]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L41:
	ldr	r3, [fp, #-16]
	cmp	r3, #4
	ble	.L42
.L43:
	nop
	sub	sp, fp, #12
	@ sp needed
	pop	{r4, r5, fp, pc}
	.size	GaussCalc, .-GaussCalc
	.align	2
	.global	Exchange
	.syntax unified
	.arm
	.fpu softvfp
	.type	Exchange, %function
Exchange:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5, r6, r7, r8, r9, fp}
	add	fp, sp, #24
	sub	sp, sp, #28
	str	r0, [fp, #-40]
	str	r1, [fp, #-44]
	ldr	r3, [fp, #-40]
	cmp	r3, #1
	bne	.L45
	mov	r3, #1
	str	r3, [fp, #-36]
	mov	r3, #0
	str	r3, [fp, #-32]
	b	.L46
.L47:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-36]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-32]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r2, [r3]
	str	r2, [fp, #-52]
	eor	r3, r3, #-2147483648
	str	r3, [fp, #-48]
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	ldr	r2, [fp, #-32]
	lsl	r2, r2, #3
	add	r3, r3, r2
	ldrd	r0, [fp, #-52]
	strd	r0, [r3]
	ldr	r3, [fp, #-32]
	add	r3, r3, #1
	str	r3, [fp, #-32]
.L46:
	ldr	r3, [fp, #-32]
	cmp	r3, #4
	ble	.L47
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	ldrd	r2, [r3, #32]
	mov	r8, r2
	eor	r9, r3, #-2147483648
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	strd	r8, [r3, #32]
	b	.L51
.L45:
	mov	r3, #2
	str	r3, [fp, #-36]
	mov	r3, #0
	str	r3, [fp, #-32]
	b	.L49
.L50:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-36]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-32]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r2, [r3]
	mov	r6, r2
	eor	r7, r3, #-2147483648
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	ldr	r2, [fp, #-32]
	lsl	r2, r2, #3
	add	r3, r3, r2
	strd	r6, [r3]
	ldr	r3, [fp, #-32]
	add	r3, r3, #1
	str	r3, [fp, #-32]
.L49:
	ldr	r3, [fp, #-32]
	cmp	r3, #4
	ble	.L50
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	ldrd	r2, [r3, #32]
	mov	r4, r2
	eor	r5, r3, #-2147483648
	movw	r3, #:lower16:TempState
	movt	r3, #:upper16:TempState
	strd	r4, [r3, #32]
.L51:
	nop
	sub	sp, fp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, fp}
	bx	lr
	.size	Exchange, .-Exchange
	.section	.rodata
	.align	2
.LC5:
	.ascii	"\012------------------Simplex Table Step = %d------"
	.ascii	"-----------\012\000"
	.align	2
.LC6:
	.ascii	"%10lf \000"
	.text
	.align	2
	.global	ShowTable
	.syntax unified
	.arm
	.fpu softvfp
	.type	ShowTable, %function
ShowTable:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	mov	r3, r0
	strh	r3, [fp, #-14]	@ movhi
	ldrsh	r3, [fp, #-14]
	mov	r1, r3
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	printf
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L53
.L56:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L54
.L55:
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	r1, [fp, #-8]
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	ldr	r1, [fp, #-12]
	add	r3, r3, r1
	lsl	r3, r3, #3
	add	r3, r2, r3
	ldrd	r2, [r3]
	movw	r0, #:lower16:.LC6
	movt	r0, #:upper16:.LC6
	bl	printf
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L54:
	ldr	r3, [fp, #-12]
	cmp	r3, #4
	ble	.L55
	mov	r0, #10
	bl	putchar
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L53:
	ldr	r3, [fp, #-8]
	cmp	r3, #2
	ble	.L56
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	ShowTable, .-ShowTable
	.section	.rodata
	.align	3
.LC0:
	.word	0
	.word	1077739520
	.word	0
	.word	1078362112
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1073741824
	.word	0
	.word	1075838976
	.word	0
	.word	1072693248
	.word	0
	.word	0
	.word	0
	.word	1078853632
	.word	0
	.word	1074790400
	.word	0
	.word	1074790400
	.word	0
	.word	0
	.word	0
	.word	1072693248
	.word	0
	.word	1078853632
	.text
	.align	2
	.global	Input
	.syntax unified
	.arm
	.fpu softvfp
	.type	Input, %function
Input:
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #128
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	sub	r0, fp, #132
	mov	r1, r3
	mov	r3, #120
	mov	r2, r3
	bl	memcpy
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L58
.L61:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L59
.L60:
	ldr	r2, [fp, #-8]
	mov	r3, r2
	lsl	r3, r3, #2
	add	r3, r3, r2
	ldr	r2, [fp, #-12]
	add	r3, r3, r2
	lsl	r3, r3, #3
	sub	r2, fp, #4
	add	r3, r2, r3
	sub	r3, r3, #128
	ldrd	r0, [r3]
	movw	r2, #:lower16:SimplexTable
	movt	r2, #:upper16:SimplexTable
	ldr	ip, [fp, #-8]
	mov	r3, ip
	lsl	r3, r3, #2
	add	r3, r3, ip
	ldr	ip, [fp, #-12]
	add	r3, r3, ip
	lsl	r3, r3, #3
	add	r3, r2, r3
	strd	r0, [r3]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L59:
	ldr	r3, [fp, #-12]
	cmp	r3, #4
	ble	.L60
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L58:
	ldr	r3, [fp, #-8]
	cmp	r3, #2
	ble	.L61
	mov	r0, #0
	bl	ShowTable
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	Input, .-Input
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
