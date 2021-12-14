0 	.arch armv7-a
1 	.eabi_attribute 20, 1
2 	.eabi_attribute 21, 1
3 	.eabi_attribute 23, 3
4 	.eabi_attribute 24, 1
5 	.eabi_attribute 25, 1
6 	.eabi_attribute 26, 2
7 	.eabi_attribute 30, 2
8 	.eabi_attribute 34, 1
9 	.eabi_attribute 18, 4
10 	.file	"heap_sort.c"
11 	.text
12 	.align	2
13 	.global	swap
14 	.syntax unified
15 	.arm
16 	.fpu softvfp
17 	.type	swap, %function
18 swap:
19 	@ args = 0, pretend = 0, frame = 0
20 	@ frame_needed = 0, uses_anonymous_args = 0
21 	@ link register save eliminated.
22 	ldr	r3, [r0, r1, lsl #2]
23 	ldr	ip, [r0, r2, lsl #2]
24 	str	ip, [r0, r1, lsl #2]
25 	str	r3, [r0, r2, lsl #2]
26 	bx	lr
27 	.size	swap, .-swap
28 	.align	2
29 	.global	heapify
30 	.syntax unified
31 	.arm
32 	.fpu softvfp
33 	.type	heapify, %function
34 heapify:
35 	@ args = 0, pretend = 0, frame = 0
36 	@ frame_needed = 0, uses_anonymous_args = 0
37 	push	{r4, r5, lr}
38 	b	.L7
39 .L12:
40 	ldr	r4, [r0, lr, lsl #2]
41 	ldr	r5, [r0, r2, lsl #2]
42 	cmp	r5, r4
43 	bcs	.L4
44 	cmp	r1, r3
45 	bhi	.L11
46 .L9:
47 	mov	ip, lr
48 	mov	r3, lr
49 .L5:
50 	cmp	r3, r2
51 	popeq	{r4, r5, pc}
52 .L13:
53 	ldr	r4, [r0, r2, lsl #2]
54 	ldr	lr, [r0, ip, lsl #2]
55 	str	r4, [r0, ip, lsl #2]
56 	str	lr, [r0, r2, lsl #2]
57 	mov	r2, r3
58 .L7:
59 	lsl	r3, r2, #1
60 	add	lr, r3, #1
61 	add	r3, r3, #2
62 	cmp	lr, r1
63 	mov	ip, r3
64 	bcc	.L12
65 .L4:
66 	cmp	r1, r3
67 	popls	{r4, r5, pc}
68 	ldr	r4, [r0, r2, lsl #2]
69 	ldr	lr, [r0, r3, lsl #2]
70 	cmp	r4, lr
71 	popcs	{r4, r5, pc}
72 	cmp	r3, r2
73 	bne	.L13
74 	pop	{r4, r5, pc}
75 .L11:
76 	ldr	r5, [r0, r3, lsl #2]
77 	cmp	r4, r5
78 	bcs	.L9
79 	b	.L5
80 	.size	heapify, .-heapify
81 	.align	2
82 	.global	heapSort
83 	.syntax unified
84 	.arm
85 	.fpu softvfp
86 	.type	heapSort, %function
87 heapSort:
88 	@ args = 0, pretend = 0, frame = 0
89 	@ frame_needed = 0, uses_anonymous_args = 0
90 	push	{r4, r5, r6, lr}
91 	lsr	r4, r1, #1
92 	cmp	r4, #0
93 	beq	.L15
94 	sub	r4, r4, #1
95 .L16:
96 	mov	r2, r4
97 	sub	r4, r4, #1
98 	bl	heapify
99 	cmn	r4, #1
100 	bne	.L16
101 .L15:
102 	subs	r5, r1, #1
103 	popeq	{r4, r5, r6, pc}
104 	add	r4, r0, r1, lsl #2
105 	add	r6, r0, #4
106 .L18:
107 	ldr	ip, [r4, #-4]!
108 	mov	r1, r5
109 	ldr	r3, [r0]
110 	mov	r2, #0
111 	sub	r5, r5, #1
112 	str	ip, [r0]
113 	str	r3, [r4]
114 	bl	heapify
115 	cmp	r6, r4
116 	bne	.L18
117 	pop	{r4, r5, r6, pc}
118 	.size	heapSort, .-heapSort
119 	.section	.rodata.str1.4,"aMS",%progbits,1
120 	.align	2
121 .LC1:
122 	.ascii	"%d \000"
123 	.section	.text.startup,"ax",%progbits
124 	.align	2
125 	.global	main
126 	.syntax unified
127 	.arm
128 	.fpu softvfp
129 	.type	main, %function
130 main:
131 	@ args = 0, pretend = 0, frame = 40
132 	@ frame_needed = 0, uses_anonymous_args = 0
133 	movw	ip, #:lower16:.LANCHOR0
134 	movt	ip, #:upper16:.LANCHOR0
135 	push	{r4, r5, r6, lr}
136 	sub	sp, sp, #40
137 	ldmia	ip!, {r0, r1, r2, r3}
138 	mov	lr, sp
139 	movw	r5, #:lower16:.LC1
140 	add	r6, sp, #40
141 	movt	r5, #:upper16:.LC1
142 	mov	r4, sp
143 	stmia	lr!, {r0, r1, r2, r3}
144 	ldmia	ip!, {r0, r1, r2, r3}
145 	stmia	lr!, {r0, r1, r2, r3}
146 	ldm	ip, {r0, r1}
147 	stm	lr, {r0, r1}
148 	mov	r0, sp
149 	mov	r1, #10
150 	bl	heapSort
151 .L29:
152 	ldr	r2, [r4], #4
153 	mov	r1, r5
154 	mov	r0, #1
155 	bl	__printf_chk
156 	cmp	r4, r6
157 	bne	.L29
158 	mov	r0, #0
159 	add	sp, sp, #40
160 	@ sp needed
161 	pop	{r4, r5, r6, pc}
162 	.size	main, .-main
163 	.section	.rodata
164 	.align	2
165 	.set	.LANCHOR0,. + 0
166 .LC0:
167 	.word	1
168 	.word	34
169 	.word	6
170 	.word	2
171 	.word	6
172 	.word	2
173 	.word	7
174 	.word	2
175 	.word	17
176 	.word	7
177 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
178 	.section	.note.GNU-stack,"",%progbits
