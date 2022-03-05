0 	.arch armv7-a
0 	.eabi_attribute 20, 1
0 	.eabi_attribute 21, 1
0 	.eabi_attribute 23, 3
0 	.eabi_attribute 24, 1
0 	.eabi_attribute 25, 1
0 	.eabi_attribute 26, 2
0 	.eabi_attribute 30, 6
0 	.eabi_attribute 34, 1
0 	.eabi_attribute 18, 4
0 	.file	"quicksort.c"
0 	.text
0 	.align	2
0 	.global	quicksort
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	quicksort, %function
0 quicksort:
0 	@ args = 0, pretend = 0, frame = 32
0 	@ frame_needed = 1, uses_anonymous_args = 0
0 .L6:
0 .L4:
0 .L8:
0 .L7:
0 .L3:
0 .L10:
0 	@ sp needed
0 	.size	quicksort, .-quicksort
0 	.section	.rodata
0 	.align	2
0 .LC0:
0 	.ascii	"Sorted.\000"
0 	.text
0 	.align	2
0 	.global	main
0 	.syntax unified
0 	.arm
0 	.fpu softvfp
0 	.type	main, %function
0 main:
0 	@ args = 0, pretend = 0, frame = 16
0 	@ frame_needed = 1, uses_anonymous_args = 0
0 .L13:
0 .L12:
0 	@ sp needed
0 	.size	main, .-main
0 	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
0 	.section	.note.GNU-stack,"",%progbits
