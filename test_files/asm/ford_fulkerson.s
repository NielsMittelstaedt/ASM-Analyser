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
	.file	"ford_fulkerson.c"
	.text
	.align	2
	.global	min
	.syntax unified
	.arm
	.fpu softvfp
	.type	min, %function
min:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, r0
	movlt	r0, r1
	bx	lr
	.size	min, .-min
	.align	2
	.global	enqueue
	.syntax unified
	.arm
	.fpu softvfp
	.type	enqueue, %function
enqueue:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #:lower16:tail
	movt	r3, #:upper16:tail
	movw	r1, #:lower16:q
	movw	r2, #:lower16:color
	ldr	ip, [r3]
	movt	r1, #:upper16:q
	movt	r2, #:upper16:color
	str	lr, [sp, #-4]!
	add	lr, ip, #1
	str	r0, [r1, ip, lsl #2]
	mov	r1, #1
	str	lr, [r3]
	str	r1, [r2, r0, lsl #2]
	ldr	pc, [sp], #4
	.size	enqueue, .-enqueue
	.align	2
	.global	dequeue
	.syntax unified
	.arm
	.fpu softvfp
	.type	dequeue, %function
dequeue:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #:lower16:head
	movt	r3, #:upper16:head
	movw	r1, #:lower16:q
	movt	r1, #:upper16:q
	ldr	r0, [r3]
	movw	r2, #:lower16:color
	str	lr, [sp, #-4]!
	add	lr, r0, #1
	ldr	r0, [r1, r0, lsl #2]
	movt	r2, #:upper16:color
	mov	ip, #2
	str	lr, [r3]
	str	ip, [r2, r0, lsl #2]
	ldr	pc, [sp], #4
	.size	dequeue, .-dequeue
	.align	2
	.global	bfs
	.syntax unified
	.arm
	.fpu softvfp
	.type	bfs, %function
bfs:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #:lower16:num
	movt	r3, #:upper16:num
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #28
	ldr	r4, [r3]
	mov	r5, r0
	str	r1, [sp, #16]
	cmp	r4, #0
	ble	.L10
	movw	r0, #:lower16:color
	lsl	r2, r4, #2
	movt	r0, #:upper16:color
	mov	r1, #0
	bl	memset
.L10:
	movw	r3, #:lower16:q
	movw	r1, #:lower16:tail
	movt	r3, #:upper16:q
	movt	r1, #:upper16:tail
	movw	lr, #:lower16:color
	movw	r8, #:lower16:pred
	movt	lr, #:upper16:color
	movt	r8, #:upper16:pred
	mov	r9, #0
	mov	r2, #1
	mov	r7, r9
	mov	r10, r3
	mov	ip, r2
	mov	r0, r3
	mov	fp, r2
	str	r5, [r3]
	str	r2, [r1]
	mvn	r3, #0
	str	r2, [lr, r5, lsl #2]
	movw	r2, #:lower16:flow
	str	r3, [r8, r5, lsl #2]
	movt	r2, #:upper16:flow
	movw	r3, #:lower16:capacity
	str	r1, [sp, #20]
	movt	r3, #:upper16:capacity
	str	lr, [sp, #4]
	str	r3, [sp, #8]
	str	r2, [sp, #12]
.L9:
	ldr	r5, [r0], #4
	cmp	r4, #0
	ldr	r3, [sp, #4]
	mov	r2, #2
	add	r7, r7, #1
	str	r2, [r3, r5, lsl #2]
	ble	.L11
	mov	r3, #200
	ldr	r1, [sp, #8]
	mul	lr, r3, r5
	movw	r2, #:lower16:color
	movt	r2, #:upper16:color
	mov	r3, #0
	str	r0, [sp]
	add	r6, lr, r1
	ldr	r1, [sp, #12]
	add	lr, lr, r1
.L13:
	ldr	r1, [r2], #4
	cmp	r1, #0
	bne	.L12
	ldr	r1, [r6, r3, lsl #2]
	ldr	r0, [lr, r3, lsl #2]
	sub	r1, r1, r0
	cmp	r1, #0
	strgt	r3, [r10, ip, lsl #2]
	addgt	ip, ip, #1
	strgt	fp, [r2, #-4]
	movgt	r9, #1
	strgt	r5, [r8, r3, lsl #2]
.L12:
	add	r3, r3, #1
	cmp	r3, r4
	bne	.L13
	ldr	r0, [sp]
.L11:
	cmp	r7, ip
	bne	.L9
	cmp	r9, #0
	movw	r3, #:lower16:head
	movt	r3, #:upper16:head
	ldr	r2, [sp, #16]
	str	r7, [r3]
	ldrne	r3, [sp, #20]
	strne	r7, [r3]
	ldr	r3, [sp, #4]
	ldr	r0, [r3, r2, lsl #2]
	sub	r0, r0, #2
	clz	r0, r0
	lsr	r0, r0, #5
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	bfs, .-bfs
	.align	2
	.global	fordFulkerson
	.syntax unified
	.arm
	.fpu softvfp
	.type	fordFulkerson, %function
fordFulkerson:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	movw	r6, #:lower16:num
	movt	r6, #:upper16:num
	sub	sp, sp, #12
	ldr	r5, [r6]
	strd	r0, [sp]
	cmp	r5, #0
	ble	.L22
	movw	r4, #:lower16:flow
	movt	r4, #:upper16:flow
	mov	r3, #200
	lsl	r7, r5, #2
	mla	r5, r3, r5, r4
.L23:
	mov	r0, r4
	mov	r2, r7
	add	r4, r4, #200
	mov	r1, #0
	bl	memset
	cmp	r5, r4
	bne	.L23
.L22:
	ldrd	r0, [sp]
	movw	r5, #:lower16:pred
	bl	bfs
	movw	r4, #:lower16:flow
	movw	r7, #:lower16:capacity
	movt	r5, #:upper16:pred
	movt	r4, #:upper16:flow
	movt	r7, #:upper16:capacity
	mov	r8, #0
	cmp	r0, #0
	beq	.L34
.L28:
	ldr	ip, [r6]
	mov	r3, #51712
	sub	ip, ip, #1
	ldr	r2, [r5, ip, lsl #2]
	cmp	r2, #0
	blt	.L29
	movt	r3, 15258
	mov	r10, ip
	mov	r0, r2
	mov	fp, #50
.L26:
	mla	r9, fp, r0, r10
	ldr	lr, [r5, r0, lsl #2]
	mov	r10, r0
	mov	r0, lr
	ldr	r1, [r7, r9, lsl #2]
	ldr	r9, [r4, r9, lsl #2]
	sub	r1, r1, r9
	cmp	r3, r1
	movge	r3, r1
	cmp	lr, #0
	bge	.L26
	mov	lr, #50
.L27:
	mla	r9, lr, r2, ip
	ldr	r1, [r5, r2, lsl #2]
	mla	r0, lr, ip, r2
	cmp	r1, #0
	mov	ip, r2
	mov	r2, r1
	ldr	r1, [r4, r9, lsl #2]
	add	r1, r1, r3
	str	r1, [r4, r9, lsl #2]
	ldr	r1, [r4, r0, lsl #2]
	sub	r1, r1, r3
	str	r1, [r4, r0, lsl #2]
	bge	.L27
	add	r8, r8, r3
.L35:
	ldrd	r0, [sp]
	bl	bfs
	cmp	r0, #0
	bne	.L28
.L34:
	mov	r0, r8
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L29:
	movt	r3, 15258
	add	r8, r8, r3
	b	.L35
	.size	fordFulkerson, .-fordFulkerson
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Max Flow: %d\012\000"
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
	push	{r4, r5, r6, r7, r8, lr}
	movw	r8, #:lower16:num
	movt	r8, #:upper16:num
	movw	r4, #:lower16:capacity
	movt	r4, #:upper16:capacity
	ldr	r6, [r8]
	cmp	r6, #0
	ble	.L37
	mov	r3, #200
	lsl	r7, r6, #2
	mla	r6, r3, r6, r4
	mov	r5, r4
.L38:
	mov	r0, r5
	mov	r2, r7
	add	r5, r5, #200
	mov	r1, #0
	bl	memset
	cmp	r5, r6
	bne	.L38
.L37:
	movw	r3, #:lower16:e
	movt	r3, #:upper16:e
	mov	r1, #15
	mov	r0, #0
	mov	r5, #1
	mov	r2, #33
	str	r5, [r4, #4]
	str	r2, [r3]
	mov	r3, #16
	str	r5, [r4, #8]
	str	r3, [r8]
	str	r5, [r4, #12]
	str	r5, [r4, #16]
	str	r5, [r4, #20]
	str	r5, [r4, #24]
	str	r5, [r4, #28]
	str	r5, [r4, #236]
	str	r5, [r4, #252]
	str	r5, [r4, #436]
	str	r5, [r4, #444]
	str	r5, [r4, #632]
	str	r5, [r4, #640]
	str	r5, [r4, #648]
	str	r5, [r4, #832]
	str	r5, [r4, #840]
	str	r5, [r4, #848]
	str	r5, [r4, #1036]
	str	r5, [r4, #1044]
	str	r5, [r4, #1052]
	str	r5, [r4, #1240]
	str	r5, [r4, #1244]
	str	r5, [r4, #1248]
	str	r5, [r4, #1252]
	str	r5, [r4, #1256]
	str	r5, [r4, #1452]
	str	r5, [r4, #1660]
	str	r5, [r4, #1860]
	str	r5, [r4, #2060]
	str	r5, [r4, #2260]
	str	r5, [r4, #2460]
	str	r5, [r4, #2660]
	str	r5, [r4, #2860]
	bl	fordFulkerson
	movw	r1, #:lower16:.LC0
	movt	r1, #:upper16:.LC0
	mov	r2, r0
	mov	r0, r5
	bl	__printf_chk
	mov	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
	.size	main, .-main
	.comm	q,208,4
	.comm	tail,4,4
	.comm	head,4,4
	.comm	pred,200,4
	.comm	color,200,4
	.comm	flow,10000,4
	.comm	capacity,10000,4
	.comm	e,4,4
	.comm	num,4,4
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
