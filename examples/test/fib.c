#include <stdio.h>
#include <stdint.h>
int32_t stack[40];
int32_t sp = 39, fp = 39;
int32_t counter = 0;
int32_t cond_reg;

int32_t r4;
int32_t r3;
int32_t r0;

int fib(){
	//push	{r4, fp, lr}
	sp -= 2;
	stack[sp] = r4;
	stack[sp+1] = fp;
	//add	fp, sp, #8
	fp = sp + 2;
	//sub	sp, sp, #12
	sp = sp - 3;
	//str	r0, [fp, #-16]
	stack[fp+(-4)] = r0;
	//ldr	r3, [fp, #-16]
	r3 = stack[fp+(-4)];
	//cmp	r3, #1
	cond_reg = r3 > 1 ? 1 : (r3 < 1 ? -1 : 0);
	counter += 7; // ADDED
	//bgt	.L2
	if (cond_reg == 1){
		//ldr	r3, [fp, #-16]
		r3 = stack[fp+(-4)];
		//sub	r3, r3, #1
		r3 = r3 - 1;
		//mov	r0, r3
		r0 = r3;
		//bl	fib
		r0 = fib(r0);
		//mov	r4, r0
		r4 = r0;
		//ldr	r3, [fp, #-16]
		r3 = stack[fp+(-4)];
		//sub	r3, r3, #2
		r3 = r3 - 2;
		//mov	r0, r3
		r0 = r3;
		//bl	fib
		r0 = fib(r0);
		//mov	r3, r0
		r3 = r0;
		//add	r3, r4, r3
		r3 = r4 + r3;
		counter += 11; // ADDED
	}
	//ldr	r3, [fp, #-16]
	r3 = stack[fp+(-4)];
	//b	.L3
	//mov	r0, r3
	r0 = r3;
	//sub	sp, fp, #8
	sp = fp -2;
	//pop	{r4, fp, pc}
	r4 = stack[sp];
	fp = stack[sp + 1];
	sp += 2;
	counter += 5; // ADDED
	return r0;
}

int32_t main()
{
    sp -= 1;
    stack[sp] = fp;
    fp = sp + 1;
    r0 = 3;
    r0 = fib(r0);
	printf("%d", r0);
    r3 = 0;
    r0 = r3;
    fp = stack[sp];
    sp += 1;
    counter += 7;
    return r0;
}