0 f:
0 	add	r0, r0, #1
0 	bx	lr
0 	.size	f, .-f
0 	.section	.rodata.str1.4,"aMS",%progbits,1
0 	.align	2
0 .LC0:
0 	.ascii	"Result: %d\012\000"
0 	.type	main, %function
0 main:
1 	mov	r2, #3
1 	movw	r1, #:lower16:.LC0
1 	push	{r4, lr}
1 	movt	r1, #:upper16:.LC0
1 	mov	r0, #1
1 	bl	__printf_chk
1 	mov	r0, #0
1 	pop	{r4, pc}