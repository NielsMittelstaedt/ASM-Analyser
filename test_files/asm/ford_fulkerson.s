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
	.file	"ford_fulkerson.c"
	.text
	.comm	num,4,4
	.comm	e,4,4
	.comm	capacity,4000000,4
	.comm	flow,4000000,4
	.comm	color,4000,4
	.comm	pred,4000,4
	.align	2
	.global	min
	.syntax unified
	.arm
	.fpu softvfp
	.type	min, %function
min:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	movlt	r3, r2
	movge	r3, r3
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	min, .-min
	.comm	head,4,4
	.comm	tail,4,4
	.comm	q,4008,4
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
	movw	r3, #:lower16:tail
	movt	r3, #:upper16:tail
	ldr	r2, [r3]
	movw	r3, #:lower16:q
	movt	r3, #:upper16:q
	ldr	r1, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:tail
	movt	r3, #:upper16:tail
	ldr	r3, [r3]
	add	r2, r3, #1
	movw	r3, #:lower16:tail
	movt	r3, #:upper16:tail
	str	r2, [r3]
	movw	r3, #:lower16:color
	movt	r3, #:upper16:color
	ldr	r2, [fp, #-8]
	mov	r1, #1
	str	r1, [r3, r2, lsl #2]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	enqueue, .-enqueue
	.align	2
	.global	dequeue
	.syntax unified
	.arm
	.fpu softvfp
	.type	dequeue, %function
dequeue:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	movw	r3, #:lower16:head
	movt	r3, #:upper16:head
	ldr	r2, [r3]
	movw	r3, #:lower16:q
	movt	r3, #:upper16:q
	ldr	r3, [r3, r2, lsl #2]
	str	r3, [fp, #-8]
	movw	r3, #:lower16:head
	movt	r3, #:upper16:head
	ldr	r3, [r3]
	add	r2, r3, #1
	movw	r3, #:lower16:head
	movt	r3, #:upper16:head
	str	r2, [r3]
	movw	r3, #:lower16:color
	movt	r3, #:upper16:color
	ldr	r2, [fp, #-8]
	mov	r1, #2
	str	r1, [r3, r2, lsl #2]
	ldr	r3, [fp, #-8]
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	dequeue, .-dequeue
	.align	2
	.global	bfs
	.syntax unified
	.arm
	.fpu softvfp
	.type	bfs, %function
bfs:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L7
.L8:
	movw	r3, #:lower16:color
	movt	r3, #:upper16:color
	ldr	r2, [fp, #-8]
	mov	r1, #0
	str	r1, [r3, r2, lsl #2]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L7:
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L8
	movw	r3, #:lower16:tail
	movt	r3, #:upper16:tail
	mov	r2, #0
	str	r2, [r3]
	movw	r3, #:lower16:tail
	movt	r3, #:upper16:tail
	ldr	r2, [r3]
	movw	r3, #:lower16:head
	movt	r3, #:upper16:head
	str	r2, [r3]
	ldr	r0, [fp, #-16]
	bl	enqueue
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	mvn	r1, #0
	str	r1, [r3, r2, lsl #2]
	b	.L9
.L13:
	bl	dequeue
	str	r0, [fp, #-8]
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L10
.L12:
	movw	r3, #:lower16:color
	movt	r3, #:upper16:color
	ldr	r2, [fp, #-12]
	ldr	r3, [r3, r2, lsl #2]
	cmp	r3, #0
	bne	.L11
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	ldr	r2, [fp, #-8]
	mov	r1, #1000
	mul	r1, r1, r2
	ldr	r2, [fp, #-12]
	add	r2, r1, r2
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:flow
	movt	r3, #:upper16:flow
	ldr	r1, [fp, #-8]
	mov	r0, #1000
	mul	r0, r0, r1
	ldr	r1, [fp, #-12]
	add	r1, r0, r1
	ldr	r3, [r3, r1, lsl #2]
	sub	r3, r2, r3
	cmp	r3, #0
	ble	.L11
	ldr	r0, [fp, #-12]
	bl	enqueue
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-12]
	ldr	r1, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
.L11:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L10:
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	ldr	r2, [fp, #-12]
	cmp	r2, r3
	blt	.L12
.L9:
	movw	r3, #:lower16:head
	movt	r3, #:upper16:head
	ldr	r2, [r3]
	movw	r3, #:lower16:tail
	movt	r3, #:upper16:tail
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L13
	movw	r3, #:lower16:color
	movt	r3, #:upper16:color
	ldr	r2, [fp, #-20]
	ldr	r3, [r3, r2, lsl #2]
	cmp	r3, #2
	moveq	r3, #1
	movne	r3, #0
	uxtb	r3, r3
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	bfs, .-bfs
	.align	2
	.global	fordFulkerson
	.syntax unified
	.arm
	.fpu softvfp
	.type	fordFulkerson, %function
fordFulkerson:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #32
	str	r0, [fp, #-32]
	str	r1, [fp, #-36]
	mov	r3, #0
	str	r3, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L16
.L19:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L17
.L18:
	movw	r3, #:lower16:flow
	movt	r3, #:upper16:flow
	ldr	r2, [fp, #-8]
	mov	r1, #1000
	mul	r1, r1, r2
	ldr	r2, [fp, #-12]
	add	r2, r1, r2
	mov	r1, #0
	str	r1, [r3, r2, lsl #2]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L17:
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	ldr	r2, [fp, #-12]
	cmp	r2, r3
	blt	.L18
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L16:
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L19
	b	.L20
.L25:
	mov	r3, #51712
	movt	r3, 15258
	str	r3, [fp, #-24]
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	sub	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L21
.L22:
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	mov	r1, #1000
	mul	r1, r1, r2
	ldr	r2, [fp, #-16]
	add	r2, r1, r2
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r1, [fp, #-16]
	ldr	r1, [r3, r1, lsl #2]
	movw	r3, #:lower16:flow
	movt	r3, #:upper16:flow
	mov	r0, #1000
	mul	r0, r0, r1
	ldr	r1, [fp, #-16]
	add	r1, r0, r1
	ldr	r3, [r3, r1, lsl #2]
	sub	r3, r2, r3
	mov	r1, r3
	ldr	r0, [fp, #-24]
	bl	min
	str	r0, [fp, #-24]
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r3, [r3, r2, lsl #2]
	str	r3, [fp, #-16]
.L21:
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r3, [r3, r2, lsl #2]
	cmp	r3, #0
	bge	.L22
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	sub	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L23
.L24:
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:flow
	movt	r3, #:upper16:flow
	mov	r1, #1000
	mul	r1, r1, r2
	ldr	r2, [fp, #-16]
	add	r2, r1, r2
	ldr	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r2, [r3, r2, lsl #2]
	ldr	r3, [fp, #-24]
	add	r1, r1, r3
	movw	r3, #:lower16:flow
	movt	r3, #:upper16:flow
	mov	r0, #1000
	mul	r0, r0, r2
	ldr	r2, [fp, #-16]
	add	r2, r0, r2
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:flow
	movt	r3, #:upper16:flow
	ldr	r1, [fp, #-16]
	mov	r0, #1000
	mul	r1, r0, r1
	add	r2, r1, r2
	ldr	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r2, [r3, r2, lsl #2]
	ldr	r3, [fp, #-24]
	sub	r1, r1, r3
	movw	r3, #:lower16:flow
	movt	r3, #:upper16:flow
	ldr	r0, [fp, #-16]
	mov	ip, #1000
	mul	r0, ip, r0
	add	r2, r0, r2
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r3, [r3, r2, lsl #2]
	str	r3, [fp, #-16]
.L23:
	movw	r3, #:lower16:pred
	movt	r3, #:upper16:pred
	ldr	r2, [fp, #-16]
	ldr	r3, [r3, r2, lsl #2]
	cmp	r3, #0
	bge	.L24
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-24]
	add	r3, r2, r3
	str	r3, [fp, #-20]
.L20:
	ldr	r1, [fp, #-36]
	ldr	r0, [fp, #-32]
	bl	bfs
	mov	r3, r0
	cmp	r3, #0
	bne	.L25
	ldr	r3, [fp, #-20]
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	fordFulkerson, .-fordFulkerson
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Max Flow: %d\012\000"
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
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L28
.L31:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L29
.L30:
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	ldr	r2, [fp, #-8]
	mov	r1, #1000
	mul	r1, r1, r2
	ldr	r2, [fp, #-12]
	add	r2, r1, r2
	mov	r1, #0
	str	r1, [r3, r2, lsl #2]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L29:
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	ldr	r2, [fp, #-12]
	cmp	r2, r3
	blt	.L30
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L28:
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	ldr	r3, [r3]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L31
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	mov	r2, #6
	str	r2, [r3]
	movw	r3, #:lower16:e
	movt	r3, #:upper16:e
	mov	r2, #7
	str	r2, [r3]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	mov	r2, #8
	str	r2, [r3, #4]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	mov	r2, #3
	str	r2, [r3, #16]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	mov	r2, #9
	str	r2, [r3, #4008]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	add	r3, r3, #4096
	mov	r2, r3
	mov	r3, #7
	str	r3, [r2, #3920]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	add	r3, r3, #4096
	mov	r2, r3
	mov	r3, #2
	str	r3, [r2, #3924]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	add	r3, r3, #8192
	mov	r2, r3
	mov	r3, #5
	str	r3, [r2, #3828]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	add	r3, r3, #12288
	mov	r2, r3
	mov	r3, #7
	str	r3, [r2, #3720]
	movw	r3, #:lower16:capacity
	movt	r3, #:upper16:capacity
	add	r3, r3, #12288
	mov	r2, r3
	mov	r3, #4
	str	r3, [r2, #3724]
	mov	r3, #0
	str	r3, [fp, #-16]
	mov	r3, #5
	str	r3, [fp, #-20]
	ldr	r1, [fp, #-20]
	ldr	r0, [fp, #-16]
	bl	fordFulkerson
	mov	r3, r0
	mov	r1, r3
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
