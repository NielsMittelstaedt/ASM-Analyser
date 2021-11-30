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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"../test_files/c_in/simplex.c\000"
	.align	2
.LC1:
	.ascii	"tab->mat[i][0] >= 0\000"
	.text
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	check_b_positive.part.0, %function
check_b_positive.part.0:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #:lower16:.LANCHOR0
	movw	r1, #:lower16:.LC0
	movw	r0, #:lower16:.LC1
	movt	r3, #:upper16:.LANCHOR0
	movt	r1, #:upper16:.LC0
	movt	r0, #:upper16:.LC1
	mov	r2, #155
	push	{r4, lr}
	bl	__assert_fail
	.size	check_b_positive.part.0, .-check_b_positive.part.0
	.global	__aeabi_dsub
	.global	__aeabi_dcmplt
	.align	2
	.global	equal
	.syntax unified
	.arm
	.fpu softvfp
	.type	equal, %function
equal:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	bl	__aeabi_dsub
	movw	r2, #35898
	movw	r3, #31118
	movt	r2, 57904
	movt	r3, 15941
	bic	r5, r1, #-2147483648
	mov	r4, r0
	mov	r1, r5
	bl	__aeabi_dcmplt
	subs	r0, r0, #0
	movne	r0, #1
	pop	{r4, r5, r6, pc}
	.size	equal, .-equal
	.align	2
	.global	nl
	.syntax unified
	.arm
	.fpu softvfp
	.type	nl, %function
nl:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r5, r0, #0
	movw	r6, #:lower16:stdout
	movt	r6, #:upper16:stdout
	movgt	r4, #0
	ble	.L8
.L9:
	ldr	r1, [r6]
	add	r4, r4, #1
	mov	r0, #45
	bl	putc
	cmp	r5, r4
	bne	.L9
.L8:
	ldr	r1, [r6]
	mov	r0, #10
	pop	{r4, r5, r6, lr}
	b	putc
	.size	nl, .-nl
	.section	.rodata.str1.4
	.align	2
.LC2:
	.ascii	"\012%d. Tableau %s:\012\000"
	.align	2
.LC3:
	.ascii	"b[i]\000"
	.align	2
.LC4:
	.ascii	"col:\000"
	.align	2
.LC5:
	.ascii	"%-6s%5s\000"
	.align	2
.LC6:
	.ascii	"    x%d,\000"
	.align	2
.LC7:
	.ascii	"max:\000"
	.align	2
.LC8:
	.ascii	"b%d: \000"
	.global	__aeabi_d2iz
	.global	__aeabi_i2d
	.align	2
.LC9:
	.ascii	" %6d\000"
	.align	2
.LC10:
	.ascii	" %6.2lf\000"
	.text
	.align	2
	.global	print_tableau
	.syntax unified
	.arm
	.fpu softvfp
	.type	print_tableau, %function
