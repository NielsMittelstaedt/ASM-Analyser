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
	.file	"pi.c"
	.text
	.global	__aeabi_ddiv
	.global	__aeabi_dadd
	.global	__aeabi_dsub
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%lf\000"
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
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	movw	fp, #33920
	mov	r5, #0
	movt	fp, 30
	movt	r5, 16368
	mov	r6, #0
	mov	r7, #0
	mov	r4, #0
	mov	r10, #1
	b	.L4
.L9:
	bl	__aeabi_dadd
	mov	r6, r0
	mov	r7, r1
.L3:
	mov	r0, r4
	mov	r1, r5
	mov	r2, #0
	mov	r3, #1073741824
	bl	__aeabi_dadd
	add	r10, r10, #1
	cmp	r10, fp
	mov	r4, r0
	mov	r5, r1
	beq	.L8
.L4:
	mov	r2, r4
	mov	r3, r5
	mov	r0, #0
	mov	r1, #0
	movt	r1, 16400
	bl	__aeabi_ddiv
	tst	r10, #1
	mov	r8, r0
	mov	r9, r1
	mov	r0, r6
	mov	r1, r7
	mov	r2, r8
	mov	r3, r9
	bne	.L9
	bl	__aeabi_dsub
	mov	r6, r0
	mov	r7, r1
	b	.L3
.L8:
	mov	r2, r6
	mov	r3, r7
	movw	r1, #:lower16:.LC0
	mov	r0, #1
	movt	r1, #:upper16:.LC0
	bl	__printf_chk
	mov	r0, #0
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
