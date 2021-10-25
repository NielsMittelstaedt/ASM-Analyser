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

reg r0, r3;


int counter0, counter1, counter2;


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


reg f()
{
    str(&fp.i, &sp.i, -4, false, true, false);
    fp.i = sp.i + 0;
    sp.i = sp.i - 12;
    str(&r0.i, &fp.i, -8, false, false, false);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = r3.i + 1;
    r0.i = r3.i;
    sp.i = fp.i + 0;
    ldr(&fp.i, &sp.i, 4, false, false, true);
    counter0 ++;
    return r0;
}

reg main()
{
    malloc_start();
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    fp.i = sp.i + 4;
    r0.i = 2;
    r0.i = f(r0).i;
    printf("%d", r0.i);
    counter1 ++;
    r3.i = 0;
    r0.i = r3.i;
    ldr(&fp.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    counter2 ++;
    return r0;
}

