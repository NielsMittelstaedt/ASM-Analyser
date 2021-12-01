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
	.file	"simplex.c"
	.text
	.global	__aeabi_ddiv
	.global	__aeabi_dcmplt
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"\012------------------Simplex Table Step = %d------"
	.ascii	"-----------\012\000"
	.align	2
.LC2:
	.ascii	"%10lf \000"
	.global	__aeabi_dmul
	.global	__aeabi_dsub
	.global	__aeabi_dadd
	.global	__aeabi_dcmpeq
	.text
	.align	2
	.global	X2Calc
	.syntax unified
	.arm
	.fpu softvfp
	.type	X2Calc, %function
X2Calc:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	movw	fp, #:lower16:SimplexTable
	movt	fp, #:upper16:SimplexTable
	sub	sp, sp, #28
	ldrd	r8, [fp, #48]
	ldrd	r0, [fp, #72]
	mov	r2, r8
	mov	r3, r9
	bl	__aeabi_ddiv
	ldrd	r6, [fp, #88]
	mov	r2, r6
	mov	r3, r7
	mov	r4, r0
	mov	r5, r1
	ldrd	r0, [fp, #112]
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	mov	r0, r4
	mov	r1, r5
	strd	r2, [sp]
	bl	__aeabi_dcmplt
	cmp	r0, #0
	beq	.L34
	mov	r2, r8
	mov	r3, r9
	ldrd	r0, [fp, #40]
	add	r10, fp, #40
	bl	__aeabi_ddiv
	mov	r2, r8
	mov	r3, r9
	movw	r7, #:lower16:.LC2
	mov	r6, r10
	movt	r7, #:upper16:.LC2
	strd	r0, [fp, #40]
	mov	r0, r8
	mov	r1, r9
	bl	__aeabi_ddiv
	mov	r2, r8
	mov	r3, r9
	strd	r0, [fp, #48]
	ldrd	r0, [fp, #56]
	bl	__aeabi_ddiv
	mov	r2, r8
	mov	r3, r9
	strd	r0, [fp, #56]
	ldrd	r0, [fp, #64]
	bl	__aeabi_ddiv
	mov	r2, #1
	strd	r4, [fp, #72]
	mov	r8, r0
	mov	r9, r1
	mov	r0, r2
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	strd	r8, [fp, #64]
	bl	__printf_chk
.L4:
	sub	r4, r6, #40
.L5:
	ldrd	r2, [r4], #8
	mov	r1, r7
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L5
	mov	r0, #10
	add	r6, r4, #40
	bl	putchar
	ldr	r3, .L40
	cmp	r3, r6
	bne	.L4
	ldrd	r2, [fp, #88]
	movw	r5, #:lower16:.LC2
	ldrd	r6, [fp, #48]
	movt	r5, #:upper16:.LC2
	mov	r4, r10
	strd	r2, [sp]
	mov	r0, r2
	mov	r1, r3
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_ddiv
	ldrd	r2, [fp, #40]
	mov	r8, r0
	mov	r9, r1
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #80]
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r6
	strd	r2, [fp, #80]
	mov	r1, r7
	mov	r2, r8
	mov	r3, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [sp]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #56]
	mov	r6, r0
	mov	r7, r1
	mov	r0, r8
	strd	r6, [fp, #88]
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #96]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #64]
	mov	r6, r0
	mov	r7, r1
	mov	r0, r8
	strd	r6, [fp, #96]
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #104]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #72]
	mov	r6, r0
	mov	r7, r1
	mov	r0, r8
	strd	r6, [fp, #104]
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #112]
	bl	__aeabi_dsub
	mov	r2, #2
	mov	r6, r0
	mov	r7, r1
	mov	r0, #1
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	strd	r6, [fp, #112]
	bl	__printf_chk
.L7:
	sub	r6, r4, #40
.L8:
	ldrd	r2, [r6], #8
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L8
	mov	r0, #10
	add	r4, r6, #40
	bl	putchar
	ldr	r3, .L40
	cmp	r3, r4
	bne	.L7
	ldr	r3, [fp, #44]
	movw	ip, #:lower16:TempState
	ldr	r5, [fp, #40]
	movt	ip, #:upper16:TempState
	add	r3, r3, #-2147483648
	str	r3, [sp, #12]
	ldr	r3, [sp, #12]
	ldr	r1, [fp, #60]
	mov	r2, r5
	ldr	r0, [fp, #56]
	strd	r2, [ip]
	add	lr, r1, #-2147483648
	ldrd	r2, [fp, #72]
	ldr	r1, [fp, #64]
	mov	r7, lr
	mov	r6, r0
	ldr	r4, [fp, #68]
	strd	r2, [sp]
	mov	r3, lr
	ldr	lr, [fp, #48]
	mov	r2, r6
	str	r1, [sp, #16]
	add	r4, r4, #-2147483648
	ldrd	r8, [fp, #8]
	strd	r6, [ip, #16]
	mov	r1, r4
	ldr	r0, [sp, #16]
	ldrd	r6, [sp]
	str	lr, [ip, #8]
	ldr	lr, [fp, #52]
	strd	r0, [ip, #24]
	mov	r0, r8
	add	lr, lr, #-2147483648
	strd	r6, [ip, #32]
	str	lr, [ip, #12]
	mov	r1, r9
	bl	__aeabi_dmul
	ldrd	r6, [fp, #32]
	ldr	r2, [sp, #16]
	mov	r3, r4
	strd	r6, [sp, #16]
	strd	r0, [fp, #16]
	mov	r0, r8
	mov	r1, r9
	bl	__aeabi_dmul
	ldrd	r2, [sp]
	ldrd	r6, [fp]
	strd	r0, [fp, #24]
	mov	r0, r8
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r5
	ldr	r3, [sp, #12]
	mov	r4, r0
	mov	r5, r1
	mov	r0, r8
	mov	r1, r9
	strd	r4, [fp, #32]
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_dadd
	mov	r2, #0
	mov	r3, #0
	strd	r2, [fp, #8]
	strd	r0, [fp]
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	beq	.L38
.L10:
	movw	r1, #:lower16:.LC1
	mov	r2, #3
	movt	r1, #:upper16:.LC1
	mov	r0, #1
	bl	__printf_chk
	movw	r5, #:lower16:.LC2
	movt	r5, #:upper16:.LC2
.L12:
	sub	r4, r10, #40
.L13:
	ldrd	r2, [r4], #8
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r10, r4
	bne	.L13
	mov	r0, #10
	add	r10, r10, #40
	bl	putchar
	ldr	r3, .L40
	cmp	r3, r10
	bne	.L12
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L34:
	mov	r2, r6
	mov	r3, r7
	ldrd	r0, [fp, #80]
	add	r10, fp, #40
	bl	__aeabi_ddiv
	mov	r2, r6
	mov	r3, r7
	mov	r5, r10
	strd	r0, [fp, #80]
	mov	r0, r6
	mov	r1, r7
	bl	__aeabi_ddiv
	mov	r2, r6
	mov	r3, r7
	strd	r0, [fp, #88]
	ldrd	r0, [fp, #96]
	bl	__aeabi_ddiv
	mov	r2, r6
	mov	r3, r7
	strd	r0, [fp, #96]
	ldrd	r0, [fp, #104]
	bl	__aeabi_ddiv
	ldrd	r8, [sp]
	mov	r2, #1
	strd	r8, [fp, #112]
	mov	r6, r0
	mov	r7, r1
	mov	r0, r2
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	strd	r6, [fp, #104]
	movw	r6, #:lower16:.LC2
	movt	r6, #:upper16:.LC2
	bl	__printf_chk
.L15:
	sub	r4, r5, #40
.L16:
	ldrd	r2, [r4], #8
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L16
	mov	r0, #10
	add	r5, r5, #40
	bl	putchar
	ldr	r3, .L40
	cmp	r5, r3
	bne	.L15
	ldrd	r2, [fp, #48]
	movw	r5, #:lower16:.LC2
	ldrd	r6, [fp, #88]
	movt	r5, #:upper16:.LC2
	mov	r4, r10
	strd	r2, [sp]
	mov	r0, r2
	mov	r1, r3
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_ddiv
	ldrd	r2, [fp, #80]
	mov	r8, r0
	mov	r9, r1
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #40]
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r6
	strd	r2, [fp, #40]
	mov	r1, r7
	mov	r2, r8
	mov	r3, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [sp]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #96]
	mov	r6, r0
	mov	r7, r1
	mov	r0, r8
	strd	r6, [fp, #48]
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #56]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #104]
	mov	r6, r0
	mov	r7, r1
	mov	r0, r8
	strd	r6, [fp, #56]
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #64]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #112]
	mov	r6, r0
	mov	r7, r1
	mov	r0, r8
	strd	r6, [fp, #64]
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #72]
	bl	__aeabi_dsub
	mov	r2, #2
	mov	r6, r0
	mov	r7, r1
	mov	r0, #1
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	strd	r6, [fp, #72]
	bl	__printf_chk
.L18:
	sub	r6, r4, #40
.L19:
	ldrd	r2, [r6], #8
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r6, r4
	bne	.L19
	mov	r0, #10
	add	r4, r6, #40
	bl	putchar
	ldr	r3, .L40
	cmp	r4, r3
	bne	.L18
	ldr	lr, [fp, #84]
	movw	ip, #:lower16:TempState
	ldr	r5, [fp, #80]
	movt	ip, #:upper16:TempState
	ldr	r6, [fp, #104]
	add	lr, lr, #-2147483648
	ldr	r3, [fp, #100]
	mov	r0, r5
	mov	r1, lr
	add	r3, r3, #-2147483648
	strd	r0, [ip]
	str	r3, [sp, #12]
	mov	r2, r5
	ldrd	r0, [fp, #112]
	mov	r3, lr
	str	r6, [sp, #16]
	ldr	r5, [fp, #96]
	ldr	r6, [sp, #16]
	ldr	r9, [sp, #12]
	strd	r0, [sp]
	mov	r8, r5
	ldr	r4, [fp, #108]
	mov	r0, r6
	strd	r8, [ip, #16]
	ldr	r1, [fp, #88]
	add	r4, r4, #-2147483648
	ldrd	r8, [fp, #8]
	ldrd	r6, [sp]
	ldr	lr, [fp, #92]
	str	r1, [ip, #8]
	mov	r1, r4
	add	lr, lr, #-2147483648
	strd	r0, [ip, #24]
	strd	r6, [ip, #32]
	mov	r0, r8
	str	lr, [ip, #12]
	mov	r1, r9
	bl	__aeabi_dmul
	ldrd	r6, [fp, #32]
	ldr	r2, [sp, #16]
	mov	r3, r4
	strd	r6, [sp, #16]
	strd	r0, [fp]
	mov	r0, r8
	mov	r1, r9
	bl	__aeabi_dmul
	ldrd	r2, [sp]
	ldrd	r6, [fp, #16]
	strd	r0, [fp, #24]
	mov	r0, r8
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r5
	ldr	r3, [sp, #12]
	mov	r4, r0
	mov	r5, r1
	mov	r0, r8
	mov	r1, r9
	strd	r4, [fp, #32]
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_dadd
	mov	r2, #0
	mov	r3, #0
	strd	r2, [fp, #8]
	strd	r0, [fp, #16]
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	beq	.L39
.L21:
	movw	r1, #:lower16:.LC1
	mov	r2, #3
	movt	r1, #:upper16:.LC1
	mov	r0, #1
	bl	__printf_chk
	movw	r5, #:lower16:.LC2
	movt	r5, #:upper16:.LC2
.L23:
	sub	r4, r10, #40
.L24:
	ldrd	r2, [r4], #8
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r10
	bne	.L24
	mov	r0, #10
	add	r10, r10, #40
	bl	putchar
	ldr	r3, .L40
	cmp	r10, r3
	bne	.L23
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L39:
	ldrd	r0, [sp, #16]
	mov	r2, r4
	mov	r3, r5
	bl	__aeabi_dadd
	strd	r0, [fp, #32]
	b	.L21
.L38:
	ldrd	r0, [sp, #16]
	mov	r2, r4
	mov	r3, r5
	bl	__aeabi_dadd
	strd	r0, [fp, #32]
	b	.L10
.L41:
	.align	2
.L40:
	.word	SimplexTable+160
	.size	X2Calc, .-X2Calc
	.align	2
	.global	X1Calc
	.syntax unified
	.arm
	.fpu softvfp
	.type	X1Calc, %function
X1Calc:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	movw	fp, #:lower16:SimplexTable
	movt	fp, #:upper16:SimplexTable
	sub	sp, sp, #28
	add	r10, fp, #40
	ldrd	r4, [fp, #80]
	mov	r3, r5
	mov	r2, r4
	mov	r1, r5
	mov	r0, r4
	bl	__aeabi_ddiv
	mov	r3, r5
	mov	r2, r4
	strd	r0, [fp, #80]
	ldrd	r0, [fp, #88]
	bl	__aeabi_ddiv
	mov	r3, r5
	mov	r2, r4
	strd	r0, [fp, #88]
	ldrd	r0, [fp, #96]
	bl	__aeabi_ddiv
	mov	r3, r5
	mov	r2, r4
	strd	r0, [fp, #96]
	ldrd	r0, [fp, #104]
	bl	__aeabi_ddiv
	mov	r3, r5
	mov	r2, r4
	mov	r5, r10
	strd	r0, [fp, #104]
	ldrd	r0, [fp, #112]
	bl	__aeabi_ddiv
	mov	r2, #4
	mov	r6, r0
	mov	r7, r1
	mov	r0, #1
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	strd	r6, [fp, #112]
	bl	__printf_chk
	movw	r6, #:lower16:.LC2
	movt	r6, #:upper16:.LC2
.L43:
	sub	r4, r5, #40
.L44:
	ldrd	r2, [r4], #8
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r5
	bne	.L44
	mov	r0, #10
	add	r5, r4, #40
	bl	putchar
	ldr	r3, .L59
	cmp	r5, r3
	bne	.L43
	ldrd	r4, [fp, #40]
	movw	r6, #:lower16:.LC2
	ldrd	r8, [fp, #80]
	movt	r6, #:upper16:.LC2
	mov	r0, r4
	mov	r1, r5
	mov	r2, r8
	mov	r3, r9
	bl	__aeabi_ddiv
	mov	r2, r0
	mov	r3, r1
	mov	r0, r8
	mov	r1, r9
	mov	r8, r2
	mov	r9, r3
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_dsub
	ldrd	r2, [fp, #88]
	strd	r8, [sp]
	mov	r4, r0
	mov	r5, r1
	mov	r0, r8
	mov	r1, r9
	strd	r4, [fp, #40]
	mov	r4, r10
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #48]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #96]
	mov	r8, r0
	mov	r9, r1
	ldrd	r0, [sp]
	strd	r8, [fp, #48]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #56]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #104]
	mov	r8, r0
	mov	r9, r1
	ldrd	r0, [sp]
	strd	r8, [fp, #56]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #64]
	bl	__aeabi_dsub
	ldrd	r2, [fp, #112]
	mov	r8, r0
	mov	r9, r1
	ldrd	r0, [sp]
	strd	r8, [fp, #64]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #72]
	bl	__aeabi_dsub
	mov	r2, #5
	mov	r8, r0
	mov	r9, r1
	mov	r0, #1
	movw	r1, #:lower16:.LC1
	movt	r1, #:upper16:.LC1
	strd	r8, [fp, #72]
	bl	__printf_chk
.L46:
	sub	r5, r4, #40
.L47:
	ldrd	r2, [r5], #8
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r5, r4
	bne	.L47
	mov	r0, #10
	add	r4, r5, #40
	bl	putchar
	ldr	r3, .L59
	cmp	r4, r3
	bne	.L46
	ldr	lr, [fp, #92]
	movw	ip, #:lower16:TempState
	ldr	r5, [fp, #88]
	movt	ip, #:upper16:TempState
	ldr	r6, [fp, #104]
	add	lr, lr, #-2147483648
	ldr	r3, [fp, #100]
	mov	r0, r5
	mov	r1, lr
	add	r3, r3, #-2147483648
	strd	r0, [ip, #8]
	str	r3, [sp, #12]
	mov	r2, r5
	ldrd	r0, [fp, #112]
	mov	r3, lr
	str	r6, [sp, #16]
	ldr	r5, [fp, #96]
	ldr	r6, [sp, #16]
	ldr	r9, [sp, #12]
	strd	r0, [sp]
	mov	r8, r5
	ldr	r4, [fp, #108]
	mov	r0, r6
	strd	r8, [ip, #16]
	ldr	r1, [fp, #80]
	add	r4, r4, #-2147483648
	ldrd	r8, [fp]
	ldrd	r6, [sp]
	ldr	lr, [fp, #84]
	str	r1, [ip]
	mov	r1, r4
	add	lr, lr, #-2147483648
	strd	r0, [ip, #24]
	strd	r6, [ip, #32]
	mov	r0, r8
	str	lr, [ip, #4]
	mov	r1, r9
	bl	__aeabi_dmul
	ldrd	r6, [fp, #32]
	ldr	r2, [sp, #16]
	mov	r3, r4
	strd	r6, [sp, #16]
	strd	r0, [fp, #8]
	mov	r0, r8
	mov	r1, r9
	bl	__aeabi_dmul
	ldrd	r2, [sp]
	ldrd	r6, [fp, #16]
	strd	r0, [fp, #24]
	mov	r0, r8
	mov	r1, r9
	bl	__aeabi_dmul
	mov	r2, r5
	ldr	r3, [sp, #12]
	mov	r4, r0
	mov	r5, r1
	mov	r0, r8
	mov	r1, r9
	strd	r4, [fp, #32]
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_dadd
	mov	r2, #0
	mov	r3, #0
	strd	r2, [fp]
	strd	r0, [fp, #16]
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	bne	.L49
	ldrd	r0, [sp, #16]
	mov	r2, r4
	mov	r3, r5
	bl	__aeabi_dadd
	strd	r0, [fp, #32]
.L49:
	movw	r1, #:lower16:.LC1
	mov	r2, #6
	movt	r1, #:upper16:.LC1
	mov	r0, #1
	bl	__printf_chk
	movw	r5, #:lower16:.LC2
	movt	r5, #:upper16:.LC2
.L51:
	sub	r4, r10, #40
.L52:
	ldrd	r2, [r4], #8
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r10, r4
	bne	.L52
	mov	r0, #10
	add	r10, r10, #40
	bl	putchar
	ldr	r3, .L59
	cmp	r10, r3
	bne	.L51
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L60:
	.align	2
.L59:
	.word	SimplexTable+160
	.size	X1Calc, .-X1Calc
	.section	.rodata.str1.4
	.align	2
.LC3:
	.ascii	"\012***** Result *****\000"
	.align	2
.LC4:
	.ascii	"x1 = %lf, \000"
	.align	2
.LC5:
	.ascii	"x2 = %lf, \000"
	.align	2
.LC6:
	.ascii	"f = %lf\012\000"
	.text
	.align	2
	.global	Result
	.syntax unified
	.arm
	.fpu softvfp
	.type	Result, %function
Result:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, lr}
	movw	r5, #:lower16:SimplexTable
	movt	r5, #:upper16:SimplexTable
	sub	sp, sp, #28
	mov	r2, #0
	mov	r3, #0
	ldrd	r0, [r5, #40]
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	ldrd	r6, [r5, #72]
	subs	r4, r0, #0
	movne	r4, #1
	strdne	r6, [sp]
.L62:
	ldrd	r0, [r5, #48]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r6, [r3, #-24]
.L64:
	ldrd	r0, [r5, #56]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r6, [r3, #-24]
.L66:
	ldrd	r0, [r5, #64]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r6, [r3, #-24]
.L68:
	mov	r9, #0
	movt	r9, 16368
	mov	r8, #0
	mov	r0, r6
	mov	r1, r7
	mov	r2, r8
	mov	r3, r9
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	bne	.L95
.L70:
	ldrd	r0, [r5, #80]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	ldrd	r6, [r5, #112]
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r6, [r3, #-24]
.L72:
	ldrd	r0, [r5, #88]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r6, [r3, #-24]
.L74:
	ldrd	r0, [r5, #96]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r6, [r3, #-24]
.L76:
	ldrd	r0, [r5, #104]
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r6, [r3, #-24]
.L78:
	mov	r9, #0
	movt	r9, 16368
	mov	r8, #0
	mov	r0, r6
	mov	r1, r7
	mov	r2, r8
	mov	r3, r9
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	addne	r3, sp, #24
	addne	r3, r3, r4, lsl #3
	addne	r4, r4, #1
	strdne	r8, [r3, #-24]
.L80:
	ldrd	r2, [r5, #32]
	add	r1, sp, #24
	add	r4, r1, r4, lsl #3
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	strd	r2, [r4, #-24]
	bl	puts
	ldrd	r2, [sp]
	movw	r1, #:lower16:.LC4
	mov	r0, #1
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
	ldrd	r2, [sp, #8]
	movw	r1, #:lower16:.LC5
	mov	r0, #1
	movt	r1, #:upper16:.LC5
	bl	__printf_chk
	ldrd	r2, [sp, #16]
	movw	r1, #:lower16:.LC6
	mov	r0, #1
	movt	r1, #:upper16:.LC6
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, lr}
	b	__printf_chk
.L95:
	add	r3, sp, #24
	add	r3, r3, r4, lsl #3
	add	r4, r4, #1
	strd	r8, [r3, #-24]
	b	.L70
	.size	Result, .-Result
	.align	2
	.global	Maxim
	.syntax unified
	.arm
	.fpu softvfp
	.type	Maxim, %function
Maxim:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	movw	r4, #:lower16:SimplexTable
	movt	r4, #:upper16:SimplexTable
	sub	sp, sp, #16
	lsl	r10, r1, #3
	cmp	r0, #1
	ldrd	r2, [r4, #32]
	movw	r5, #:lower16:TempState
	ldrd	r6, [r4, r10]
	movt	r5, #:upper16:TempState
	strd	r2, [sp]
	beq	.L103
	mov	r2, r6
	mov	r3, r7
	ldrd	r0, [r5]
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	strd	r0, [r4]
	ldrd	r0, [r5, #8]
	bl	__aeabi_dmul
	ldrd	r2, [r5, #16]
	mov	r8, r0
	mov	r9, r1
	mov	r0, r6
	strd	r8, [r4, #8]
	mov	r1, r7
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	mov	r8, r0
	mov	r9, r1
	ldrd	r0, [r5, #24]
	bl	__aeabi_dmul
	ldrd	r2, [r4, #16]
	strd	r2, [sp, #8]
	mov	r2, r6
	mov	r3, r7
	strd	r0, [r4, #24]
	ldrd	r0, [r5, #32]
	bl	__aeabi_dmul
	mov	r2, r8
	mov	r3, r9
	strd	r0, [r4, #32]
	ldrd	r0, [sp, #8]
	bl	__aeabi_dadd
	mov	r2, #0
	mov	r3, #0
	strd	r0, [r4, #16]
	strd	r2, [r4, r10]
.L98:
	ldrd	r6, [r4, #32]
	mov	r2, #0
	mov	r3, #0
	mov	r0, r6
	mov	r1, r7
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	bne	.L96
	ldrd	r2, [sp]
	mov	r0, r6
	mov	r1, r7
	bl	__aeabi_dadd
	strd	r0, [r4, #32]
.L96:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L103:
	ldrd	r2, [r5]
	mov	r0, r6
	mov	r1, r7
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	mov	r8, r0
	mov	r9, r1
	ldrd	r0, [r5, #8]
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	strd	r0, [r4, #8]
	ldrd	r0, [r5, #16]
	bl	__aeabi_dmul
	mov	r2, r6
	mov	r3, r7
	strd	r0, [r4, #16]
	ldrd	r0, [r5, #24]
	bl	__aeabi_dmul
	ldrd	r2, [r4]
	strd	r2, [sp, #8]
	mov	r2, r6
	mov	r3, r7
	strd	r0, [r4, #24]
	ldrd	r0, [r5, #32]
	bl	__aeabi_dmul
	mov	r2, r8
	mov	r3, r9
	strd	r0, [r4, #32]
	ldrd	r0, [sp, #8]
	bl	__aeabi_dadd
	mov	r2, #0
	mov	r3, #0
	strd	r0, [r4]
	strd	r2, [r4, r10]
	b	.L98
	.size	Maxim, .-Maxim
	.align	2
	.global	GaussCalc
	.syntax unified
	.arm
	.fpu softvfp
	.type	GaussCalc, %function
GaussCalc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	movw	r4, #:lower16:SimplexTable
	movt	r4, #:upper16:SimplexTable
	cmp	r0, #1
	add	r2, r4, r1, lsl #3
	ldrd	r6, [r2, #40]
	beq	.L108
	add	ip, r0, r0, lsl #2
	mov	r3, r1
	add	r3, ip, r3
	mov	r5, r0
	mov	r1, r7
	mov	r0, r6
	lsl	r3, r3, #3
	ldrd	r2, [r3, r4]
	bl	__aeabi_ddiv
	mov	r3, #40
	mul	r5, r3, r5
	add	r8, r4, r5
	ldrd	r2, [r4, r5]
	mov	r6, r0
	mov	r7, r1
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #40]
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r6
	strd	r2, [r4, #40]
	mov	r1, r7
	ldrd	r2, [r8, #8]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #48]
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r6
	strd	r2, [r4, #48]
	mov	r1, r7
	ldrd	r2, [r8, #16]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #56]
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r6
	strd	r2, [r4, #56]
	mov	r1, r7
	ldrd	r2, [r8, #24]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #64]
	bl	__aeabi_dsub
	mov	r2, r0
	mov	r3, r1
	mov	r0, r6
	strd	r2, [r4, #64]
	mov	r1, r7
	ldrd	r2, [r8, #32]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #72]
	bl	__aeabi_dsub
	strd	r0, [r4, #72]
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L108:
	mov	r1, r2
	mov	r3, r7
	ldrd	r0, [r1, #80]
	mov	r2, r6
	bl	__aeabi_ddiv
	ldrd	r2, [r4, #40]
	mov	r6, r0
	mov	r7, r1
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #80]
	bl	__aeabi_dsub
	ldrd	r2, [r4, #48]
	mov	r8, r0
	mov	r9, r1
	mov	r0, r6
	strd	r8, [r4, #80]
	mov	r1, r7
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #88]
	bl	__aeabi_dsub
	ldrd	r2, [r4, #56]
	mov	r8, r0
	mov	r9, r1
	mov	r0, r6
	strd	r8, [r4, #88]
	mov	r1, r7
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #96]
	bl	__aeabi_dsub
	ldrd	r2, [r4, #64]
	mov	r8, r0
	mov	r9, r1
	mov	r0, r6
	strd	r8, [r4, #96]
	mov	r1, r7
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #104]
	bl	__aeabi_dsub
	ldrd	r2, [r4, #72]
	mov	r8, r0
	mov	r9, r1
	mov	r0, r6
	mov	r1, r7
	strd	r8, [r4, #104]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [r4, #112]
	bl	__aeabi_dsub
	strd	r0, [r4, #112]
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	GaussCalc, .-GaussCalc
	.align	2
	.global	Exchange
	.syntax unified
	.arm
	.fpu softvfp
	.type	Exchange, %function
Exchange:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r0, #1
	movw	r2, #:lower16:SimplexTable
	movw	r3, #:lower16:TempState
	movt	r2, #:upper16:SimplexTable
	movt	r3, #:upper16:TempState
	push	{r4, r5, lr}
	beq	.L114
	ldr	r0, [r2, #88]
	ldr	r4, [r2, #80]
	ldr	r1, [r2, #84]
	str	r0, [r3, #8]
	ldr	r0, [r2, #92]
	add	r1, r1, #-2147483648
	ldr	lr, [r2, #96]
	ldr	ip, [r2, #104]
	add	r0, r0, #-2147483648
	str	r4, [r3]
	str	r1, [r3, #4]
	ldrd	r4, [r2, #112]
	ldr	r1, [r2, #100]
	ldr	r2, [r2, #108]
	str	lr, [r3, #16]
	str	ip, [r3, #24]
.L113:
	add	r1, r1, #-2147483648
	add	r2, r2, #-2147483648
	str	r0, [r3, #12]
	str	r1, [r3, #20]
	str	r2, [r3, #28]
	strd	r4, [r3, #32]
	pop	{r4, r5, pc}
.L114:
	ldr	r0, [r2, #48]
	ldr	r4, [r2, #40]
	ldr	lr, [r2, #56]
	ldr	ip, [r2, #64]
	ldr	r1, [r2, #44]
	str	r0, [r3, #8]
	ldr	r0, [r2, #52]
	add	r1, r1, #-2147483648
	str	r4, [r3]
	str	r1, [r3, #4]
	add	r0, r0, #-2147483648
	ldrd	r4, [r2, #72]
	ldr	r1, [r2, #60]
	str	lr, [r3, #16]
	ldr	r2, [r2, #68]
	str	ip, [r3, #24]
	b	.L113
	.size	Exchange, .-Exchange
	.align	2
	.global	ShowTable
	.syntax unified
	.arm
	.fpu softvfp
	.type	ShowTable, %function
ShowTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r2, r0
	movw	r1, #:lower16:.LC1
	mov	r0, #1
	movt	r1, #:upper16:.LC1
	ldr	r5, .L121
	bl	__printf_chk
	movw	r6, #:lower16:.LC2
	add	r7, r5, #120
	movt	r6, #:upper16:.LC2
.L116:
	sub	r4, r5, #40
.L117:
	ldrd	r2, [r4], #8
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r5
	bne	.L117
	add	r5, r4, #40
	mov	r0, #10
	bl	putchar
	cmp	r5, r7
	bne	.L116
	pop	{r4, r5, r6, r7, r8, pc}
.L122:
	.align	2
.L121:
	.word	SimplexTable+40
	.size	ShowTable, .-ShowTable
	.align	2
	.global	Input
	.syntax unified
	.arm
	.fpu softvfp
	.type	Input, %function
Input:
	@ args = 0, pretend = 0, frame = 120
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, lr}
	sub	sp, sp, #124
	mov	r2, #120
	movw	r1, #:lower16:.LANCHOR0
	mov	r0, sp
	movt	r1, #:upper16:.LANCHOR0
	bl	memcpy
	ldrd	r4, [sp, #16]
	movw	ip, #:lower16:SimplexTable
	movt	ip, #:upper16:SimplexTable
	ldrd	r6, [sp, #24]
	add	r8, ip, #40
	strd	r4, [ip, #16]
	add	r9, ip, #160
	ldrd	r4, [sp, #32]
	strd	r6, [ip, #24]
	ldrd	r6, [sp, #48]
	strd	r4, [ip, #32]
	ldrd	r4, [sp, #40]
	strd	r6, [ip, #48]
	ldrd	r6, [sp, #64]
	strd	r4, [ip, #40]
	ldrd	r4, [sp, #56]
	strd	r6, [ip, #64]
	ldrd	r6, [sp, #80]
	strd	r4, [ip, #56]
	ldrd	r4, [sp, #72]
	strd	r6, [ip, #80]
	ldrd	r6, [sp, #96]
	strd	r4, [ip, #72]
	ldrd	r4, [sp, #88]
	ldrd	r0, [sp]
	ldrd	r2, [sp, #8]
	strd	r4, [ip, #88]
	strd	r6, [ip, #96]
	ldrd	r4, [sp, #104]
	ldrd	r6, [sp, #112]
	strd	r0, [ip]
	movw	r1, #:lower16:.LC1
	strd	r2, [ip, #8]
	movt	r1, #:upper16:.LC1
	mov	r2, #0
	mov	r0, #1
	strd	r4, [ip, #104]
	movw	r5, #:lower16:.LC2
	strd	r6, [ip, #112]
	bl	__printf_chk
	movt	r5, #:upper16:.LC2
.L124:
	sub	r4, r8, #40
.L125:
	ldrd	r2, [r4], #8
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r8
	bne	.L125
	add	r8, r4, #40
	mov	r0, #10
	bl	putchar
	cmp	r8, r9
	bne	.L124
	add	sp, sp, #124
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, pc}
	.size	Input, .-Input
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
	bl	Input
	bl	X2Calc
	bl	X1Calc
	bl	Result
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.comm	TempState,40,8
	.comm	SimplexTable,120,8
	.section	.rodata
	.align	3
	.set	.LANCHOR0,. + 0
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
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
