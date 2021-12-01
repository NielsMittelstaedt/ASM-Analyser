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
	.file	"modified_binary_search.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Found at (%d,%d)\012\000"
	.align	2
.LC1:
	.ascii	"element not found\000"
	.text
	.align	2
	.global	binarySearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	binarySearch, %function
binarySearch:
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	str	r3, [fp, #-28]
	b	.L2
.L6:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-28]
	add	r3, r2, r3
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #4]
	cmp	r2, r3
	bne	.L3
	ldr	r2, [fp, #-8]
	ldr	r1, [fp, #-20]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	ldr	r3, [fp, #-8]
	b	.L4
.L3:
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #4]
	cmp	r2, r3
	bge	.L5
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-28]
	b	.L2
.L5:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-24]
.L2:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-28]
	cmp	r2, r3
	ble	.L6
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	puts
	mvn	r3, #0
.L4:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	binarySearch, .-binarySearch
	.align	2
	.global	modifiedBinarySearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	modifiedBinarySearch, %function
modifiedBinarySearch:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #40
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	str	r2, [fp, #-32]
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-28]
	cmp	r3, #1
	bne	.L8
	ldr	r3, [fp, #-32]
	sub	r2, r3, #1
	ldr	r3, [fp, #-36]
	str	r3, [sp]
	mov	r3, r2
	mov	r2, #0
	mov	r1, #0
	ldr	r0, [fp, #-24]
	bl	binarySearch
	b	.L7
.L8:
	mov	r3, #0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-28]
	sub	r3, r3, #1
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-32]
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L10
.L13:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r3, r2, r3
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	str	r3, [fp, #-20]
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	bne	.L11
	ldr	r2, [fp, #-16]
	ldr	r1, [fp, #-20]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	b	.L7
.L11:
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	bge	.L12
	ldr	r3, [fp, #-20]
	str	r3, [fp, #-12]
	b	.L10
.L12:
	ldr	r3, [fp, #-20]
	str	r3, [fp, #-8]
.L10:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	ldr	r2, [fp, #-12]
	cmp	r2, r3
	bgt	.L13
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	bne	.L14
	ldr	r2, [fp, #-16]
	ldr	r1, [fp, #-8]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	b	.L7
.L14:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	bne	.L15
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	ldr	r2, [fp, #-16]
	mov	r1, r3
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	b	.L7
.L15:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	sub	r3, r3, #-1073741823
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	bgt	.L16
	ldr	r3, [fp, #-16]
	sub	r2, r3, #1
	ldr	r3, [fp, #-36]
	str	r3, [sp]
	mov	r3, r2
	mov	r2, #0
	ldr	r1, [fp, #-8]
	ldr	r0, [fp, #-24]
	bl	binarySearch
	b	.L7
.L16:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	blt	.L17
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-32]
	sub	r3, r3, #-1073741823
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	bgt	.L17
	ldr	r3, [fp, #-16]
	add	r2, r3, #1
	ldr	r3, [fp, #-32]
	sub	r1, r3, #1
	ldr	r3, [fp, #-36]
	str	r3, [sp]
	mov	r3, r1
	ldr	r1, [fp, #-8]
	ldr	r0, [fp, #-24]
	bl	binarySearch
	b	.L7
.L17:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	lsl	r3, r3, #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	sub	r3, r3, #-1073741823
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-36]
	cmp	r2, r3
	bgt	.L18
	ldr	r3, [fp, #-8]
	add	r1, r3, #1
	ldr	r3, [fp, #-16]
	sub	r2, r3, #1
	ldr	r3, [fp, #-36]
	str	r3, [sp]
	mov	r3, r2
	mov	r2, #0
	ldr	r0, [fp, #-24]
	bl	binarySearch
	b	.L7
.L18:
	ldr	r3, [fp, #-8]
	add	r1, r3, #1
	ldr	r3, [fp, #-16]
	add	r2, r3, #1
	ldr	r3, [fp, #-32]
	sub	r0, r3, #1
	ldr	r3, [fp, #-36]
	str	r3, [sp]
	mov	r3, r0
	ldr	r0, [fp, #-24]
	bl	binarySearch
.L7:
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	modifiedBinarySearch, .-modifiedBinarySearch
	.section	.rodata
	.align	2
.LC2:
	.ascii	"%d %d %d\012\000"
	.align	2
.LC3:
	.ascii	"%d\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #36
	sub	r3, fp, #36
	sub	r2, fp, #40
	sub	r1, fp, #44
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	__isoc99_scanf
	ldr	r3, [fp, #-44]
	lsl	r3, r3, #2
	mov	r0, r3
	bl	malloc
	mov	r3, r0
	str	r3, [fp, #-32]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L20
.L21:
	ldr	r3, [fp, #-40]
	lsl	r1, r3, #2
	ldr	r3, [fp, #-16]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-32]
	add	r4, r2, r3
	mov	r0, r1
	bl	malloc
	mov	r3, r0
	str	r3, [r4]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L20:
	ldr	r3, [fp, #-40]
	ldr	r2, [fp, #-16]
	cmp	r2, r3
	blt	.L21
	mov	r3, #0
	str	r3, [fp, #-20]
	b	.L22
.L25:
	mov	r3, #0
	str	r3, [fp, #-24]
	b	.L23
.L24:
	ldr	r3, [fp, #-20]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-32]
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-24]
	lsl	r3, r3, #2
	add	r3, r2, r3
	mov	r1, r3
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	__isoc99_scanf
	ldr	r3, [fp, #-24]
	add	r3, r3, #1
	str	r3, [fp, #-24]
.L23:
	ldr	r3, [fp, #-40]
	ldr	r2, [fp, #-24]
	cmp	r2, r3
	blt	.L24
	ldr	r3, [fp, #-20]
	add	r3, r3, #1
	str	r3, [fp, #-20]
.L22:
	ldr	r3, [fp, #-44]
	ldr	r2, [fp, #-20]
	cmp	r2, r3
	blt	.L25
	ldr	r1, [fp, #-44]
	ldr	r2, [fp, #-40]
	ldr	r3, [fp, #-36]
	ldr	r0, [fp, #-32]
	bl	modifiedBinarySearch
	mov	r3, #0
	str	r3, [fp, #-28]
	b	.L26
.L27:
	ldr	r3, [fp, #-28]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-32]
	add	r3, r2, r3
	ldr	r3, [r3]
	mov	r0, r3
	bl	free
	ldr	r3, [fp, #-28]
	add	r3, r3, #1
	str	r3, [fp, #-28]
.L26:
	ldr	r3, [fp, #-44]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	blt	.L27
	ldr	r0, [fp, #-32]
	bl	free
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #8
	@ sp needed
	pop	{r4, fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
