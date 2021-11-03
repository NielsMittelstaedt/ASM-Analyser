#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef union
{
    int32_t i;
    float f;
} reg;

reg sp, fp, lr, pc;
int32_t cond_reg;
char* malloc_0 = 0;

reg r4, r3, r5, r8, r1, r6, r7, r0;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7, counter8, counter9;

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(200);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 199;
    fp = sp;
}

void ldr(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index)
{
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;
    *target = 0;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;

    for(int j=0; j<bytes; j++)
        *target += (*(ptr+j) << 8*j) & (0xff << 8*j);

    if (update || post_index)
        *address += offset;
}

void str(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index)
{
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;

    for(int j=0; j<bytes; j++)
        *(ptr+j) = (*target >> (8*j)) & 0xff;

    if(update || post_index)
        *address += offset;
}


reg fib()
{
    cond_reg = r0.i > 1 ? 1 : (r0.i < 1 ? -1 : 0);
    if (cond_reg <= 0)
    {
        return r0;
    }
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&r5.i, &sp.i, 1*4, false, false, false);
    str(&r6.i, &sp.i, 2*4, false, false, false);
    str(&r7.i, &sp.i, 3*4, false, false, false);
    str(&r8.i, &sp.i, 4*4, false, false, false);
    str(&lr.i, &sp.i, 5*4, false, false, false);
    r7.i = r0.i - 2;
    r6.i = r0.i - 3;
    r3.i = r7.i & ~1;
    r5.i = r0.i - 1;
    r6.i = r6.i - r3.i;
    r4.i = 0;
L3:
    r0.i = r5.i;
    r5.i = r5.i - 2;
    r0.i = fib(r0).i;
    cond_reg = r5.i > r6.i ? 1 : (r5.i < r6.i ? -1 : 0);
    r4.i = r4.i + r0.i;
    if (cond_reg != 0)
    {
        goto L3;
    }
    r0.i = r7.i & 1;
    r0.i = r0.i + r4.i;
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, false, false, false);
    sp.i += 24;
    return r0;
}

reg main()
{
    malloc_start();
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    r0.i = 5;
    r0.i = fib(r0).i;
    printf("%d",r0.i);
    r0.i = 3;
    r0.i = fib(r0).i;
    r0.i = 1;
    r0.i = fib(r0).i;
    r0.i = 3;
    r0.i = fib(r0).i;
    r0.i = 1;
    r0.i = fib(r0).i;
    r0.i = 1;
    r0.i = fib(r0).i;
    r0.i = 0;
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    return r0;
}

