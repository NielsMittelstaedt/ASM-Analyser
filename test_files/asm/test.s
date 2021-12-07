0 	.arch armv7-a
1 	.eabi_attribute 20, 1
2 	.eabi_attribute 21, 1
3 	.eabi_attribute 23, 3
4 	.eabi_attribute 24, 1
5 	.eabi_attribute 25, 1
6 	.eabi_attribute 26, 2
7 	.eabi_attribute 30, 6
8 	.eabi_attribute 34, 1
9 	.eabi_attribute 18, 4
10 	.file	"test.c"
11 	.text
12 	.global	__aeabi_idivmod
13 	.align	2
14 	.global	mulmod
15 	.syntax unified
16 	.arm
17 	.fpu softvfp
18 	.type	mulmod, %function
19 mulmod:
20 	@ args = 0, pretend = 0, frame = 24
21 	@ frame_needed = 1, uses_anonymous_args = 0
22 	push	{fp, lr}
23 	add	fp, sp, #4
24 	sub	sp, sp, #24
25 	str	r0, [fp, #-16]
26 	str	r1, [fp, #-20]
27 	str	r2, [fp, #-24]
28 	mov	r3, #0
29 	str	r3, [fp, #-8]
30 	ldr	r3, [fp, #-16]
31 	ldr	r1, [fp, #-24]
32 	mov	r0, r3
33 	bl	__aeabi_idivmod
34 	mov	r3, r1
35 	str	r3, [fp, #-12]
36 	b	.L2
37 .L4:
38 	ldr	r3, [fp, #-20]
39 	cmp	r3, #0
40 	and	r3, r3, #1
41 	rsblt	r3, r3, #0
42 	cmp	r3, #1
43 	bne	.L3
44 	ldr	r2, [fp, #-8]
45 	ldr	r3, [fp, #-12]
46 	add	r3, r2, r3
47 	ldr	r1, [fp, #-24]
48 	mov	r0, r3
49 	bl	__aeabi_idivmod
50 	mov	r3, r1
51 	str	r3, [fp, #-8]
52 .L3:
53 	ldr	r3, [fp, #-12]
54 	lsl	r3, r3, #1
55 	ldr	r1, [fp, #-24]
56 	mov	r0, r3
57 	bl	__aeabi_idivmod
58 	mov	r3, r1
59 	str	r3, [fp, #-12]
60 	ldr	r3, [fp, #-20]
61 	lsr	r2, r3, #31
62 	add	r3, r2, r3
63 	asr	r3, r3, #1
64 	str	r3, [fp, #-20]
65 .L2:
66 	ldr	r3, [fp, #-20]
67 	cmp	r3, #0
68 	bgt	.L4
69 	ldr	r3, [fp, #-8]
70 	ldr	r1, [fp, #-24]
71 	mov	r0, r3
72 	bl	__aeabi_idivmod
73 	mov	r3, r1
74 	mov	r0, r3
75 	sub	sp, fp, #4
76 	@ sp needed
77 	pop	{fp, pc}
78 	.size	mulmod, .-mulmod
79 	.align	2
80 	.global	modulo
81 	.syntax unified
82 	.arm
83 	.fpu softvfp
84 	.type	modulo, %function
85 modulo:
86 	@ args = 0, pretend = 0, frame = 24
87 	@ frame_needed = 1, uses_anonymous_args = 0
88 	push	{fp, lr}
89 	add	fp, sp, #4
90 	sub	sp, sp, #24
91 	str	r0, [fp, #-16]
92 	str	r1, [fp, #-20]
93 	str	r2, [fp, #-24]
94 	mov	r3, #1
95 	str	r3, [fp, #-8]
96 	ldr	r3, [fp, #-16]
97 	str	r3, [fp, #-12]
98 	b	.L7
99 .L9:
100 	ldr	r3, [fp, #-20]
101 	cmp	r3, #0
102 	and	r3, r3, #1
103 	rsblt	r3, r3, #0
104 	cmp	r3, #1
105 	bne	.L8
106 	ldr	r3, [fp, #-8]
107 	ldr	r2, [fp, #-12]
108 	mul	r3, r2, r3
109 	ldr	r1, [fp, #-24]
110 	mov	r0, r3
111 	bl	__aeabi_idivmod
112 	mov	r3, r1
113 	str	r3, [fp, #-8]
114 .L8:
115 	ldr	r3, [fp, #-12]
116 	mul	r3, r3, r3
117 	ldr	r1, [fp, #-24]
118 	mov	r0, r3
119 	bl	__aeabi_idivmod
120 	mov	r3, r1
121 	str	r3, [fp, #-12]
122 	ldr	r3, [fp, #-20]
123 	lsr	r2, r3, #31
124 	add	r3, r2, r3
125 	asr	r3, r3, #1
126 	str	r3, [fp, #-20]
127 .L7:
128 	ldr	r3, [fp, #-20]
129 	cmp	r3, #0
130 	bgt	.L9
131 	ldr	r3, [fp, #-8]
132 	ldr	r1, [fp, #-24]
133 	mov	r0, r3
134 	bl	__aeabi_idivmod
135 	mov	r3, r1
136 	mov	r0, r3
137 	sub	sp, fp, #4
138 	@ sp needed
139 	pop	{fp, pc}
140 	.size	modulo, .-modulo
141 	.align	2
142 	.global	Miller
143 	.syntax unified
144 	.arm
145 	.fpu softvfp
146 	.type	Miller, %function
147 Miller:
148 	@ args = 0, pretend = 0, frame = 32
149 	@ frame_needed = 1, uses_anonymous_args = 0
150 	push	{fp, lr}
151 	add	fp, sp, #4
152 	sub	sp, sp, #32
153 	str	r0, [fp, #-32]
154 	str	r1, [fp, #-36]
155 	ldr	r3, [fp, #-32]
156 	cmp	r3, #1
157 	bgt	.L12
158 	mov	r3, #0
159 	b	.L13
160 .L12:
161 	ldr	r3, [fp, #-32]
162 	cmp	r3, #2
163 	beq	.L14
164 	ldr	r3, [fp, #-32]
165 	and	r3, r3, #1
166 	cmp	r3, #0
167 	bne	.L14
168 	mov	r3, #0
169 	b	.L13
170 .L14:
171 	ldr	r3, [fp, #-32]
172 	sub	r3, r3, #1
173 	str	r3, [fp, #-12]
174 	b	.L15
175 .L16:
176 	ldr	r3, [fp, #-12]
177 	lsr	r2, r3, #31
178 	add	r3, r2, r3
179 	asr	r3, r3, #1
180 	str	r3, [fp, #-12]
181 .L15:
182 	ldr	r3, [fp, #-12]
183 	and	r3, r3, #1
184 	cmp	r3, #0
185 	beq	.L16
186 	mov	r3, #0
187 	str	r3, [fp, #-8]
188 	b	.L17
189 .L22:
190 	bl	rand
191 	mov	r2, r0
192 	ldr	r3, [fp, #-32]
193 	sub	r3, r3, #1
194 	mov	r1, r3
195 	mov	r0, r2
196 	bl	__aeabi_idivmod
197 	mov	r3, r1
198 	add	r3, r3, #1
199 	str	r3, [fp, #-24]
200 	ldr	r3, [fp, #-12]
201 	str	r3, [fp, #-16]
202 	ldr	r2, [fp, #-32]
203 	ldr	r1, [fp, #-16]
204 	ldr	r0, [fp, #-24]
205 	bl	modulo
206 	str	r0, [fp, #-20]
207 	b	.L18
208 .L20:
209 	ldr	r2, [fp, #-32]
210 	ldr	r1, [fp, #-20]
211 	ldr	r0, [fp, #-20]
212 	bl	mulmod
213 	str	r0, [fp, #-20]
214 	ldr	r3, [fp, #-16]
215 	lsl	r3, r3, #1
216 	str	r3, [fp, #-16]
217 .L18:
218 	ldr	r3, [fp, #-32]
219 	sub	r3, r3, #1
220 	ldr	r2, [fp, #-16]
221 	cmp	r2, r3
222 	beq	.L19
223 	ldr	r3, [fp, #-20]
224 	cmp	r3, #1
225 	beq	.L19
226 	ldr	r3, [fp, #-32]
227 	sub	r3, r3, #1
228 	ldr	r2, [fp, #-20]
229 	cmp	r2, r3
230 	bne	.L20
231 .L19:
232 	ldr	r3, [fp, #-32]
233 	sub	r3, r3, #1
234 	ldr	r2, [fp, #-20]
235 	cmp	r2, r3
236 	beq	.L21
237 	ldr	r3, [fp, #-16]
238 	and	r3, r3, #1
239 	cmp	r3, #0
240 	bne	.L21
241 	mov	r3, #0
242 	b	.L13
243 .L21:
244 	ldr	r3, [fp, #-8]
245 	add	r3, r3, #1
246 	str	r3, [fp, #-8]
247 .L17:
248 	ldr	r2, [fp, #-8]
249 	ldr	r3, [fp, #-36]
250 	cmp	r2, r3
251 	blt	.L22
252 	mov	r3, #1
253 .L13:
254 	mov	r0, r3
255 	sub	sp, fp, #4
256 	@ sp needed
257 	pop	{fp, pc}
258 	.size	Miller, .-Miller
259 	.align	2
260 	.global	swap
261 	.syntax unified
262 	.arm
263 	.fpu softvfp
264 	.type	swap, %function
265 swap:
266 	@ args = 0, pretend = 0, frame = 24
267 	@ frame_needed = 1, uses_anonymous_args = 0
268 	@ link register save eliminated.
269 	str	fp, [sp, #-4]!
270 	add	fp, sp, #0
271 	sub	sp, sp, #28
272 	str	r0, [fp, #-16]
273 	str	r1, [fp, #-20]
274 	str	r2, [fp, #-24]
275 	ldr	r3, [fp, #-20]
276 	lsl	r3, r3, #2
277 	ldr	r2, [fp, #-16]
278 	add	r3, r2, r3
279 	ldr	r3, [r3]
280 	str	r3, [fp, #-8]
281 	ldr	r3, [fp, #-24]
282 	lsl	r3, r3, #2
283 	ldr	r2, [fp, #-16]
284 	add	r2, r2, r3
285 	ldr	r3, [fp, #-20]
286 	lsl	r3, r3, #2
287 	ldr	r1, [fp, #-16]
288 	add	r3, r1, r3
289 	ldr	r2, [r2]
290 	str	r2, [r3]
291 	ldr	r3, [fp, #-24]
292 	lsl	r3, r3, #2
293 	ldr	r2, [fp, #-16]
294 	add	r3, r2, r3
295 	ldr	r2, [fp, #-8]
296 	str	r2, [r3]
297 	nop
298 	add	sp, fp, #0
299 	@ sp needed
300 	ldr	fp, [sp], #4
301 	bx	lr
302 	.size	swap, .-swap
303 	.align	2
304 	.global	heapify
305 	.syntax unified
306 	.arm
307 	.fpu softvfp
308 	.type	heapify, %function
309 heapify:
310 	@ args = 0, pretend = 0, frame = 32
311 	@ frame_needed = 1, uses_anonymous_args = 0
312 	push	{fp, lr}
313 	add	fp, sp, #4
314 	sub	sp, sp, #32
315 	str	r0, [fp, #-24]
316 	str	r1, [fp, #-28]
317 	str	r2, [fp, #-32]
318 	ldr	r3, [fp, #-32]
319 	str	r3, [fp, #-8]
320 	ldr	r3, [fp, #-32]
321 	lsl	r3, r3, #1
322 	add	r3, r3, #1
323 	str	r3, [fp, #-12]
324 	ldr	r3, [fp, #-32]
325 	add	r3, r3, #1
326 	lsl	r3, r3, #1
327 	str	r3, [fp, #-16]
328 	ldr	r3, [fp, #-12]
329 	ldr	r2, [fp, #-28]
330 	cmp	r2, r3
331 	bls	.L25
332 	ldr	r3, [fp, #-8]
333 	lsl	r3, r3, #2
334 	ldr	r2, [fp, #-24]
335 	add	r3, r2, r3
336 	ldr	r2, [r3]
337 	ldr	r3, [fp, #-12]
338 	lsl	r3, r3, #2
339 	ldr	r1, [fp, #-24]
340 	add	r3, r1, r3
341 	ldr	r3, [r3]
342 	cmp	r2, r3
343 	bcs	.L25
344 	ldr	r3, [fp, #-12]
345 	str	r3, [fp, #-8]
346 .L25:
347 	ldr	r3, [fp, #-16]
348 	ldr	r2, [fp, #-28]
349 	cmp	r2, r3
350 	bls	.L26
351 	ldr	r3, [fp, #-8]
352 	lsl	r3, r3, #2
353 	ldr	r2, [fp, #-24]
354 	add	r3, r2, r3
355 	ldr	r2, [r3]
356 	ldr	r3, [fp, #-16]
357 	lsl	r3, r3, #2
358 	ldr	r1, [fp, #-24]
359 	add	r3, r1, r3
360 	ldr	r3, [r3]
361 	cmp	r2, r3
362 	bcs	.L26
363 	ldr	r3, [fp, #-16]
364 	str	r3, [fp, #-8]
365 .L26:
366 	ldr	r2, [fp, #-8]
367 	ldr	r3, [fp, #-32]
368 	cmp	r2, r3
369 	beq	.L28
370 	ldr	r3, [fp, #-8]
371 	ldr	r2, [fp, #-32]
372 	mov	r1, r3
373 	ldr	r0, [fp, #-24]
374 	bl	swap
375 	ldr	r2, [fp, #-8]
376 	ldr	r1, [fp, #-28]
377 	ldr	r0, [fp, #-24]
378 	bl	heapify
379 .L28:
380 	nop
381 	sub	sp, fp, #4
382 	@ sp needed
383 	pop	{fp, pc}
384 	.size	heapify, .-heapify
385 	.align	2
386 	.global	heapSort
387 	.syntax unified
388 	.arm
389 	.fpu softvfp
390 	.type	heapSort, %function
391 heapSort:
392 	@ args = 0, pretend = 0, frame = 16
393 	@ frame_needed = 1, uses_anonymous_args = 0
394 	push	{fp, lr}
395 	add	fp, sp, #4
396 	sub	sp, sp, #16
397 	str	r0, [fp, #-16]
398 	str	r1, [fp, #-20]
399 	ldr	r3, [fp, #-20]
400 	lsr	r3, r3, #1
401 	sub	r3, r3, #1
402 	str	r3, [fp, #-8]
403 	b	.L30
404 .L31:
405 	ldr	r2, [fp, #-8]
406 	ldr	r1, [fp, #-20]
407 	ldr	r0, [fp, #-16]
408 	bl	heapify
409 	ldr	r3, [fp, #-8]
410 	sub	r3, r3, #1
411 	str	r3, [fp, #-8]
412 .L30:
413 	ldr	r3, [fp, #-8]
414 	cmp	r3, #0
415 	bge	.L31
416 	mov	r3, #0
417 	str	r3, [fp, #-12]
418 	b	.L32
419 .L33:
420 	ldr	r3, [fp, #-12]
421 	ldr	r2, [fp, #-20]
422 	sub	r3, r2, r3
423 	sub	r3, r3, #1
424 	mov	r2, r3
425 	mov	r1, #0
426 	ldr	r0, [fp, #-16]
427 	bl	swap
428 	ldr	r3, [fp, #-12]
429 	ldr	r2, [fp, #-20]
430 	sub	r3, r2, r3
431 	sub	r3, r3, #1
432 	mov	r2, #0
433 	mov	r1, r3
434 	ldr	r0, [fp, #-16]
435 	bl	heapify
436 	ldr	r3, [fp, #-12]
437 	add	r3, r3, #1
438 	str	r3, [fp, #-12]
439 .L32:
440 	ldr	r3, [fp, #-20]
441 	sub	r2, r3, #1
442 	ldr	r3, [fp, #-12]
443 	cmp	r2, r3
444 	bhi	.L33
445 	nop
446 	nop
447 	sub	sp, fp, #4
448 	@ sp needed
449 	pop	{fp, pc}
450 	.size	heapSort, .-heapSort
451 	.align	2
452 	.global	test
453 	.syntax unified
454 	.arm
455 	.fpu softvfp
456 	.type	test, %function
457 test:
458 	@ args = 0, pretend = 0, frame = 64
459 	@ frame_needed = 1, uses_anonymous_args = 0
460 	push	{fp, lr}
461 	add	fp, sp, #4
462 	sub	sp, sp, #64
463 	str	r0, [fp, #-64]
464 	mov	r3, #0
465 	str	r3, [fp, #-8]
466 	b	.L35
467 .L36:
468 	ldr	r3, [fp, #-8]
469 	lsl	r3, r3, #2
470 	ldr	r2, [fp, #-64]
471 	add	r3, r2, r3
472 	ldr	r3, [r3]
473 	mov	r2, r3
474 	ldr	r3, [fp, #-8]
475 	lsl	r3, r3, #2
476 	sub	r1, fp, #4
477 	add	r3, r1, r3
478 	str	r2, [r3, #-56]
479 	ldr	r3, [fp, #-8]
480 	add	r3, r3, #1
481 	str	r3, [fp, #-8]
482 .L35:
483 	ldr	r3, [fp, #-8]
484 	cmp	r3, #9
485 	ble	.L36
486 	sub	r3, fp, #60
487 	mov	r1, #10
488 	mov	r0, r3
489 	bl	heapSort
490 	mov	r3, #0
491 	str	r3, [fp, #-12]
492 	b	.L37
493 .L38:
494 	ldr	r3, [fp, #-12]
495 	lsl	r3, r3, #2
496 	sub	r2, fp, #4
497 	add	r3, r2, r3
498 	ldr	r1, [r3, #-56]
499 	ldr	r3, [fp, #-12]
500 	lsl	r3, r3, #2
501 	ldr	r2, [fp, #-64]
502 	add	r3, r2, r3
503 	mov	r2, r1
504 	str	r2, [r3]
505 	ldr	r3, [fp, #-12]
506 	add	r3, r3, #1
507 	str	r3, [fp, #-12]
508 .L37:
509 	ldr	r3, [fp, #-12]
510 	cmp	r3, #9
511 	ble	.L38
512 	mov	r3, #0
513 	str	r3, [fp, #-16]
514 	mov	r3, #0
515 	str	r3, [fp, #-20]
516 	b	.L39
517 .L43:
518 	ldr	r1, [fp, #-20]
519 	movw	r3, #21846
520 	movt	r3, 21845
521 	smull	r3, r2, r3, r1
522 	asr	r3, r1, #31
523 	sub	r2, r2, r3
524 	mov	r3, r2
525 	lsl	r3, r3, #1
526 	add	r3, r3, r2
527 	sub	r2, r1, r3
528 	cmp	r2, #0
529 	beq	.L40
530 	ldr	r3, [fp, #-20]
531 	lsl	r3, r3, #2
532 	ldr	r2, [fp, #-64]
533 	add	r3, r2, r3
534 	ldr	r2, [r3]
535 	ldr	r3, [fp, #-16]
536 	mul	r3, r2, r3
537 	str	r3, [fp, #-16]
538 .L40:
539 	ldr	r3, [fp, #-20]
540 	and	r3, r3, #1
541 	cmp	r3, #0
542 	bne	.L41
543 	ldr	r3, [fp, #-20]
544 	lsl	r3, r3, #2
545 	ldr	r2, [fp, #-64]
546 	add	r3, r2, r3
547 	ldr	r3, [r3]
548 	ldr	r2, [fp, #-16]
549 	add	r3, r2, r3
550 	str	r3, [fp, #-16]
551 	b	.L42
552 .L41:
553 	ldr	r3, [fp, #-20]
554 	lsl	r3, r3, #2
555 	ldr	r2, [fp, #-64]
556 	add	r3, r2, r3
557 	ldr	r3, [r3]
558 	ldr	r2, [fp, #-16]
559 	sub	r3, r2, r3
560 	str	r3, [fp, #-16]
561 .L42:
562 	ldr	r3, [fp, #-20]
563 	add	r3, r3, #1
564 	str	r3, [fp, #-20]
565 .L39:
566 	ldr	r3, [fp, #-20]
567 	cmp	r3, #9
568 	ble	.L43
569 	ldr	r3, [fp, #-16]
570 	mov	r0, r3
571 	sub	sp, fp, #4
572 	@ sp needed
573 	pop	{fp, pc}
574 	.size	test, .-test
575 	.align	2
576 	.global	fib
577 	.syntax unified
578 	.arm
579 	.fpu softvfp
580 	.type	fib, %function
581 fib:
582 	@ args = 0, pretend = 0, frame = 8
583 	@ frame_needed = 1, uses_anonymous_args = 0
584 	push	{r4, fp, lr}
585 	add	fp, sp, #8
586 	sub	sp, sp, #12
587 	str	r0, [fp, #-16]
588 	ldr	r3, [fp, #-16]
589 	cmp	r3, #1
590 	bgt	.L46
591 	ldr	r3, [fp, #-16]
592 	b	.L47
593 .L46:
594 	ldr	r3, [fp, #-16]
595 	sub	r3, r3, #1
596 	mov	r0, r3
597 	bl	fib
598 	mov	r4, r0
599 	ldr	r3, [fp, #-16]
600 	sub	r3, r3, #2
601 	mov	r0, r3
602 	bl	fib
603 	mov	r3, r0
604 	add	r3, r4, r3
605 .L47:
606 	mov	r0, r3
607 	sub	sp, fp, #8
608 	@ sp needed
609 	pop	{r4, fp, pc}
610 	.size	fib, .-fib
611 	.global	__aeabi_idiv
612 	.section	.rodata
613 	.align	2
614 .LC1:
615 	.ascii	"%d is prime\012\000"
616 	.align	2
617 .LC2:
618 	.ascii	"%d is not prime\012\000"
619 	.align	2
620 .LC3:
621 	.ascii	"Ergebnis: %d\012\000"
622 	.align	2
623 .LC0:
624 	.word	1
625 	.word	34
626 	.word	6
627 	.word	2
628 	.word	6
629 	.word	2
630 	.word	7
631 	.word	2
632 	.word	17
633 	.word	7
634 	.text
635 	.align	2
636 	.global	main
637 	.syntax unified
638 	.arm
639 	.fpu softvfp
640 	.type	main, %function
641 main:
642 	@ args = 0, pretend = 0, frame = 56
643 	@ frame_needed = 1, uses_anonymous_args = 0
644 	push	{fp, lr}
645 	add	fp, sp, #4
646 	sub	sp, sp, #56
647 	movw	r3, #:lower16:.LC0
648 	movt	r3, #:upper16:.LC0
649 	sub	ip, fp, #56
650 	mov	lr, r3
651 	ldmia	lr!, {r0, r1, r2, r3}
652 	stmia	ip!, {r0, r1, r2, r3}
653 	ldmia	lr!, {r0, r1, r2, r3}
654 	stmia	ip!, {r0, r1, r2, r3}
655 	ldm	lr, {r0, r1}
656 	stm	ip, {r0, r1}
657 	sub	r3, fp, #56
658 	mov	r0, r3
659 	bl	test
660 	str	r0, [fp, #-16]
661 	ldr	r3, [fp, #-16]
662 	mul	r3, r3, r3
663 	ldr	r2, [fp, #-16]
664 	mul	r3, r2, r3
665 	ldr	r2, [fp, #-16]
666 	mul	r3, r2, r3
667 	ldr	r2, [fp, #-16]
668 	mul	r3, r2, r3
669 	ldr	r2, [fp, #-16]
670 	mul	r2, r2, r3
671 	ldr	r3, [fp, #-16]
672 	mul	r3, r2, r3
673 	str	r3, [fp, #-16]
674 	mov	r3, #0
675 	str	r3, [fp, #-8]
676 	ldr	r3, [fp, #-16]
677 	str	r3, [fp, #-12]
678 	b	.L49
679 .L50:
680 	ldr	r2, [fp, #-12]
681 	movw	r3, #26215
682 	movt	r3, 26214
683 	smull	r1, r3, r3, r2
684 	asr	r1, r3, #2
685 	asr	r3, r2, #31
686 	sub	r3, r1, r3
687 	mov	r1, #10
688 	mul	r3, r1, r3
689 	sub	r3, r2, r3
690 	ldr	r2, [fp, #-8]
691 	add	r3, r2, r3
692 	str	r3, [fp, #-8]
693 	ldr	r2, [fp, #-12]
694 	movw	r3, #26215
695 	movt	r3, 26214
696 	smull	r1, r3, r3, r2
697 	asr	r1, r3, #2
698 	asr	r3, r2, #31
699 	sub	r3, r1, r3
700 	str	r3, [fp, #-12]
701 .L49:
702 	ldr	r3, [fp, #-12]
703 	cmp	r3, #0
704 	bne	.L50
705 	ldr	r3, [fp, #-8]
706 	mul	r3, r3, r3
707 	mov	r1, r3
708 	ldr	r0, [fp, #-16]
709 	bl	__aeabi_idiv
710 	mov	r3, r0
711 	str	r3, [fp, #-16]
712 	ldr	r0, [fp, #-8]
713 	bl	fib
714 	mov	r3, r0
715 	ldr	r1, [fp, #-8]
716 	mov	r0, r3
717 	bl	__aeabi_idiv
718 	mov	r3, r0
719 	mov	r1, r3
720 	ldr	r0, [fp, #-16]
721 	bl	__aeabi_idiv
722 	mov	r3, r0
723 	str	r3, [fp, #-16]
724 	mov	r1, #10
725 	ldr	r0, [fp, #-16]
726 	bl	Miller
727 	mov	r3, r0
728 	cmp	r3, #0
729 	beq	.L51
730 	ldr	r1, [fp, #-16]
731 	movw	r0, #:lower16:.LC1
732 	movt	r0, #:upper16:.LC1
733 	bl	printf
734 	b	.L52
735 .L51:
736 	ldr	r1, [fp, #-16]
737 	movw	r0, #:lower16:.LC2
738 	movt	r0, #:upper16:.LC2
739 	bl	printf
740 .L52:
741 	ldr	r1, [fp, #-16]
742 	movw	r0, #:lower16:.LC3
743 	movt	r0, #:upper16:.LC3
744 	bl	printf
745 	mov	r3, #0
746 	mov	r0, r3
747 	sub	sp, fp, #4
748 	@ sp needed
749 	pop	{fp, pc}
750 	.size	main, .-main
751 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
752 	.section	.note.GNU-stack,"",%progbits
