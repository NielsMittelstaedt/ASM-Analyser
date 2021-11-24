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
	.file	"multikey_quick_sort.c"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"apple\000"
	.align	2
.LC1:
	.ascii	"cat\000"
	.align	2
.LC2:
	.ascii	"boy\000"
	.text
	.align	2
	.global	vecswap
	.syntax unified
	.arm
	.fpu softvfp
	.type	vecswap, %function
vecswap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r2, #0
	bxle	lr
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	lsl	r4, r0, #2
	lsl	ip, r1, #2
	sub	r6, r2, #1
	mov	r5, r4
	add	r7, ip, #8
	add	r4, r4, #8
	add	lr, r3, r5
	cmp	r7, r5
	cmpgt	r4, ip
	add	ip, r3, ip
	orr	r5, ip, lr
	movle	r4, #1
	movgt	r4, #0
	cmp	r6, #6
	movls	r4, #0
	andhi	r4, r4, #1
	tst	r5, #7
	movne	r4, #0
	cmp	r4, #0
	beq	.L3
	lsr	r10, r2, #1
	sub	lr, lr, #8
	sub	r9, ip, #8
	add	r10, ip, r10, lsl #3
	mov	r8, lr
.L4:
	ldrd	r4, [lr, #8]!
	ldrd	r6, [r9, #8]!
	strd	r6, [r8, #8]!
	strd	r4, [ip], #8
	cmp	ip, r10
	bne	.L4
	bic	ip, r2, #1
	cmp	r2, ip
	add	r0, r0, ip
	add	r1, r1, ip
	ldrne	r2, [r3, r0, lsl #2]
	ldrne	ip, [r3, r1, lsl #2]
	strne	ip, [r3, r0, lsl #2]
	strne	r2, [r3, r1, lsl #2]
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L3:
	add	r0, r2, r0
	add	r3, r3, r0, lsl #2
.L6:
	ldr	r1, [ip]
	ldr	r2, [lr]
	str	r1, [lr], #4
	cmp	lr, r3
	str	r2, [ip], #4
	bne	.L6
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
	.size	vecswap, .-vecswap
	.global	__aeabi_idivmod
	.align	2
	.global	ssort1
	.syntax unified
	.arm
	.fpu softvfp
	.type	ssort1, %function
ssort1:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	cmp	r1, #1
	sub	sp, sp, #20
	str	r1, [sp]
	ble	.L15
	mov	r6, r0
	mov	r7, r2
	add	r3, r2, #1
	str	r3, [sp, #12]
.L47:
	bl	rand
	ldr	r4, [sp]
	mov	r10, r6
	mov	fp, #0
	mov	r5, #1
	mov	r1, r4
	bl	__aeabi_idivmod
	ldr	r3, [r6]
	sub	r0, r4, #1
	mov	r4, r0
	ldr	r2, [r6, r1, lsl #2]
	str	r2, [r6]
	str	r3, [r6, r1, lsl #2]
	ldr	r3, [r6]
	ldrb	r9, [r3, r7]	@ zero_extendqisi2
.L17:
	ldr	r2, [r10, #4]!
	mov	lr, fp
	add	fp, fp, #1
	ldrb	r3, [r2, r7]	@ zero_extendqisi2
	mov	ip, fp
	sub	r3, r3, r9
	cmp	r3, #0
	ble	.L20
	cmp	fp, r0
	bgt	.L19
	add	r2, r6, r0, lsl #2
	b	.L23
.L27:
	ldreq	r3, [r6, r4, lsl #2]
	sub	r0, r0, #1
	streq	r3, [r2, #4]
	streq	r1, [r6, r4, lsl #2]
	subeq	r4, r4, #1
	cmp	r0, lr
	beq	.L19
.L23:
	mov	r8, r2
	ldr	r1, [r2], #-4
	ldrb	r3, [r1, r7]	@ zero_extendqisi2
	sub	r3, r3, r9
	cmp	r3, #0
	bge	.L27
	ldr	r3, [r10]
	add	ip, lr, #2
	sub	r0, r0, #1
	str	r1, [r10]
	str	r3, [r8]
.L48:
	cmp	ip, r0
	ble	.L17
.L19:
	sub	r8, ip, r5
	cmp	r8, r5
	movlt	lr, r8
	movge	lr, r5
	cmp	lr, #0
	sub	r9, ip, lr
	sub	r10, lr, #1
	ble	.L32
	lsl	r2, r9, #2
	add	r3, r6, #8
	add	r1, r6, r2
	add	r2, r2, #8
	cmp	r1, r3
	orr	fp, r6, r1
	movcc	r3, #0
	movcs	r3, #1
	cmp	r2, #0
	orrle	r3, r3, #1
	cmp	r10, #6
	movls	r3, #0
	andhi	r3, r3, #1
	tst	fp, #7
	movne	r3, #0
	cmp	r3, #0
	beq	.L29
	lsr	r10, lr, #1
	sub	fp, r6, #8
	str	r5, [sp, #4]
	add	r10, r1, r10, lsl #3
	str	r4, [sp, #8]
.L30:
	ldrd	r2, [fp, #8]!
	ldrd	r4, [r1]
	strd	r4, [fp]
	strd	r2, [r1], #8
	cmp	r10, r1
	bne	.L30
	bic	r3, lr, #1
	ldr	r5, [sp, #4]
	cmp	lr, r3
	ldr	r4, [sp, #8]
	add	r9, r3, r9
	ldrne	r2, [r6, r3, lsl #2]
	ldrne	r1, [r6, r9, lsl #2]
	strne	r1, [r6, r3, lsl #2]
	strne	r2, [r6, r9, lsl #2]
.L32:
	ldr	r3, [sp]
	sub	r9, r4, r0
	sub	r1, r3, r4
	cmp	r1, r9
	movgt	r1, r9
	suble	r1, r1, #1
.L25:
	cmp	r1, #0
	sub	fp, r3, r1
	sub	r10, r1, #1
	ble	.L42
	lsl	lr, ip, #2
	lsl	r3, fp, #2
	add	r0, lr, #8
	add	r2, r6, lr
	str	r2, [sp, #4]
	add	r2, r3, #8
	cmp	lr, r2
	cmplt	r3, r0
	ldr	r2, [sp, #4]
	add	lr, r6, r3
	orr	r3, lr, r2
	movge	r0, #1
	movlt	r0, #0
	cmp	r10, #6
	movls	r0, #0
	andhi	r0, r0, #1
	tst	r3, #7
	movne	r0, #0
	cmp	r0, #0
	beq	.L39
	lsr	r10, r1, #1
	sub	r0, r2, #8
	str	r5, [sp, #4]
	add	r10, lr, r10, lsl #3
	str	r4, [sp, #8]
.L40:
	ldrd	r2, [r0, #8]!
	ldrd	r4, [lr]
	strd	r4, [r0]
	strd	r2, [lr], #8
	cmp	lr, r10
	bne	.L40
	bic	r3, r1, #1
	ldr	r5, [sp, #4]
	cmp	r3, r1
	add	ip, r3, ip
	ldr	r4, [sp, #8]
	add	r3, fp, r3
	ldrne	r2, [r6, ip, lsl #2]
	ldrne	r1, [r6, r3, lsl #2]
	strne	r1, [r6, ip, lsl #2]
	strne	r2, [r6, r3, lsl #2]
.L42:
	mov	r0, r6
	mov	r2, r7
	mov	r1, r8
	bl	ssort1
	ldr	r3, [r6, r8, lsl #2]
	add	r0, r6, r8, lsl #2
	ldrb	r3, [r3, r7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L59
.L38:
	ldr	r3, [sp]
	cmp	r9, #1
	sub	r3, r3, r9
	add	r6, r6, r3, lsl #2
	ble	.L15
	str	r9, [sp]
	b	.L47
.L20:
	ldreq	r3, [r6, r5, lsl #2]
	add	ip, lr, #2
	streq	r2, [r6, r5, lsl #2]
	addeq	r5, r5, #1
	streq	r3, [r10]
	b	.L48
.L29:
	add	lr, r6, lr, lsl #2
	mov	r3, r6
.L34:
	ldr	r9, [r1]
	ldr	r2, [r3]
	str	r9, [r3], #4
	cmp	lr, r3
	str	r2, [r1], #4
	bne	.L34
	b	.L32
.L59:
	ldr	r3, [sp]
	ldr	r2, [sp, #12]
	add	r1, r3, r5
	sub	r1, r1, r4
	sub	r1, r1, #1
	bl	ssort1
	b	.L38
.L15:
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L39:
	add	r1, r1, ip
	mov	r3, lr
	add	r1, r6, r1, lsl #2
.L44:
	ldr	ip, [r3]
	ldr	r0, [r2]
	str	ip, [r2], #4
	cmp	r2, r1
	str	r0, [r3], #4
	bne	.L44
	b	.L42
	.size	ssort1, .-ssort1
	.align	2
	.global	ssort1main
	.syntax unified
	.arm
	.fpu softvfp
	.type	ssort1main, %function
ssort1main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r2, #0
	b	ssort1
	.size	ssort1main, .-ssort1main
	.align	2
	.global	vecswap2
	.syntax unified
	.arm
	.fpu softvfp
	.type	vecswap2, %function
vecswap2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r2, #0
	bxle	lr
	add	r3, r0, #7
	sub	ip, r2, #1
	sub	r3, r3, r1
	cmp	r3, #14
	cmphi	ip, #6
	push	{r4, r5, r6, r7, r8, lr}
	orr	lr, r0, r1
	movhi	r3, #1
	movls	r3, #0
	tst	lr, #7
	movne	r3, #0
	cmp	r3, #0
	beq	.L63
	lsr	r8, r2, #1
	sub	lr, r0, #8
	mov	ip, r1
	mov	r3, #0
.L64:
	ldrd	r6, [lr, #8]!
	add	r3, r3, #1
	ldrd	r4, [ip]
	cmp	r3, r8
	strd	r4, [lr]
	strd	r6, [ip], #8
	bne	.L64
	tst	r2, #1
	bic	r2, r2, #1
	ldrne	r3, [r0, r2, lsl #2]
	ldrne	ip, [r1, r2, lsl #2]
	strne	ip, [r0, r2, lsl #2]
	strne	r3, [r1, r2, lsl #2]
	pop	{r4, r5, r6, r7, r8, pc}
.L63:
	ldr	r3, [r0]
	sub	ip, ip, #1
	ldr	r2, [r1]
	cmn	ip, #1
	str	r2, [r0], #4
	str	r3, [r1], #4
	bne	.L63
	pop	{r4, r5, r6, r7, r8, pc}
	.size	vecswap2, .-vecswap2
	.align	2
	.global	med3func
	.syntax unified
	.arm
	.fpu softvfp
	.type	med3func, %function
med3func:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	ldr	ip, [r1]
	ldr	lr, [r0]
	ldrb	ip, [ip, r3]	@ zero_extendqisi2
	ldrb	lr, [lr, r3]	@ zero_extendqisi2
	cmp	lr, ip
	popeq	{r4, pc}
	ldr	r4, [r2]
	ldrb	r3, [r4, r3]	@ zero_extendqisi2
	cmp	ip, r3
	cmpne	lr, r3
	beq	.L79
	cmp	lr, ip
	bge	.L77
	cmp	ip, r3
	blt	.L82
	cmp	lr, r3
	movlt	r0, r2
	pop	{r4, pc}
.L79:
	mov	r0, r2
	pop	{r4, pc}
.L77:
	cmp	ip, r3
	ble	.L85
.L82:
	mov	r0, r1
	pop	{r4, pc}
.L85:
	cmp	lr, r3
	movge	r0, r2
	pop	{r4, pc}
	.size	med3func, .-med3func
	.align	2
	.global	inssort
	.syntax unified
	.arm
	.fpu softvfp
	.type	inssort, %function
inssort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	sub	r6, r1, #1
	cmp	r6, #0
	pople	{r4, r5, r6, r7, r8, pc}
	add	r7, r0, #4
	mov	r8, r0
	mov	lr, r2
.L87:
	cmp	r8, r7
	movcc	ip, r7
	bcs	.L92
.L93:
	ldr	r5, [ip, #-4]
	ldr	r4, [ip], #-4
	add	r0, r5, lr
	ldrb	r3, [r5, lr]	@ zero_extendqisi2
	add	r1, r4, lr
	ldrb	r2, [r4, lr]	@ zero_extendqisi2
	cmp	r2, r3
	beq	.L90
	b	.L89
.L91:
	ldrb	r3, [r0, #1]!	@ zero_extendqisi2
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	cmp	r3, r2
	bne	.L89
.L90:
	cmp	r3, #0
	bne	.L91
.L92:
	subs	r6, r6, #1
	add	r7, r7, #4
	bne	.L87
	pop	{r4, r5, r6, r7, r8, pc}
.L89:
	cmp	r2, r3
	bcs	.L92
	cmp	ip, r8
	strd	r4, [ip]
	bhi	.L93
	b	.L92
	.size	inssort, .-inssort
	.align	2
	.global	ssort2
	.syntax unified
	.arm
	.fpu softvfp
	.type	ssort2, %function
ssort2:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #9
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r8, r1
	sub	sp, sp, #36
	mov	fp, r0
	mov	r6, r2
	ble	.L154
.L155:
	asr	r3, r8, #1
	ldr	r0, [fp]
	sub	r10, r8, #-1073741823
	cmp	r8, #30
	ldr	r9, [fp, r3, lsl #2]
	add	r3, fp, r3, lsl #2
	lsl	r10, r10, #2
	ldrb	r1, [r0, r6]	@ zero_extendqisi2
	add	r4, fp, r10
	str	r8, [sp, #16]
	ldrb	r2, [r9, r6]	@ zero_extendqisi2
	ble	.L156
	asr	lr, r8, #3
	ldr	r5, [fp, lr, lsl #2]
	lsl	ip, lr, #2
	add	r8, fp, ip
	lsl	r7, lr, #3
	str	r7, [sp, #8]
	add	r7, r8, ip
	str	r5, [sp, #12]
	ldrb	r5, [r5, r6]	@ zero_extendqisi2
	str	r7, [sp]
	cmp	r5, r1
	beq	.L160
	ldr	r7, [r8, lr, lsl #2]
	str	r7, [sp, #4]
	ldrb	r7, [r7, r6]	@ zero_extendqisi2
	cmp	r7, r1
	cmpne	r5, r7
	beq	.L162
	cmp	r5, r1
	ble	.L115
	cmp	r5, r7
	bge	.L198
.L161:
	mov	r1, r5
	ldr	r5, [sp, #12]
	str	r8, [sp]
	str	r5, [sp, #4]
.L114:
	rsb	r5, ip, #0
	sub	r7, r3, ip
	str	r7, [sp, #12]
	add	ip, r3, ip
	ldr	r7, [r3, r5]
	str	ip, [sp, #20]
	ldrb	ip, [r7, r6]	@ zero_extendqisi2
	cmp	ip, r2
	beq	.L195
	ldr	r8, [r3, lr, lsl #2]
	ldrb	lr, [r8, r6]	@ zero_extendqisi2
	cmp	lr, r2
	cmpne	ip, lr
	beq	.L166
	cmp	ip, r2
	bge	.L117
	cmp	lr, r2
	ble	.L199
.L116:
	ldr	ip, [sp, #8]
	add	r8, r4, r5
	ldr	lr, [r4, r5]
	sub	ip, r4, ip
	ldr	r7, [ip]
	ldrb	r5, [lr, r6]	@ zero_extendqisi2
	ldrb	lr, [r7, r6]	@ zero_extendqisi2
	cmp	lr, r5
	beq	.L113
	ldr	r7, [r4]
	ldrb	r7, [r7, r6]	@ zero_extendqisi2
	cmp	lr, r7
	cmpne	r5, r7
	moveq	ip, r4
	beq	.L113
	cmp	lr, r5
	bge	.L118
	cmp	r5, r7
	bge	.L200
.L170:
	mov	ip, r8
.L113:
	cmp	r1, r2
	beq	.L171
.L205:
	ldr	lr, [ip]
	ldrb	r5, [lr, r6]	@ zero_extendqisi2
	cmp	r5, r1
	cmpne	r5, r2
	beq	.L119
	cmp	r1, r2
	bge	.L120
	cmp	r5, r2
	bgt	.L173
	ldr	r3, [sp, #4]
	cmp	r5, r1
	movle	lr, r3
	ldr	r3, [sp]
	movle	ip, r3
.L119:
	mov	r2, fp
	str	lr, [r2], #4
	cmp	r4, r2
	str	r0, [ip]
	bcc	.L201
	ldr	r1, [fp]
	mov	r3, r2
	mov	r7, r2
	mov	lr, fp
	mov	r5, r4
	ldrb	r8, [r1, r6]	@ zero_extendqisi2
.L124:
	ldr	r0, [lr, #4]!
	mov	r2, r3
	add	r3, r3, #4
	ldrb	r1, [r0, r6]	@ zero_extendqisi2
	sub	r1, r1, r8
	cmp	r1, #0
	ble	.L126
	cmp	lr, r4
	bhi	.L197
	mov	r1, r4
	b	.L129
.L130:
	ldreq	r0, [r5]
	streq	r0, [r1, #4]
	streq	ip, [r5], #-4
	cmp	r1, lr
	bcc	.L202
.L129:
	mov	r4, r1
	ldr	ip, [r1], #-4
	ldrb	r0, [ip, r6]	@ zero_extendqisi2
	sub	r0, r0, r8
	cmp	r0, #0
	bge	.L130
	cmp	lr, r4
	bhi	.L197
	ldr	r1, [lr]
	mov	r2, r3
	str	ip, [lr]
	str	r1, [r4], #-4
.L132:
	cmp	r4, r3
	bcs	.L124
	sub	r4, r5, r4
	sub	r3, r3, r7
	sub	r1, r7, fp
	str	r1, [sp, #4]
	asr	r8, r4, #2
	add	r1, fp, r3
	str	r1, [sp]
	asr	r1, r3, #2
	str	r1, [sp, #8]
.L125:
	ldr	r1, [sp, #4]
	add	r0, r10, #4
	str	r0, [sp, #20]
	add	r0, fp, r0
	cmp	r1, r3
	str	r0, [sp, #12]
	asrle	ip, r1, #2
	ldrgt	ip, [sp, #8]
.L133:
	cmp	ip, #0
	lsl	r0, ip, #2
	sub	r7, r2, r0
	sub	r10, ip, #1
	ble	.L140
	rsb	r1, r0, #8
	add	r9, fp, #8
	add	r1, r2, r1
	orr	lr, r7, fp
	cmp	r7, r9
	cmpcc	fp, r1
	movcs	r1, #1
	movcc	r1, #0
	cmp	r10, #6
	movls	r1, #0
	andhi	r1, r1, #1
	tst	lr, #7
	movne	r1, #0
	cmp	r1, #0
	beq	.L137
	lsr	r10, ip, #1
	sub	r9, fp, #8
	mov	lr, r7
	strd	r2, [sp, #24]
	add	r10, r7, r10, lsl #3
.L138:
	ldrd	r0, [r9, #8]!
	ldrd	r2, [lr]
	strd	r2, [r9]
	strd	r0, [lr], #8
	cmp	r10, lr
	bne	.L138
	tst	ip, #1
	ldrd	r2, [sp, #24]
	bic	ip, ip, #1
	ldrne	r1, [fp, ip, lsl #2]
	ldrne	r0, [r7, ip, lsl #2]
	strne	r0, [fp, ip, lsl #2]
	strne	r1, [r7, ip, lsl #2]
.L140:
	ldr	r1, [sp, #12]
	sub	r1, r1, r5
	cmp	r1, r4
	movgt	ip, r8
	asrle	r1, r1, #2
	suble	ip, r1, #1
.L135:
	ldr	r1, [sp, #12]
	cmp	ip, #0
	lsl	lr, ip, #2
	sub	r9, ip, #1
	sub	r7, r1, lr
	ble	.L150
	ldr	r1, [sp, #20]
	add	r0, r2, #8
	sub	lr, r1, lr
	add	r1, lr, #8
	add	lr, fp, lr
	add	r1, fp, r1
	orr	r10, lr, r2
	cmp	lr, r0
	cmpcc	r2, r1
	movcs	r1, #1
	movcc	r1, #0
	cmp	r9, #6
	movls	r1, #0
	andhi	r1, r1, #1
	tst	r10, #7
	movne	r1, #0
	cmp	r1, #0
	beq	.L193
	lsr	r10, ip, #1
	sub	r9, r2, #8
	strd	r2, [sp, #20]
	add	r10, lr, r10, lsl #3
.L148:
	ldrd	r0, [r9, #8]!
	ldrd	r2, [lr]
	strd	r2, [r9]
	strd	r0, [lr], #8
	cmp	lr, r10
	bne	.L148
	tst	ip, #1
	ldrd	r2, [sp, #20]
	bic	ip, ip, #1
	ldrne	r1, [r2, ip, lsl #2]
	ldrne	r0, [r7, ip, lsl #2]
	strne	r0, [r2, ip, lsl #2]
	strne	r1, [r7, ip, lsl #2]
.L150:
	cmp	r3, #4
	bgt	.L203
.L146:
	ldr	r3, [sp]
	ldr	r3, [r3]
	ldrb	r3, [r3, r6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L204
.L153:
	cmp	r4, #4
	ble	.L102
	ldr	r3, [sp, #16]
	cmp	r4, #36
	sub	r3, r3, r8
	add	fp, fp, r3, lsl #2
	bgt	.L155
.L154:
	cmp	r8, #1
	add	r5, fp, #4
	addgt	r7, fp, r8, lsl #2
	ble	.L102
.L109:
	cmp	fp, r5
	movcc	ip, r5
	bcs	.L110
.L111:
	ldr	r4, [ip, #-4]
	ldr	lr, [ip], #-4
	add	r0, r4, r6
	ldrb	r3, [r4, r6]	@ zero_extendqisi2
	add	r1, lr, r6
	ldrb	r2, [lr, r6]	@ zero_extendqisi2
	cmp	r3, r2
	beq	.L107
	b	.L106
.L108:
	ldrb	r3, [r0, #1]!	@ zero_extendqisi2
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	cmp	r3, r2
	bne	.L106
.L107:
	cmp	r3, #0
	bne	.L108
.L110:
	add	r5, r5, #4
	cmp	r7, r5
	bne	.L109
.L102:
	add	sp, sp, #36
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L106:
	cmp	r2, r3
	bcs	.L110
	cmp	ip, fp
	str	r4, [ip, #4]
	str	lr, [ip]
	bhi	.L111
	add	r5, r5, #4
	cmp	r7, r5
	bne	.L109
	b	.L102
.L126:
	ldreq	r2, [r7]
	streq	r0, [r7], #4
	streq	r2, [lr]
	mov	r2, r3
	b	.L132
.L201:
	mov	r8, #0
	add	r3, r10, #4
	mov	r5, r4
	mov	r1, #4
	str	r3, [sp, #20]
	mov	r4, r8
	add	r3, fp, r3
	mov	ip, r8
	str	r3, [sp, #12]
	mov	r3, r8
	str	r8, [sp, #8]
	str	fp, [sp]
	str	r1, [sp, #4]
	b	.L133
.L156:
	cmp	r1, r2
	mov	ip, r4
	str	r0, [sp, #4]
	str	fp, [sp]
	bne	.L205
.L171:
	ldm	sp, {ip, lr}
	b	.L119
.L204:
	ldr	r2, [sp, #4]
	ldr	r3, [sp, #12]
	ldr	r0, [sp]
	add	r1, r3, r2
	add	r2, r6, #1
	sub	r1, r1, r5
	asr	r1, r1, #2
	sub	r1, r1, #1
	bl	ssort2
	b	.L153
.L203:
	ldr	r1, [sp, #8]
	mov	r2, r6
	mov	r0, fp
	bl	ssort2
	b	.L146
.L173:
	mov	lr, r9
	mov	ip, r3
	b	.L119
.L120:
	cmp	r5, r2
	blt	.L173
	ldr	r3, [sp, #4]
	cmp	r5, r1
	movle	r3, lr
	mov	lr, r3
	ldr	r3, [sp]
	movle	r3, ip
	mov	ip, r3
	b	.L119
.L115:
	cmp	r5, r7
	bgt	.L161
	cmp	r7, r1
	bgt	.L160
.L162:
	mov	r1, r7
	b	.L114
.L117:
	cmp	lr, r2
	blt	.L116
	cmp	ip, lr
	blt	.L165
.L166:
	ldr	r3, [sp, #20]
	mov	r2, lr
	mov	r9, r8
	b	.L116
.L193:
	ldr	ip, [sp, #12]
.L147:
	ldr	r1, [r2]
	ldr	r0, [r7]
	str	r0, [r2], #4
	str	r1, [r7], #4
	cmp	ip, r7
	bne	.L147
	b	.L150
.L137:
	add	r0, fp, r0
	mov	r1, fp
.L142:
	ldr	lr, [r7]
	ldr	ip, [r1]
	str	lr, [r1], #4
	cmp	r1, r0
	str	ip, [r7], #4
	bne	.L142
	b	.L140
.L199:
	cmp	ip, lr
	blt	.L166
.L165:
	mov	r2, ip
.L195:
	ldr	r3, [sp, #12]
	mov	r9, r7
	b	.L116
.L198:
	cmp	r7, r1
	bgt	.L162
.L160:
	str	r0, [sp, #4]
	str	fp, [sp]
	b	.L114
.L118:
	cmp	r5, r7
	bgt	.L170
	cmp	lr, r7
	movge	ip, r4
	b	.L113
.L200:
	cmp	lr, r7
	movlt	ip, r4
	b	.L113
.L197:
	sub	r4, r5, r4
.L196:
	sub	r3, r2, r7
	sub	r1, r7, fp
	asr	r8, r4, #2
	str	r1, [sp, #4]
	add	r1, fp, r3
	str	r1, [sp]
	asr	r1, r3, #2
	str	r1, [sp, #8]
	b	.L125
.L202:
	sub	r4, r5, r1
	b	.L196
	.size	ssort2, .-ssort2
	.align	2
	.global	ssort2main
	.syntax unified
	.arm
	.fpu softvfp
	.type	ssort2main, %function
ssort2main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r2, #0
	b	ssort2
	.size	ssort2main, .-ssort2main
	.align	2
	.global	insert1
	.syntax unified
	.arm
	.fpu softvfp
	.type	insert1, %function
insert1:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L217
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, r3
	bcc	.L218
	beq	.L219
	ldr	r0, [r4, #12]
	mov	r6, r4
	bl	insert1
	str	r0, [r4, #12]
.L207:
	mov	r0, r6
	pop	{r4, r5, r6, pc}
.L218:
	ldr	r0, [r4, #4]
	mov	r6, r4
	bl	insert1
	str	r0, [r4, #4]
	mov	r0, r6
	pop	{r4, r5, r6, pc}
.L217:
	mov	r0, #16
	bl	malloc
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r6, r0
	str	r4, [r0, #12]
	str	r4, [r0, #8]
	str	r4, [r0, #4]
	strb	r3, [r0]
.L209:
	cmp	r3, #0
	beq	.L207
	ldr	r0, [r6, #8]
	add	r1, r5, #1
	bl	insert1
	str	r0, [r6, #8]
	mov	r0, r6
	pop	{r4, r5, r6, pc}
.L219:
	mov	r6, r4
	b	.L209
	.size	insert1, .-insert1
	.align	2
	.global	cleanup1
	.syntax unified
	.arm
	.fpu softvfp
	.type	cleanup1, %function
cleanup1:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	subs	r4, r0, #0
	popeq	{r4, pc}
	ldr	r0, [r4, #4]
	bl	cleanup1
	ldr	r0, [r4, #8]
	bl	cleanup1
	ldr	r0, [r4, #12]
	bl	cleanup1
	mov	r0, r4
	pop	{r4, lr}
	b	free
	.size	cleanup1, .-cleanup1
	.align	2
	.global	insert2
	.syntax unified
	.arm
	.fpu softvfp
	.type	insert2, %function
insert2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}
	movw	r3, #:lower16:root
	movt	r3, #:upper16:root
	mov	r7, r0
	mov	r5, r0
	ldr	r1, [r3]
	add	r6, r1, #4
	add	ip, r1, #8
	mov	lr, r1
	ldrb	r0, [lr], #12	@ zero_extendqisi2
	b	.L228
.L247:
	cmp	r3, #0
	add	r5, r5, #1
	popeq	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	ldr	r3, [r4]
	cmp	r3, r1
	bne	.L246
.L228:
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r4, ip
	sub	r2, r3, r0
	cmp	r2, #0
	beq	.L247
	mov	r4, lr
	movlt	r4, r6
	ldr	r3, [r4]
	cmp	r3, r1
	beq	.L228
.L246:
	movw	r9, #:lower16:bufn
	movt	r9, #:upper16:bufn
	movw	r8, #:lower16:buffer
	movw	r10, #:lower16:freen
	movw	fp, #:lower16:freearr
	ldr	r6, [r9]
	movt	r8, #:upper16:buffer
	movt	r10, #:upper16:freen
	movt	fp, #:upper16:freearr
	b	.L233
.L248:
	ldr	r0, [r8]
	add	r1, r0, #16
	str	r1, [r8]
	str	r0, [r4]
	ldrb	r1, [r5]	@ zero_extendqisi2
	str	r2, [r0, #12]
	str	r2, [r0, #8]
	strb	r1, [r0]
	str	r2, [r0, #4]
	ldrb	r2, [r5], #1	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L230
.L231:
	add	r4, r0, #8
	mov	r6, r3
.L233:
	mov	r2, #0
	cmp	r6, r2
	sub	r3, r6, #1
	str	r3, [r9]
	bne	.L248
	mov	r0, #16000
	bl	malloc
	ldr	r3, [r10]
	add	r2, r0, #16
	str	r0, [fp, r3, lsl #2]
	str	r2, [r8]
	add	r2, r3, #1
	movw	r3, #999
	str	r2, [r10]
	str	r3, [r9]
	str	r0, [r4]
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldrb	r1, [r5], #1	@ zero_extendqisi2
	str	r6, [r0, #12]
	cmp	r1, #0
	str	r6, [r0, #8]
	str	r6, [r0, #4]
	strb	r2, [r0]
	bne	.L231
.L230:
	movw	r3, #:lower16:.LANCHOR0
	movt	r3, #:upper16:.LANCHOR0
	ldr	r3, [r3]
	cmp	r3, #0
	strne	r7, [r0, #8]
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	insert2, .-insert2
	.align	2
	.global	cleanup2
	.syntax unified
	.arm
	.fpu softvfp
	.type	cleanup2, %function
cleanup2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movw	r6, #:lower16:freen
	movt	r6, #:upper16:freen
	ldr	r3, [r6]
	cmp	r3, #0
	pople	{r4, r5, r6, pc}
	movw	r5, #:lower16:freearr
	movt	r5, #:upper16:freearr
	mov	r4, #0
.L251:
	ldr	r0, [r5], #4
	add	r4, r4, #1
	bl	free
	ldr	r3, [r6]
	cmp	r3, r4
	bgt	.L251
	pop	{r4, r5, r6, pc}
	.size	cleanup2, .-cleanup2
	.align	2
	.global	search1
	.syntax unified
	.arm
	.fpu softvfp
	.type	search1, %function
search1:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movw	r3, #:lower16:root
	movt	r3, #:upper16:root
	ldr	r3, [r3]
.L263:
	cmp	r3, #0
	beq	.L260
.L264:
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldrb	r2, [r0]	@ zero_extendqisi2
	cmp	r2, r1
	ldrcc	r3, [r3, #4]
	bcc	.L263
	ldrne	r3, [r3, #12]
	bne	.L263
	cmp	r2, #0
	add	r0, r0, #1
	beq	.L261
	ldr	r3, [r3, #8]
	cmp	r3, #0
	bne	.L264
.L260:
	mov	r0, r3
	bx	lr
.L261:
	mov	r0, #1
	bx	lr
	.size	search1, .-search1
	.align	2
	.global	search2
	.syntax unified
	.arm
	.fpu softvfp
	.type	search2, %function
search2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movw	r3, #:lower16:root
	movt	r3, #:upper16:root
	ldrb	r1, [r0]	@ zero_extendqisi2
	ldr	r3, [r3]
.L274:
	cmp	r3, #0
	beq	.L271
.L275:
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	r2, r1, r2
	cmp	r2, #0
	bne	.L267
	cmp	r1, #0
	beq	.L272
	ldr	r3, [r3, #8]
	add	r0, r0, #1
	ldrb	r1, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L275
.L271:
	mov	r0, r3
	bx	lr
.L267:
	ldrlt	r3, [r3, #4]
	ldrge	r3, [r3, #12]
	b	.L274
.L272:
	mov	r0, #1
	bx	lr
	.size	search2, .-search2
	.align	2
	.global	pmsearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	pmsearch, %function
pmsearch:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	subs	r4, r0, #0
	popeq	{r4, r5, r6, r7, r8, r9, r10, pc}
	movw	r9, #:lower16:nodecnt
	movw	r5, #:lower16:srchtop
	movw	r6, #:lower16:srcharr
	movt	r9, #:upper16:nodecnt
	movt	r5, #:upper16:srchtop
	add	r7, r1, #1
	movt	r6, #:upper16:srcharr
	mov	r8, r1
	b	.L277
.L278:
	ldr	r0, [r4, #4]
	mov	r1, r8
	bl	pmsearch
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r3, #46
	bne	.L308
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L289
.L287:
	ldr	r4, [r4, #12]
	cmp	r4, #0
	popeq	{r4, r5, r6, r7, r8, r9, r10, pc}
.L277:
	ldr	r3, [r9]
	add	r3, r3, #1
	str	r3, [r9]
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r3, #46
	beq	.L278
	ldrb	r2, [r4]	@ zero_extendqisi2
	cmp	r3, r2
	bcc	.L278
	cmp	r3, r2
	beq	.L309
.L281:
	cmp	r3, #0
	bne	.L288
	cmp	r2, #0
	popne	{r4, r5, r6, r7, r8, r9, r10, pc}
.L310:
	ldr	r3, [r5]
	ldr	r2, [r4, #8]
	add	r1, r3, #1
	str	r1, [r5]
	str	r2, [r6, r3, lsl #2]
	ldrb	r3, [r8]	@ zero_extendqisi2
.L283:
	cmp	r3, #46
	ldrbne	r2, [r4]	@ zero_extendqisi2
	beq	.L287
.L288:
	cmp	r3, r2
	bhi	.L287
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L308:
	ldrb	r2, [r4]	@ zero_extendqisi2
	cmp	r3, r2
	bne	.L281
.L309:
	cmp	r3, #0
	bne	.L289
.L304:
	ldrb	r2, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L310
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}
.L289:
	ldr	r0, [r4, #8]
	mov	r1, r7
	bl	pmsearch
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L304
	b	.L283
	.size	pmsearch, .-pmsearch
	.align	2
	.global	nearsearch
	.syntax unified
	.arm
	.fpu softvfp
	.type	nearsearch, %function
nearsearch:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r0, #0
	lsrne	r3, r2, #31
	moveq	r3, #1
	cmp	r3, #0
	bxne	lr
	cmp	r2, #0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	movw	r7, #:lower16:nodecnt
	movw	r8, #:lower16:srchtop
	movw	r9, #:lower16:srcharr
	movt	r7, #:upper16:nodecnt
	movt	r8, #:upper16:srchtop
	subne	r10, r2, #1
	movtne	r9, #:upper16:srcharr
	mov	r6, r2
	mov	r5, r1
	mov	r4, r0
	bne	.L313
	movt	r9, #:upper16:srcharr
	b	.L322
.L340:
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r0, [r4, #8]
	cmp	r3, #0
	moveq	r1, r5
	beq	.L317
	cmp	r6, r3
	add	r1, r5, #1
	moveq	r2, #0
	bne	.L317
.L319:
	bl	nearsearch
	ldrb	r6, [r4]	@ zero_extendqisi2
.L318:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, r6
	popls	{r4, r5, r6, r7, r8, r9, r10, pc}
	ldr	r4, [r4, #12]
	cmp	r4, #0
	popeq	{r4, r5, r6, r7, r8, r9, r10, pc}
.L322:
	ldr	r3, [r7]
	add	r3, r3, #1
	str	r3, [r7]
	ldrb	r6, [r4]	@ zero_extendqisi2
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, r6
	bcs	.L314
	ldr	r0, [r4, #4]
	mov	r2, #0
	mov	r1, r5
	bl	nearsearch
	ldrb	r6, [r4]	@ zero_extendqisi2
.L314:
	cmp	r6, #0
	bne	.L340
	mov	r0, r5
	bl	strlen
	cmp	r0, #0
	bne	.L318
	ldr	r3, [r8]
	ldr	r2, [r4, #8]
	add	r1, r3, #1
	str	r1, [r8]
	str	r2, [r9, r3, lsl #2]
	ldrb	r6, [r4]	@ zero_extendqisi2
	b	.L318
.L323:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r0, [r4, #8]
	cmp	r2, #0
	bne	.L341
	mov	r1, r5
.L325:
	mov	r2, r10
.L326:
	bl	nearsearch
.L324:
	ldr	r4, [r4, #12]
	cmp	r4, #0
	popeq	{r4, r5, r6, r7, r8, r9, r10, pc}
.L313:
	ldr	r3, [r7]
	mov	r2, r6
	ldr	r0, [r4, #4]
	mov	r1, r5
	add	r3, r3, #1
	str	r3, [r7]
	bl	nearsearch
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L323
	mov	r0, r5
	bl	strlen
	cmp	r0, r6
	bgt	.L324
	ldr	r3, [r8]
	ldr	r2, [r4, #8]
	add	r1, r3, #1
	str	r1, [r8]
	str	r2, [r9, r3, lsl #2]
	b	.L324
.L317:
	mvn	r2, #0
	b	.L319
.L341:
	cmp	r2, r3
	add	r1, r5, #1
	moveq	r2, r6
	beq	.L326
	b	.L325
	.size	nearsearch, .-nearsearch
	.section	.rodata.str1.4
	.align	2
.LC5:
	.ascii	"%s \000"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r2, #:lower16:.LANCHOR1
	movt	r2, #:upper16:.LANCHOR1
	push	{r4, r5, r6, lr}
	sub	sp, sp, #16
	ldm	r2, {r0, r1, r2}
	add	r3, sp, #4
	movw	r5, #:lower16:.LC5
	add	r6, sp, #16
	movt	r5, #:upper16:.LC5
	mov	r4, r3
	stm	r3, {r0, r1, r2}
	mov	r0, r3
	mov	r2, #0
	mov	r1, #3
	bl	ssort1
.L343:
	ldr	r2, [r4], #4
	mov	r1, r5
	mov	r0, #1
	bl	__printf_chk
	cmp	r4, r6
	bne	.L343
	mov	r0, #0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, pc}
	.size	main, .-main
	.comm	srchtop,4,4
	.comm	srcharr,400000,4
	.comm	nodecnt,4,4
	.global	storestring
	.comm	freearr,40000,4
	.comm	freen,4,4
	.comm	bufn,4,4
	.comm	buffer,4,4
	.comm	root,4,4
	.section	.rodata
	.align	2
	.set	.LANCHOR1,. + 0
.LC4:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.bss
	.align	2
	.set	.LANCHOR0,. + 0
	.type	storestring, %object
	.size	storestring, 4
storestring:
	.space	4
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",%progbits