print_tableau:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:.LANCHOR1
	movt	ip, #:upper16:.LANCHOR1
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r3, r1
	ldr	r2, [ip]
	sub	sp, sp, #20
	mov	r9, r0
	movw	r1, #:lower16:.LC2
	add	r2, r2, #1
	movt	r1, #:upper16:.LC2
	mov	r0, #1
	str	r2, [ip]
	bl	__printf_chk
	mov	r0, #70
	bl	nl
	movw	r3, #:lower16:.LC3
	movw	r2, #:lower16:.LC4
	movt	r3, #:upper16:.LC3
	movt	r2, #:upper16:.LC4
	movw	r1, #:lower16:.LC5
	mov	r0, #1
	movt	r1, #:upper16:.LC5
	bl	__printf_chk
	ldr	r3, [r9, #4]
	cmp	r3, #1
	ble	.L15
	movw	r5, #:lower16:.LC6
	movt	r5, #:upper16:.LC6
	mov	r4, #1
.L16:
	mov	r2, r4
	mov	r0, #1
	mov	r1, r5
	add	r4, r4, r0
	bl	__printf_chk
	ldr	r3, [r9, #4]
	cmp	r3, r4
	bgt	.L16
.L15:
	mov	r0, #10
	bl	putchar
	ldr	r3, [r9]
	cmp	r3, #0
	ble	.L17
	movw	r3, #:lower16:.LC8
	movw	r2, #:lower16:.LC7
	movt	r3, #:upper16:.LC8
	movt	r2, #:upper16:.LC7
	str	r3, [sp, #8]
	add	r3, r9, #8
	str	r2, [sp, #12]
	str	r3, [sp, #4]
	mov	r3, #0
	str	r3, [sp]
.L25:
	ldr	r3, [sp]
	cmp	r3, #0
	bne	.L18
	ldr	r1, [sp, #12]
	mov	r0, #1
	bl	__printf_chk
.L21:
	ldr	r3, [r9, #4]
	cmp	r3, #0
	ble	.L20
	movw	r10, #:lower16:.LC10
	movw	fp, #:lower16:.LC9
	ldr	r8, [sp, #4]
	movt	r10, #:upper16:.LC10
	movt	fp, #:upper16:.LC9
	mov	r7, #0
	b	.L19
.L33:
	mov	r2, r6
	mov	r1, fp
	bl	__printf_chk
	ldr	r3, [r9, #4]
	add	r7, r7, #1
	cmp	r3, r7
	ble	.L20
.L19:
	ldrd	r4, [r8], #8
	mov	r1, r5
	mov	r0, r4
	bl	__aeabi_d2iz
	mov	r6, r0
	bl	__aeabi_i2d
	mov	r2, r4
	mov	r3, r5
	bl	__aeabi_dsub
	movw	r2, #35898
	movw	r3, #31118
	movt	r2, 57904
	movt	r3, 15941
	mov	ip, r0
	mov	lr, r1
	mov	r0, ip
	bic	r1, lr, #-2147483648
	bl	__aeabi_dcmplt
	mov	r2, r4
	mov	r3, r5
	mov	r1, r10
	mov	ip, r0
	cmp	ip, #0
	mov	r0, #1
	bne	.L33
	bl	__printf_chk
	ldr	r3, [r9, #4]
	add	r7, r7, #1
	cmp	r3, r7
	bgt	.L19
.L20:
	ldr	r3, [sp]
	mov	r0, #10
	add	r4, r3, #1
	str	r4, [sp]
	bl	putchar
	ldr	r3, [r9]
	ldr	r2, [sp, #4]
	cmp	r3, r4
	add	r2, r2, #160
	str	r2, [sp, #4]
	bgt	.L25
.L17:
	mov	r0, #70
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	nl
.L18:
	ldr	r2, [sp]
	mov	r0, #1
	ldr	r1, [sp, #8]
	bl	__printf_chk
	b	.L21
	.size	print_tableau, .-print_tableau
	.global	__aeabi_dcmpgt
	.section	.rodata.str1.4
	.align	2
.LC11:
	.ascii	"pivot>0\000"
	.global	__aeabi_ddiv
	.align	2
.LC12:
	.ascii	"equal(tab->mat[row][col], 1. )\000"
	.global	__aeabi_dmul
	.text
	.align	2
	.global	pivot_on
	.syntax unified
	.arm
	.fpu softvfp
	.type	pivot_on, %function
pivot_on:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r5, #20
	mul	r5, r5, r1
	mov	r9, r2
	sub	sp, sp, #28
	mov	r2, #0
	mov	r3, #0
	mov	r8, r0
	add	r10, r9, r5
	str	r1, [sp]
	add	r10, r0, r10, lsl #3
	ldrd	r6, [r10, #8]
	mov	r0, r6
	mov	r1, r7
	bl	__aeabi_dcmpgt
	cmp	r0, #0
	beq	.L53
	ldr	r3, [r8, #4]
	cmp	r3, #0
	str	r3, [sp, #8]
	ble	.L38
	ldr	r3, [sp, #8]
	mov	r4, #160
	add	r5, r3, r5
	ldr	r3, [sp]
	mla	r4, r4, r3, r8
	add	r3, r8, #8
	add	r5, r3, r5, lsl #3
	add	r4, r4, #8
.L39:
	ldrd	r0, [r4]
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_ddiv
	strd	r0, [r4], #8
	cmp	r4, r5
	bne	.L39
	ldrd	r6, [r10, #8]
.L38:
	mov	r2, #0
	mov	r0, r6
	mov	r1, r7
	mov	r3, #0
	movt	r3, 16368
	bl	__aeabi_dsub
	movw	r2, #35898
	movw	r3, #31118
	movt	r2, 57904
	movt	r3, 15941
	bic	r5, r1, #-2147483648
	mov	r1, r5
	bl	__aeabi_dcmplt
	cmp	r0, #0
	beq	.L54
	ldr	r3, [r8]
	cmp	r3, #0
	str	r3, [sp, #4]
	ble	.L34
	ldr	r2, [sp]
	mov	r3, #160
	add	r10, r8, #8
	mov	fp, #0
	mla	r8, r3, r2, r8
	ldr	r3, [sp, #8]
	lsl	r2, r9, #3
	str	r2, [sp, #16]
	lsl	r3, r3, #3
	add	r10, r10, r3
	rsb	r3, r3, #0
	str	r3, [sp, #20]
	add	r3, r8, #8
	str	r3, [sp, #12]
.L44:
	ldr	r3, [sp]
	cmp	r3, fp
	beq	.L46
	ldr	r3, [sp, #8]
	cmp	r3, #0
	ble	.L46
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #20]
	add	r3, r10, r3
	ldr	r5, [sp, #12]
	add	r4, r10, r2
	ldrd	r8, [r3, r2]
.L47:
	ldrd	r0, [r5], #8
	mov	r2, r8
	mov	r3, r9
	ldrd	r6, [r4]
	bl	__aeabi_dmul
	mov	r2, r0
	mov	r3, r1
	mov	r0, r6
	mov	r1, r7
	bl	__aeabi_dsub
	strd	r0, [r4], #8
	cmp	r4, r10
	bne	.L47
.L46:
	ldr	r3, [sp, #4]
	add	fp, fp, #1
	add	r10, r10, #160
	cmp	fp, r3
	bne	.L44
.L34:
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L53:
	movw	r1, #:lower16:.LC0
	movw	r0, #:lower16:.LC11
	ldr	r3, .L56
	movt	r1, #:upper16:.LC0
	movt	r0, #:upper16:.LC11
	mov	r2, #91
	bl	__assert_fail
.L54:
	movw	r1, #:lower16:.LC0
	movw	r0, #:lower16:.LC12
	ldr	r3, .L56
	movt	r1, #:upper16:.LC0
	movt	r0, #:upper16:.LC12
	mov	r2, #94
	bl	__assert_fail
.L57:
	.align	2
.L56:
	.word	.LANCHOR0+20
	.size	pivot_on, .-pivot_on
	.section	.rodata.str1.4
	.align	2
.LC13:
	.ascii	"Most negative column in row[0] is col %d = %g.\012\000"
	.global	__aeabi_dcmpge
	.text
	.align	2
	.global	find_pivot_column
	.syntax unified
	.arm
	.fpu softvfp
	.type	find_pivot_column, %function
find_pivot_column:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #12
	ldr	r10, [r0, #4]
	ldrd	r8, [r0, #16]
	cmp	r10, #1
	ble	.L66
	mov	r4, #1
	add	r5, r0, #16
	mov	fp, r4
	b	.L60
.L63:
	ldrd	r6, [r5, #8]!
	mov	r0, r6
	mov	r1, r7
	bl	__aeabi_dcmplt
	cmp	r0, #0
	movne	r8, r6
	movne	r9, r7
	movne	fp, r4
.L60:
	add	r4, r4, #1
	mov	r2, r8
	cmp	r4, r10
	mov	r3, r9
	bne	.L63
.L59:
	mov	r2, fp
	strd	r8, [sp]
	movw	r1, #:lower16:.LC13
	mov	r0, #1
	movt	r1, #:upper16:.LC13
	bl	__printf_chk
	mov	r0, r8
	mov	r1, r9
	mov	r2, #0
	mov	r3, #0
	bl	__aeabi_dcmpge
	cmp	r0, #0
	moveq	r0, fp
	mvnne	r0, #0
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L66:
	mov	fp, #1
	b	.L59
	.size	find_pivot_column, .-find_pivot_column
	.section	.rodata.str1.4
	.align	2
.LC14:
	.ascii	"Ratios A[row_i,0]/A[row_i,%d] = [\000"
	.align	2
.LC15:
	.ascii	"%3.2lf, \000"
	.align	2
.LC16:
	.ascii	"].\000"
	.global	__aeabi_dcmpeq
	.align	2
.LC17:
	.ascii	"Found pivot A[%d,%d], min positive ratio=%g in row="
	.ascii	"%d.\012\000"
	.text
	.align	2
	.global	find_pivot_row
	.syntax unified
	.arm
	.fpu softvfp
	.type	find_pivot_row, %function
find_pivot_row:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #36
	mov	r8, r0
	mov	r2, r1
	str	r1, [sp, #28]
	mov	r4, r1
	mov	r0, #1
	movw	r1, #:lower16:.LC14
	movt	r1, #:upper16:.LC14
	bl	__printf_chk
	ldr	r3, [r8]
	cmp	r3, #1
	ble	.L71
	movw	r9, #:lower16:.LC15
	movt	r9, #:upper16:.LC15
	lsl	r3, r4, #3
	mov	fp, #0
	add	r3, r3, #168
	str	r3, [sp, #20]
	mov	r3, #0
	str	r3, [sp, #24]
	mov	r3, r9
	mov	r6, r8
	mov	r9, r8
	movt	fp, 49136
	mov	r10, #0
	mov	r7, #1
	mov	r8, r3
	b	.L75
.L85:
	bl	__aeabi_dcmplt
	cmp	r0, #0
	beq	.L72
.L78:
	mov	r10, r4
	mov	fp, r5
	str	r7, [sp, #24]
.L74:
	ldr	r3, [r9]
	add	r7, r7, #1
	add	r6, r6, #160
	cmp	r3, r7
	ble	.L84
.L75:
	ldr	r3, [sp, #20]
	ldrd	r0, [r6, #168]
	ldrd	r2, [r3, r6]
	bl	__aeabi_ddiv
	mov	r4, r0
	mov	r5, r1
	mov	r2, r4
	mov	r1, r8
	mov	r3, r5
	mov	r0, #1
	bl	__printf_chk
	mov	r2, #0
	mov	r3, #0
	mov	r1, r5
	mov	r0, r4
	bl	__aeabi_dcmpgt
	mov	r2, r10
	mov	r3, fp
	mov	r1, r5
	mov	ip, r0
	cmp	ip, #0
	mov	r0, r4
	bne	.L85
.L72:
	mov	r2, #0
	mov	r3, #0
	mov	r0, r10
	mov	r1, fp
	bl	__aeabi_dcmplt
	cmp	r0, #0
	beq	.L74
	b	.L78
.L84:
	movw	r0, #:lower16:.LC16
	movt	r0, #:upper16:.LC16
	bl	puts
	mov	r2, #0
	mov	r3, #0
	mov	r0, r10
	movt	r3, 49136
	mov	r1, fp
	bl	__aeabi_dcmpeq
	cmp	r0, #0
	bne	.L83
	ldr	r2, [sp, #24]
	movw	r1, #:lower16:.LC17
	ldr	r3, [sp, #28]
	movt	r1, #:upper16:.LC17
	mov	r0, #1
	strd	r10, [sp]
	str	r2, [sp, #8]
	bl	__printf_chk
.L70:
	ldr	r0, [sp, #24]
	add	sp, sp, #36
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L71:
	movw	r0, #:lower16:.LC16
	movt	r0, #:upper16:.LC16
	bl	puts
.L83:
	mvn	r3, #0
	str	r3, [sp, #24]
	b	.L70
	.size	find_pivot_row, .-find_pivot_row
	.align	2
	.global	add_slack_variables
	.syntax unified
	.arm
	.fpu softvfp
	.type	add_slack_variables, %function
add_slack_variables:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	ip, [r0]
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	cmp	ip, #1
	ldr	r10, [r0, #4]
	ble	.L91
	add	lr, r0, r10, lsl #3
	mov	r9, #0
	add	lr, lr, #160
	movt	r9, 16368
	mov	r8, #0
	mov	r6, #0
	mov	r7, #0
	mov	r1, #1
.L90:
	mov	r2, lr
	mov	r3, #1
.L89:
	cmp	r1, r3
	add	r3, r3, #1
	mov	r4, r6
	mov	r5, r7
	moveq	r4, r8
	moveq	r5, r9
	cmp	r3, ip
	strd	r4, [r2, #8]!
	bne	.L89
	add	r1, r1, #1
	add	lr, lr, #160
	cmp	r1, ip
	bne	.L90
.L91:
	sub	ip, ip, #1
	add	r10, ip, r10
	str	r10, [r0, #4]
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	add_slack_variables, .-add_slack_variables
	.align	2
	.global	check_b_positive
	.syntax unified
	.arm
	.fpu softvfp
	.type	check_b_positive, %function
check_b_positive:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	ldr	r8, [r0]
	cmp	r8, #1
	pople	{r4, r5, r6, r7, r8, pc}
	mov	r4, r0
	mov	r6, #0
	mov	r7, #0
	mov	r5, #1
	b	.L100
.L99:
	add	r5, r5, #1
	add	r4, r4, #160
	cmp	r5, r8
	popeq	{r4, r5, r6, r7, r8, pc}
.L100:
	ldrd	r0, [r4, #168]
	mov	r2, r6
	mov	r3, r7
	bl	__aeabi_dcmpge
	cmp	r0, #0
	bne	.L99
	bl	check_b_positive.part.0
	.size	check_b_positive, .-check_b_positive
	.align	2
	.global	find_basis_variable
	.syntax unified
	.arm
	.fpu softvfp
	.type	find_basis_variable, %function
find_basis_variable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	ldr	fp, [r0]
	cmp	fp, #1
	ble	.L116
	movw	r6, #35898
	movw	r7, #31118
	movt	r6, 57904
	movt	r7, 15941
	add	r4, r0, r1, lsl #3
	mvn	r10, #0
	mov	r5, #1
	b	.L109
.L118:
	cmn	r10, #1
	mov	r10, r5
	bne	.L116
.L107:
	add	r5, r5, #1
	cmp	r5, fp
	beq	.L103
.L109:
	ldr	r8, [r4, #172]
	mov	r2, #0
	ldr	r9, [r4, #168]
	mov	r3, #0
	movt	r3, 16368
	add	r4, r4, #160
	mov	r1, r8
	mov	r0, r9
	bl	__aeabi_dsub
	movw	r2, #35898
	movw	r3, #31118
	movt	r2, 57904
	movt	r3, 15941
	bic	r1, r1, #-2147483648
	bl	__aeabi_dcmplt
	bic	r1, r8, #-2147483648
	mov	r2, r6
	mov	r3, r7
	mov	ip, r0
	cmp	ip, #0
	mov	r0, r9
	bne	.L118
	bl	__aeabi_dcmplt
	cmp	r0, #0
	bne	.L107
.L116:
	mvn	r10, #0
.L103:
	mov	r0, r10
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	find_basis_variable, .-find_basis_variable
	.section	.rodata.str1.4
	.align	2
.LC18:
	.ascii	"%s at \000"
	.align	2
.LC19:
	.ascii	"x%d=%3.2lf, \000"
	.align	2
.LC20:
	.ascii	"x%d=0, \000"
	.text
	.align	2
	.global	print_optimal_vector
	.syntax unified
	.arm
	.fpu softvfp
	.type	print_optimal_vector, %function
print_optimal_vector:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #28
	mov	r2, r1
	mov	r4, r0
	str	r0, [sp, #16]
	movw	r1, #:lower16:.LC18
	mov	r0, #1
	movt	r1, #:upper16:.LC18
	bl	__printf_chk
	ldr	r3, [r4, #4]
	cmp	r3, #1
	ble	.L121
	movw	r6, #35898
	movw	r7, #31118
	movt	r6, 57904
	movt	r7, 15941
	movw	r3, #:lower16:.LC20
	movt	r3, #:upper16:.LC20
	str	r3, [sp, #20]
	mov	r3, #1
	str	r3, [sp, #12]
.L120:
	ldr	r3, [sp, #16]
	ldr	fp, [r3]
	cmp	fp, #1
	ble	.L125
	ldrd	r2, [sp, #12]
	mvn	r10, #0
	mov	r5, #1
	add	r4, r3, r2, lsl #3
	b	.L127
.L140:
	cmn	r10, #1
	mov	r10, r5
	bne	.L125
.L124:
	add	r5, r5, #1
	cmp	r5, fp
	beq	.L139
.L127:
	ldr	r8, [r4, #172]
	mov	r2, #0
	ldr	r9, [r4, #168]
	mov	r3, #0
	movt	r3, 16368
	add	r4, r4, #160
	mov	r1, r8
	mov	r0, r9
	bl	__aeabi_dsub
	mov	r2, r6
	mov	r3, r7
	bic	r1, r1, #-2147483648
	bl	__aeabi_dcmplt
	bic	r1, r8, #-2147483648
	mov	r2, r6
	mov	r3, r7
	mov	ip, r0
	cmp	ip, #0
	mov	r0, r9
	bne	.L140
	bl	__aeabi_dcmplt
	cmp	r0, #0
	bne	.L124
.L125:
	ldr	r2, [sp, #12]
	mov	r0, #1
	ldr	r1, [sp, #20]
	bl	__printf_chk
.L128:
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #12]
	ldr	r3, [r3, #4]
	add	r2, r2, #1
	str	r2, [sp, #12]
	cmp	r3, r2
	bgt	.L120
.L121:
	mov	r0, #10
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	putchar
.L139:
	cmn	r10, #1
	beq	.L125
	ldr	r2, [sp, #16]
	mov	r3, #160
	movw	r1, #:lower16:.LC19
	mov	r0, #1
	movt	r1, #:upper16:.LC19
	mla	r10, r3, r10, r2
	ldr	r2, [sp, #12]
	ldrd	r4, [r10, #8]
	strd	r4, [sp]
	bl	__printf_chk
	b	.L128
	.size	print_optimal_vector, .-print_optimal_vector
	.section	.rodata.str1.4
	.align	2
.LC21:
	.ascii	"Padded with slack variables\000"
	.align	2
.LC22:
	.ascii	"Found optimal value=A[0,0]=%3.2lf (no negatives in "
	.ascii	"row 0).\012\000"
	.align	2
.LC23:
	.ascii	"Optimal vector\000"
	.align	2
.LC24:
	.ascii	"Entering variable x%d to be made basic, so pivot_co"
	.ascii	"l=%d.\012\000"
	.align	2
.LC25:
	.ascii	"unbounded (no pivot_row).\000"
	.align	2
.LC26:
	.ascii	"Leaving variable x%d, so pivot_row=%d\012\000"
	.align	2
.LC27:
	.ascii	"After pivoting\000"
	.align	2
.LC28:
	.ascii	"Basic feasible solution\000"
	.align	2
.LC29:
	.ascii	"Too many iterations > %d.\012\000"
	.text
	.align	2
	.global	simplex
	.syntax unified
	.arm
	.fpu softvfp
	.type	simplex, %function
simplex:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r5, r0
	ldr	r4, [r0]
	ldr	r3, [r0, #4]
	cmp	r4, #1
	sub	r10, r4, #1
	add	r10, r10, r3
	ble	.L142
	add	r3, r0, r3, lsl #3
	mov	r1, #0
	add	r9, r3, #160
	movt	r1, 16368
	mov	r8, #1
	mov	r0, #0
	mov	r6, #0
	mov	r7, #0
.L143:
	mov	lr, r9
	mov	ip, #1
.L145:
	cmp	ip, r8
	add	ip, ip, #1
	movne	r2, r6
	movne	r3, r7
	moveq	r2, r0
	moveq	r3, r1
	cmp	ip, r4
	strd	r2, [lr, #8]!
	bne	.L145
	add	r8, r8, #1
	add	r9, r9, #160
	cmp	r8, r4
	bne	.L143
	mov	r6, r5
	mov	r7, #1
	mov	r8, #0
	mov	r9, #0
	str	r10, [r5, #4]
.L148:
	ldrd	r0, [r6, #168]
	mov	r2, r8
	mov	r3, r9
	bl	__aeabi_dcmpge
	cmp	r0, #0
	beq	.L160
	add	r7, r7, #1
	add	r6, r6, #160
	cmp	r7, r4
	bne	.L148
.L153:
	movw	r1, #:lower16:.LC21
	mov	r0, r5
	movt	r1, #:upper16:.LC21
	movw	r8, #:lower16:.LC24
	bl	print_tableau
	movw	r10, #:lower16:.LC26
	movw	r9, #:lower16:.LC27
	movt	r8, #:upper16:.LC24
	movt	r10, #:upper16:.LC26
	movt	r9, #:upper16:.LC27
	mov	r7, #21
.L149:
	mov	r0, r5
	bl	find_pivot_column
	subs	r4, r0, #0
	blt	.L161
	mov	r3, r4
	mov	r2, r4
	mov	r1, r8
	mov	r0, #1
	bl	__printf_chk
	mov	r1, r4
	mov	r0, r5
	bl	find_pivot_row
	subs	r6, r0, #0
	blt	.L162
	mov	r3, r6
	mov	r2, r6
	mov	r1, r10
	mov	r0, #1
	bl	__printf_chk
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	bl	pivot_on
	mov	r1, r9
	mov	r0, r5
	bl	print_tableau
	movw	r1, #:lower16:.LC28
	mov	r0, r5
	movt	r1, #:upper16:.LC28
	bl	print_optimal_vector
	subs	r7, r7, #1
	bne	.L149
	movw	r1, #:lower16:.LC29
	mov	r2, #21
	pop	{r4, r5, r6, r7, r8, r9, r10, lr}
	movt	r1, #:upper16:.LC29
	mov	r0, #1
	b	__printf_chk
.L161:
	ldrd	r2, [r5, #8]
	movw	r1, #:lower16:.LC22
	mov	r0, #1
	movt	r1, #:upper16:.LC22
	bl	__printf_chk
	mov	r0, r5
	movw	r1, #:lower16:.LC23
	movt	r1, #:upper16:.LC23
	pop	{r4, r5, r6, r7, r8, r9, r10, lr}
	b	print_optimal_vector
.L162:
	movw	r0, #:lower16:.LC25
	movt	r0, #:upper16:.LC25
	pop	{r4, r5, r6, r7, r8, r9, r10, lr}
	b	puts
.L142:
	str	r10, [r0, #4]
	b	.L153
.L160:
	bl	check_b_positive.part.0
	.size	simplex, .-simplex
	.section	.rodata.str1.4
	.align	2
.LC30:
	.ascii	"Initial\000"
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
	movw	r4, #:lower16:.LANCHOR2
	movt	r4, #:upper16:.LANCHOR2
	movw	r1, #:lower16:.LC30
	movt	r1, #:upper16:.LC30
	mov	r0, r4
	bl	print_tableau
	mov	r0, r4
	bl	simplex
	mov	r0, #0
	pop	{r4, pc}
	.size	main, .-main
	.global	tab
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
	.type	__PRETTY_FUNCTION__.6810, %object
	.size	__PRETTY_FUNCTION__.6810, 17
__PRETTY_FUNCTION__.6810:
	.ascii	"check_b_positive\000"
	.space	3
	.type	__PRETTY_FUNCTION__.6763, %object
	.size	__PRETTY_FUNCTION__.6763, 9
__PRETTY_FUNCTION__.6763:
	.ascii	"pivot_on\000"
	.data
	.align	3
	.set	.LANCHOR2,. + 0
	.type	tab, %object
	.size	tab, 3208
tab:
	.word	4
	.word	5
	.word	0
	.word	0
	.word	0
	.word	-1075838976
	.word	0
	.word	-1073217536
	.word	0
	.word	-1074790400
	.word	0
	.word	-1072693248
	.space	120
	.word	0
	.word	1078198272
	.word	0
	.word	1072693248
	.word	0
	.word	1072693248
	.word	0
	.word	1072693248
	.word	0
	.word	1072693248
	.space	120
	.word	0
	.word	1076101120
	.word	0
	.word	-1073741824
	.word	0
	.word	-1074790400
	.word	0
	.word	1072693248
	.word	0
	.word	1072693248
	.space	120
	.word	0
	.word	1076101120
	.word	0
	.word	0
	.word	0
	.word	1072693248
	.word	0
	.word	0
	.word	0
	.word	-1074790400
	.space	120
	.space	2560
	.bss
	.align	2
	.set	.LANCHOR1,. + 0
	.type	counter.6743, %object
	.size	counter.6743, 4
counter.6743:
	.space	4
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
