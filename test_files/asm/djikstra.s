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
	.file	"djikstra.c"
	.text
	.comm	mat,1600,4
	.comm	V,4,4
	.comm	dist,80,4
	.comm	q,80,4
	.global	qp
	.bss
	.align	2
	.type	qp, %object
	.size	qp, 4
qp:
	.space	4
	.text
	.align	2
	.global	enqueue
	.syntax unified
	.arm
	.fpu softvfp
	.type	enqueue, %function
enqueue:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	movw	r3, #:lower16:qp
	movt	r3, #:upper16:qp
	ldr	r2, [r3]
	add	r1, r2, #1
	movw	r3, #:lower16:qp
	movt	r3, #:upper16:qp
	str	r1, [r3]
	movw	r3, #:lower16:q
	movt	r3, #:upper16:q
	ldr	r1, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	enqueue, .-enqueue
	.align	2
	.global	cf
	.syntax unified
	.arm
	.fpu softvfp
	.type	cf, %function
cf:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-20]
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	ldr	r2, [r3]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	sub	r3, r2, r3
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	cf, .-cf
	.align	2
	.global	dequeue
	.syntax unified
	.arm
	.fpu softvfp
	.type	dequeue, %function
dequeue:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	movw	r3, #:lower16:qp
	movt	r3, #:upper16:qp
	ldr	r3, [r3]
	mov	r1, r3
	movw	r3, #:lower16:cf
	movt	r3, #:upper16:cf
	mov	r2, #4
	movw	r0, #:lower16:q
	movt	r0, #:upper16:q
	bl	qsort
	movw	r3, #:lower16:qp
	movt	r3, #:upper16:qp
	ldr	r3, [r3]
	sub	r2, r3, #1
	movw	r3, #:lower16:qp
	movt	r3, #:upper16:qp
	str	r2, [r3]
	movw	r3, #:lower16:qp
	movt	r3, #:upper16:qp
	ldr	r2, [r3]
	movw	r3, #:lower16:q
	movt	r3, #:upper16:q
	ldr	r3, [r3, r2, lsl #2]
	mov	r0, r3
	pop	{fp, pc}
	.size	dequeue, .-dequeue
	.align	2
	.global	queue_has_something
	.syntax unified
	.arm
	.fpu softvfp
	.type	queue_has_something, %function
queue_has_something:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	movw	r3, #:lower16:qp
	movt	r3, #:upper16:qp
	ldr	r3, [r3]
	cmp	r3, #0
	movgt	r3, #1
	movle	r3, #0
	uxtb	r3, r3
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	queue_has_something, .-queue_has_something
	.comm	visited,80,4
	.global	vp
	.bss
	.align	2
	.type	vp, %object
	.size	vp, 4
vp:
	.space	4
	.text
	.align	2
	.global	dijkstra
	.syntax unified
	.arm
	.fpu softvfp
	.type	dijkstra, %function
dijkstra:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	movw	r3, #:lower16:dist
	movt	r3, #:upper16:dist
	ldr	r2, [fp, #-16]
	mov	r1, #0
	str	r1, [r3, r2, lsl #2]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L9
.L11:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-16]
	cmp	r2, r3
	beq	.L10
	movw	r3, #:lower16:dist
	movt	r3, #:upper16:dist
	ldr	r2, [fp, #-8]
	movw	r1, #999
	str	r1, [r3, r2, lsl #2]
.L10:
	ldr	r0, [fp, #-8]
	bl	enqueue
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L9:
	movw	r3, #:lower16:V
	movt	r3, #:upper16:V
	ldr	r3, [r3]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L11
	b	.L12
.L16:
	bl	dequeue
	str	r0, [fp, #-12]
	movw	r3, #:lower16:vp
	movt	r3, #:upper16:vp
	ldr	r2, [r3]
	add	r1, r2, #1
	movw	r3, #:lower16:vp
	movt	r3, #:upper16:vp
	str	r1, [r3]
	movw	r3, #:lower16:visited
	movt	r3, #:upper16:visited
	ldr	r1, [fp, #-12]
	str	r1, [r3, r2, lsl #2]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L13
.L15:
	movw	r3, #:lower16:mat
	movt	r3, #:upper16:mat
	ldr	r2, [fp, #-12]
	mov	r1, #20
	mul	r1, r1, r2
	ldr	r2, [fp, #-8]
	add	r2, r1, r2
	ldr	r3, [r3, r2, lsl #2]
	cmp	r3, #0
	beq	.L14
	movw	r3, #:lower16:dist
	movt	r3, #:upper16:dist
	ldr	r2, [fp, #-8]
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:dist
	movt	r3, #:upper16:dist
	ldr	r1, [fp, #-12]
	ldr	r1, [r3, r1, lsl #2]
	movw	r3, #:lower16:mat
	movt	r3, #:upper16:mat
	ldr	r0, [fp, #-12]
	mov	ip, #20
	mul	ip, ip, r0
	ldr	r0, [fp, #-8]
	add	r0, ip, r0
	ldr	r3, [r3, r0, lsl #2]
	add	r3, r1, r3
	cmp	r2, r3
	ble	.L14
	movw	r3, #:lower16:dist
	movt	r3, #:upper16:dist
	ldr	r2, [fp, #-12]
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:mat
	movt	r3, #:upper16:mat
	ldr	r1, [fp, #-12]
	mov	r0, #20
	mul	r0, r0, r1
	ldr	r1, [fp, #-8]
	add	r1, r0, r1
	ldr	r3, [r3, r1, lsl #2]
	add	r1, r2, r3
	movw	r3, #:lower16:dist
	movt	r3, #:upper16:dist
	ldr	r2, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
.L14:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L13:
	movw	r3, #:lower16:V
	movt	r3, #:upper16:V
	ldr	r3, [r3]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L15
.L12:
	bl	queue_has_something
	mov	r3, r0
	cmp	r3, #0
	bne	.L16
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	dijkstra, .-dijkstra
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Enter the number of vertices: \000"
	.align	2
.LC1:
	.ascii	" %d\000"
	.align	2
.LC2:
	.ascii	"Enter the adj matrix: \000"
	.align	2
.LC3:
	.ascii	"\012Node\011Dist\000"
	.align	2
.LC4:
	.ascii	"%d\011%d\012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	movw	r1, #:lower16:V
	movt	r1, #:upper16:V
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	__isoc99_scanf
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	printf
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L18
.L21:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L19
.L20:
	ldr	r3, [fp, #-8]
	mov	r2, #20
	mul	r2, r2, r3
	ldr	r3, [fp, #-12]
	add	r3, r2, r3
	lsl	r2, r3, #2
	movw	r3, #:lower16:mat
	movt	r3, #:upper16:mat
	add	r3, r2, r3
	mov	r1, r3
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	__isoc99_scanf
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L19:
	movw	r3, #:lower16:V
	movt	r3, #:upper16:V
	ldr	r3, [r3]
	ldr	r2, [fp, #-12]
	cmp	r2, r3
	blt	.L20
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L18:
	movw	r3, #:lower16:V
	movt	r3, #:upper16:V
	ldr	r3, [r3]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L21
	mov	r0, #0
	bl	dijkstra
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	puts
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L22
.L23:
	movw	r3, #:lower16:dist
	movt	r3, #:upper16:dist
	ldr	r2, [fp, #-8]
	ldr	r3, [r3, r2, lsl #2]
	mov	r2, r3
	ldr	r1, [fp, #-8]
	movw	r0, #:lower16:.LC4
	movt	r0, #:upper16:.LC4
	bl	printf
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L22:
	movw	r3, #:lower16:V
	movt	r3, #:upper16:V
	ldr	r3, [r3]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L23
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
