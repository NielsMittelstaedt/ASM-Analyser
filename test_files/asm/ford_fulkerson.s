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
	ldr	ip, [r3]
	movw	r3, #:lower16:color
	movt	r3, #:upper16:color
	str	r1, [sp, #16]
	cmp	ip, #0
	str	r3, [sp, #4]
	addgt	r1, r3, ip, lsl #2
	movgt	r2, #0
	ble	.L11
.L10:
	str	r2, [r3], #4
	cmp	r3, r1
	bne	.L10
.L11:
	movw	r3, #:lower16:q
	movt	r3, #:upper16:q
	movw	r1, #:lower16:tail
	movw	r8, #:lower16:pred
	mov	r10, r3
	mov	r4, r3
	str	r0, [r3]
	movt	r1, #:upper16:tail
	ldr	r3, [sp, #4]
	movt	r8, #:upper16:pred
	mov	r9, #0
	mov	r2, #1
	mov	r7, r9
	mov	lr, r2
	str	r2, [r3, r0, lsl #2]
	mov	fp, r2
	mvn	r3, #0
	str	r2, [r1]
	str	r3, [r8, r0, lsl #2]
	movw	r2, #:lower16:flow
	movw	r3, #:lower16:capacity
	movt	r2, #:upper16:flow
	movt	r3, #:upper16:capacity
	str	r1, [sp, #20]
	str	r3, [sp, #8]
	str	r2, [sp, #12]
.L9:
	ldr	r3, [sp, #4]
	cmp	ip, #0
	mov	r2, #2
	add	r7, r7, #1
	str	r2, [r3, r0, lsl #2]
	ble	.L12
	mov	r3, #4000
	ldr	r1, [sp, #8]
	mul	r5, r3, r0
	movw	r2, #:lower16:color
	movt	r2, #:upper16:color
	mov	r3, #0
	str	r4, [sp]
	add	r6, r5, r1
	ldr	r1, [sp, #12]
	add	r5, r5, r1
.L14:
	ldr	r1, [r2], #4
	cmp	r1, #0
	bne	.L13
	ldr	r1, [r6, r3, lsl #2]
	ldr	r4, [r5, r3, lsl #2]
	sub	r1, r1, r4
	cmp	r1, #0
	strgt	r3, [r10, lr, lsl #2]
	addgt	lr, lr, #1
	strgt	fp, [r2, #-4]
	movgt	r9, #1
	strgt	r0, [r8, r3, lsl #2]
.L13:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L14
	ldr	r4, [sp]
.L12:
	cmp	r7, lr
	ldrne	r0, [r4, #4]!
	bne	.L9
.L15:
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
	movw	r8, #:lower16:num
	movt	r8, #:upper16:num
	sub	sp, sp, #12
	ldr	r3, [r8]
	strd	r0, [sp]
	cmp	r3, #0
	ble	.L24
	movw	r2, #:lower16:flow
	movt	r2, #:upper16:flow
	lsl	ip, r3, #2
	movw	r0, #4004
	mla	r0, r0, r3, r2
	add	r2, r2, ip
	rsb	ip, ip, #0
	mov	r1, #0
.L26:
	add	r3, r2, ip
.L25:
	str	r1, [r3], #4
	cmp	r3, r2
	bne	.L25
	add	r2, r2, #4000
	cmp	r2, r0
	bne	.L26
.L24:
	ldrd	r0, [sp]
	movw	r5, #:lower16:pred
	bl	bfs
	movw	r4, #:lower16:flow
	movw	r6, #:lower16:capacity
	movt	r5, #:upper16:pred
	movt	r4, #:upper16:flow
	movt	r6, #:upper16:capacity
	mov	r7, #0
	cmp	r0, #0
	beq	.L38
.L31:
	ldr	ip, [r8]
	mov	r3, #51712
	sub	ip, ip, #1
	ldr	r2, [r5, ip, lsl #2]
	cmp	r2, #0
	blt	.L32
	movt	r3, 15258
	mov	r10, ip
	mov	r0, r2
	mov	fp, #1000
.L29:
	mla	r9, fp, r0, r10
	ldr	lr, [r5, r0, lsl #2]
	mov	r10, r0
	mov	r0, lr
	ldr	r1, [r6, r9, lsl #2]
	ldr	r9, [r4, r9, lsl #2]
	sub	r1, r1, r9
	cmp	r3, r1
	movge	r3, r1
	cmp	lr, #0
	bge	.L29
	mov	lr, #1000
.L30:
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
	bge	.L30
	add	r7, r7, r3
.L39:
	ldrd	r0, [sp]
	bl	bfs
	cmp	r0, #0
	bne	.L31
.L38:
	mov	r0, r7
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L32:
	movt	r3, 15258
	add	r7, r7, r3
	b	.L39
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
	push	{r4, r5, r6, lr}
	movw	r5, #:lower16:num
	movt	r5, #:upper16:num
	movw	r0, #:lower16:capacity
	movt	r0, #:upper16:capacity
	ldr	ip, [r5]
	cmp	ip, #0
	ble	.L41
	movw	r3, #4004
	lsl	lr, ip, #2
	mla	ip, r3, ip, r0
	add	r2, r0, lr
	rsb	lr, lr, #0
	mov	r1, #0
.L43:
	add	r3, r2, lr
.L42:
	str	r1, [r3], #4
	cmp	r3, r2
	bne	.L42
	add	r2, r2, #4000
	cmp	r2, ip
	bne	.L43
.L41:
	ldr	r3, .L49
	mov	r4, #1
	str	r4, [r0, #4]
	movw	r2, #:lower16:e
	add	r1, r3, #4096
	add	ip, r3, #20480
	str	r4, [r0, #8]
	add	lr, r3, #24576
	str	r4, [r1, #3840]
	movt	r2, #:upper16:e
	str	r4, [r1, #3848]
	str	r4, [r1, #3856]
	add	r1, r3, #28672
	str	r4, [r0, #12]
	str	r4, [r0, #16]
	str	r4, [r0, #20]
	str	r4, [r0, #24]
	str	r4, [r0, #28]
	str	r4, [r0, #4036]
	str	r4, [r0, #4052]
	add	r0, r3, #32768
	str	r4, [ip, #3476]
	add	ip, r3, #36864
	str	r4, [r1, #3292]
	add	r1, r3, #8192
	str	r4, [r0, #3196]
	add	r0, r3, #12288
	str	r4, [r3, #3940]
	str	r4, [r3, #3948]
	str	r4, [lr, #3388]
	add	lr, r3, #40960
	str	r4, [ip, #3100]
	mov	ip, #33
	str	ip, [r2]
	add	r2, r3, #16384
	add	ip, r3, #45056
	add	r3, r3, #49152
	str	r4, [r1, #3744]
	str	r4, [r1, #3752]
	str	r4, [r1, #3760]
	mov	r1, #15
	str	r4, [r0, #3652]
	str	r4, [r0, #3660]
	str	r4, [r0, #3668]
	mov	r0, #0
	str	r4, [r2, #3560]
	str	r4, [r2, #3564]
	str	r4, [r2, #3568]
	str	r4, [r2, #3572]
	str	r4, [r2, #3576]
	mov	r2, #16
	str	r2, [r5]
	str	r4, [lr, #3004]
	str	r4, [ip, #2908]
	str	r4, [r3, #2812]
	bl	fordFulkerson
	movw	r1, #:lower16:.LC0
	movt	r1, #:upper16:.LC0
	mov	r2, r0
	mov	r0, r4
	bl	__printf_chk
	mov	r0, #0
	pop	{r4, r5, r6, pc}
.L50:
	.align	2
.L49:
	.word	capacity+4096
	.size	main, .-main
	.comm	q,4008,4
	.comm	tail,4,4
	.comm	head,4,4
	.comm	pred,4000,4
	.comm	color,4000,4
	.comm	flow,4000000,4
	.comm	capacity,4000000,4
	.comm	e,4,4
	.comm	num,4,4
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
