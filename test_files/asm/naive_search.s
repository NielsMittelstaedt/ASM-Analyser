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
	.file	"naive_search.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"--Pattern is found at: %d\012\000"
	.text
	.align	2
	.global	naive_search
	.syntax unified
	.arm
	.fpu softvfp
	.type	naive_search, %function
naive_search:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r4, r1
	mov	r8, r0
	bl	strlen
	mov	r5, r0
	mov	r0, r4
	bl	strlen
	subs	r5, r5, r0
	popmi	{r4, r5, r6, r7, r8, r9, r10, pc}
	movw	r9, #:lower16:.LC0
	sub	r8, r8, #1
	movt	r9, #:upper16:.LC0
	add	r7, r5, #1
	mov	r6, r0
	mov	r5, #0
.L3:
	cmp	r6, #0
	subne	ip, r4, #1
	addne	r2, r8, r5
	addne	lr, ip, r6
	bne	.L5
	b	.L7
.L12:
	cmp	ip, lr
	beq	.L11
.L5:
	mov	r3, ip
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	ldrb	r1, [ip, #1]!	@ zero_extendqisi2
	add	r3, r3, #2
	sub	r3, r3, r4
	cmp	r0, r1
	beq	.L12
.L4:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L3
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L11:
	cmp	r6, r3
	bne	.L4
.L7:
	mov	r2, r5
	mov	r1, r9
	mov	r0, #1
	bl	__printf_chk
	b	.L4
	.size	naive_search, .-naive_search
	.section	.rodata.str1.4
	.align	2
.LC3:
	.ascii	"moin\000"
	.align	2
.LC4:
	.ascii	"String test: %s\012\000"
	.align	2
.LC5:
	.ascii	"Test1: search pattern %s\012\000"
	.align	2
.LC6:
	.ascii	"Test2: search pattern %s\012\000"
	.align	2
.LC7:
	.ascii	"Test3: search pattern %s\012\000"
	.align	2
.LC1:
	.ascii	"AABCAB12AFAABCABFFEGABCAB\000"
	.align	2
.LC2:
	.ascii	"ABCAB\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	movw	lr, #:lower16:.LC1
	movt	lr, #:upper16:.LC1
	sub	sp, sp, #48
	add	ip, sp, #20
	movw	r4, #:lower16:.LC2
	ldmia	lr!, {r0, r1, r2, r3}
	movt	r4, #:upper16:.LC2
	stmia	ip!, {r0, r1, r2, r3}
	movw	r3, #17990
	ldm	lr, {r0, r1, r2}
	movt	r3, 70
	str	r3, [sp, #4]
	movw	r3, #16707
	movt	r3, 66
	str	r3, [sp, #8]
	stmia	ip!, {r0, r1}
	ldm	r4, {r0, r1}
	strh	r2, [ip]	@ movhi
	str	r0, [sp, #12]
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	strh	r1, [sp, #16]	@ movhi
	bl	puts
	add	r2, sp, #20
	movw	r1, #:lower16:.LC4
	mov	r0, #1
	movt	r1, #:upper16:.LC4
	bl	__printf_chk
	add	r2, sp, #12
	movw	r1, #:lower16:.LC5
	mov	r0, #1
	movt	r1, #:upper16:.LC5
	bl	__printf_chk
	add	r1, sp, #12
	add	r0, sp, #20
	bl	naive_search
	add	r2, sp, #4
	movw	r1, #:lower16:.LC6
	mov	r0, #1
	movt	r1, #:upper16:.LC6
	bl	__printf_chk
	add	r1, sp, #4
	add	r0, sp, #20
	bl	naive_search
	add	r2, sp, #8
	movw	r1, #:lower16:.LC7
	mov	r0, #1
	movt	r1, #:upper16:.LC7
	bl	__printf_chk
	add	r0, sp, #20
	add	r1, sp, #8
	bl	naive_search
	mov	r0, #0
	add	sp, sp, #48
	@ sp needed
	pop	{r4, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
