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
	.file	"bucket_sort.c"
	.text
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	.ascii	"Bucket[\"%d\"] : \000"
	.align	2
.LC2:
	.ascii	"%d \000"
	.align	2
.LC3:
	.ascii	"--------------\000"
	.align	2
.LC4:
	.ascii	"Buckets after sorted\000"
	.align	2
.LC5:
	.ascii	"../test_files/c_in/bucket_sort.c\000"
	.align	2
.LC6:
	.ascii	"j < NARRAY\000"
	.text
	.align	2
	.global	BucketSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	BucketSort, %function
BucketSort:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r8, r0
	sub	sp, sp, #12
	mov	r0, #20
	bl	malloc
	movw	r4, #26215
	sub	r9, r8, #4
	add	r6, r8, #28
	movt	r4, 26214
	mov	r3, #0
	mov	r2, #0
	mov	r5, r0
	str	r3, [r0, #16]
	mov	r3, #0
	strd	r2, [r0]
	strd	r2, [r0, #8]
.L2:
	mov	r0, #8
	ldr	r7, [r9, #4]!
	bl	malloc
	cmp	r9, r6
	smull	r3, r2, r4, r7
	asr	r3, r7, #31
	rsb	r3, r3, r2, asr #2
	ldr	r2, [r5, r3, lsl #2]
	str	r7, [r0]
	str	r0, [r5, r3, lsl #2]
	str	r2, [r0, #4]
	bne	.L2
	sub	r7, r5, #4
	movw	fp, #:lower16:.LC1
	movw	r6, #:lower16:.LC2
	movt	fp, #:upper16:.LC1
	movt	r6, #:upper16:.LC2
	mov	r10, r7
	mov	r9, #0
.L4:
	mov	r2, r9
	mov	r1, fp
	mov	r0, #1
	bl	__printf_chk
	ldr	r4, [r10, #4]!
	cmp	r4, #0
	beq	.L6
.L3:
	ldr	r2, [r4]
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	ldr	r4, [r4, #4]
	cmp	r4, #0
	bne	.L3
.L6:
	add	r9, r9, #1
	mov	r0, #10
	bl	putchar
	cmp	r9, #5
	bne	.L4
	add	r9, r5, #16
	mov	r6, r7
	mov	r10, #0
.L14:
	ldr	lr, [r6, #4]!
	cmp	lr, #0
	beq	.L7
	ldr	r1, [lr, #4]
	cmp	r1, #0
	beq	.L7
	ldr	r4, [lr]
	str	r10, [lr, #4]
	b	.L13
.L85:
	ldr	r3, [r1, #4]
	mov	r4, r0
	str	lr, [r1, #4]
	mov	lr, r1
	mov	r1, r3
.L9:
	cmp	r1, #0
	beq	.L7
.L13:
	ldr	r0, [r1]
	cmp	r0, r4
	blt	.L85
	mov	r3, lr
	b	.L8
.L11:
	ldr	r2, [r3]
	cmp	r0, r2
	blt	.L86
.L8:
	mov	ip, r3
	ldr	r3, [r3, #4]
	cmp	r3, #0
	bne	.L11
	str	r1, [ip, #4]
	ldr	r2, [r1, #4]
	str	r3, [r1, #4]
	mov	r1, r2
	cmp	r1, #0
	bne	.L13
.L7:
	cmp	r6, r9
	str	lr, [r6]
	bne	.L14
	movw	r0, #:lower16:.LC3
	movw	fp, #:lower16:.LC1
	movt	r0, #:upper16:.LC3
	movw	r4, #:lower16:.LC2
	movt	fp, #:upper16:.LC1
	movt	r4, #:upper16:.LC2
	bl	puts
	mov	r6, #0
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	puts
	str	r7, [sp, #4]
.L16:
	mov	r2, r6
	mov	r1, fp
	mov	r0, #1
	bl	__printf_chk
	ldr	r3, [sp, #4]
	ldr	r10, [r3, #4]!
	cmp	r10, #0
	str	r3, [sp, #4]
	beq	.L18
.L15:
	ldr	r2, [r10]
	mov	r1, r4
	mov	r0, #1
	bl	__printf_chk
	ldr	r10, [r10, #4]
	cmp	r10, #0
	bne	.L15
.L18:
	add	r6, r6, #1
	mov	r0, #10
	bl	putchar
	cmp	r6, #5
	bne	.L16
	mov	r1, r7
	mov	r3, #0
.L17:
	ldr	r2, [r1, #4]
	add	lr, r1, #4
	cmp	r2, #0
	beq	.L30
	cmp	r3, #8
	beq	.L20
	ldr	r0, [r2, #4]
	add	r4, r3, #1
	ldr	ip, [r2]
	lsl	r2, r3, #2
	cmp	r0, #0
	str	ip, [r8, r3, lsl #2]
	beq	.L36
	cmp	r4, #8
	beq	.L20
	ldr	ip, [r0, #4]
	add	r2, r8, r2
	ldr	r0, [r0]
	add	r4, r3, #2
	cmp	ip, #0
	str	r0, [r2, #4]
	beq	.L36
	cmp	r4, #8
	beq	.L20
	ldr	r0, [ip, #4]
	add	r4, r3, #3
	ldr	ip, [ip]
	cmp	r0, #0
	str	ip, [r2, #8]
	beq	.L36
	cmp	r4, #8
	beq	.L20
	ldr	ip, [r0, #4]
	add	r4, r3, #4
	ldr	r0, [r0]
	cmp	ip, #0
	str	r0, [r2, #12]
	beq	.L36
	cmp	r4, #8
	beq	.L20
	ldr	r0, [ip, #4]
	add	r4, r3, #5
	ldr	ip, [ip]
	cmp	r0, #0
	str	ip, [r2, #16]
	beq	.L36
	cmp	r4, #8
	beq	.L20
	ldr	ip, [r0, #4]
	add	r4, r3, #6
	ldr	r0, [r0]
	cmp	ip, #0
	str	r0, [r2, #20]
	beq	.L36
	cmp	r4, #8
	beq	.L20
	ldr	r0, [ip, #4]
	add	r3, r3, #7
	ldr	ip, [ip]
	cmp	r0, #0
	str	ip, [r2, #24]
	beq	.L30
	cmp	r3, #7
	bne	.L20
	ldr	r2, [r0, #4]
	ldr	r3, [r0]
	cmp	r2, #0
	str	r3, [r8, #28]
	beq	.L87
.L20:
	movw	r3, #:lower16:.LANCHOR0
	movw	r1, #:lower16:.LC5
	movw	r0, #:lower16:.LC6
	movt	r3, #:upper16:.LANCHOR0
	movt	r1, #:upper16:.LC5
	movt	r0, #:upper16:.LC6
	mov	r2, #83
	bl	__assert_fail
.L86:
	ldr	r2, [r1, #4]
	str	r3, [r1, #4]
	str	r1, [ip, #4]
	mov	r1, r2
	b	.L9
.L36:
	mov	r3, r4
.L30:
	mov	r1, lr
.L19:
	cmp	r1, r9
	bne	.L17
.L26:
	ldr	r4, [r7, #4]!
	cmp	r4, #0
	beq	.L28
.L25:
	mov	r0, r4
	ldr	r4, [r4, #4]
	bl	free
	cmp	r4, #0
	bne	.L25
.L28:
	cmp	r7, r9
	bne	.L26
	mov	r0, r5
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	free
.L87:
	cmp	lr, r9
	beq	.L26
	ldr	r3, [r1, #8]!
	cmp	r3, #0
	bne	.L20
	mov	r3, #8
	b	.L19
	.size	BucketSort, .-BucketSort
	.align	2
	.global	InsertionSort
	.syntax unified
	.arm
	.fpu softvfp
	.type	InsertionSort, %function
InsertionSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	subs	r3, r0, #0
	beq	.L97
	ldr	ip, [r3, #4]
	cmp	ip, #0
	beq	.L97
	push	{r4, lr}
	mov	r2, #0
	ldr	r4, [r3]
	mov	r0, r3
	str	r2, [r3, #4]
	b	.L95
.L106:
	ldr	r3, [ip, #4]
	mov	r4, r1
	str	r0, [ip, #4]
	mov	r0, ip
	mov	ip, r3
	cmp	ip, #0
	popeq	{r4, pc}
.L95:
	ldr	r1, [ip]
	cmp	r1, r4
	blt	.L106
	mov	r3, r0
	b	.L90
.L93:
	ldr	r2, [r3]
	cmp	r1, r2
	blt	.L107
.L90:
	mov	lr, r3
	ldr	r3, [r3, #4]
	cmp	r3, #0
	bne	.L93
	str	ip, [lr, #4]
	ldr	r2, [ip, #4]
	str	r3, [ip, #4]
	mov	ip, r2
	cmp	ip, #0
	bne	.L95
	pop	{r4, pc}
.L107:
	ldr	r2, [ip, #4]
	str	r3, [ip, #4]
	str	ip, [lr, #4]
	mov	ip, r2
	cmp	ip, #0
	bne	.L95
	pop	{r4, pc}
.L97:
	mov	r0, r3
	bx	lr
	.size	InsertionSort, .-InsertionSort
	.align	2
	.global	getBucketIndex
	.syntax unified
	.arm
	.fpu softvfp
	.type	getBucketIndex, %function
getBucketIndex:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movw	r3, #26215
	movt	r3, 26214
	asr	r2, r0, #31
	smull	r3, r0, r3, r0
	rsb	r0, r2, r0, asr #2
	bx	lr
	.size	getBucketIndex, .-getBucketIndex
	.align	2
	.global	print
	.syntax unified
	.arm
	.fpu softvfp
	.type	print, %function
print:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movw	r6, #:lower16:.LC2
	sub	r4, r0, #4
	movt	r6, #:upper16:.LC2
	add	r5, r0, #28
.L110:
	ldr	r2, [r4, #4]!
	mov	r1, r6
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r5
	bne	.L110
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	print, .-print
	.align	2
	.global	printBuckets
	.syntax unified
	.arm
	.fpu softvfp
	.type	printBuckets, %function
printBuckets:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r4, r0, #0
	popeq	{r4, r5, r6, pc}
	movw	r5, #:lower16:.LC2
	movt	r5, #:upper16:.LC2
.L115:
	ldr	r2, [r4]
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	ldr	r4, [r4, #4]
	cmp	r4, #0
	bne	.L115
	pop	{r4, r5, r6, pc}
	.size	printBuckets, .-printBuckets
	.section	.rodata.str1.4
	.align	2
.LC7:
	.ascii	"Initial array\000"
	.align	2
.LC8:
	.ascii	"------------\000"
	.align	2
.LC9:
	.ascii	"Sorted array\000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	sub	sp, sp, #32
	ldr	lr, .L123
	movw	r4, #:lower16:.LC8
	mov	ip, sp
	movt	r4, #:upper16:.LC8
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldm	lr, {r0, r1, r2, r3}
	stm	ip, {r0, r1, r2, r3}
	movw	r0, #:lower16:.LC7
	movt	r0, #:upper16:.LC7
	bl	puts
	mov	r0, sp
	bl	print
	mov	r0, r4
	bl	puts
	mov	r0, sp
	bl	BucketSort
	mov	r0, r4
	bl	puts
	movw	r0, #:lower16:.LC9
	movt	r0, #:upper16:.LC9
	bl	puts
	mov	r0, sp
	bl	print
	mov	r0, #0
	add	sp, sp, #32
	@ sp needed
	pop	{r4, pc}
.L124:
	.align	2
.L123:
	.word	.LANCHOR0+12
	.size	main, .-main
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
	.type	__PRETTY_FUNCTION__.5477, %object
	.size	__PRETTY_FUNCTION__.5477, 11
__PRETTY_FUNCTION__.5477:
	.ascii	"BucketSort\000"
	.space	1
.LC0:
	.word	29
	.word	25
	.word	-1
	.word	49
	.word	9
	.word	37
	.word	21
	.word	43
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
