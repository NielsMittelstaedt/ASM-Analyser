#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef union
{
    int32_t i;
    float f;
} reg;

reg sp, fp, lr, pc, ip;
int32_t cond_reg;
char* malloc_0 = 0;

reg r2, r1, r3, r0;

int counter0, counter1, counter2, counter3, counter4, counter5;

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


reg sum()
{
    str(&fp.i, &sp.i, -4, false, true, false);
    fp.i = sp.i + 0;
    sp.i = sp.i - 20;
    str(&r0.i, &fp.i, -16, false, false, false);
    str(&r1.i, &fp.i, -20, false, false, false);
    r3.i = 0;
    str(&r3.i, &fp.i, -8, false, false, false);
    r3.i = 0;
    str(&r3.i, &fp.i, -12, false, false, false);
    goto L2;
L3:
    ldr(&r3.i, &fp.i, -12, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    ldr(&r2.i, &fp.i, -16, false, false, false);
    r3.i = r2.i + r3.i;
    ldr(&r3.i, &r3.i, 0, false, false, true);
    ldr(&r2.i, &fp.i, -8, false, false, false);
    r3.i = r2.i + r3.i;
    str(&r3.i, &fp.i, -8, false, false, false);
    ldr(&r3.i, &fp.i, -12, false, false, false);
    r3.i = r3.i + 1;
    str(&r3.i, &fp.i, -12, false, false, false);
L2:
    ldr(&r2.i, &fp.i, -12, false, false, false);
    ldr(&r3.i, &fp.i, -20, false, false, false);
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg < 0)
    {
        goto L3;
    }
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r0.i = r3.i;
    sp.i = fp.i + 0;
    ldr(&fp.i, &sp.i, 4, false, false, true);
    return r0;
LC0:

}

reg main()
{
    malloc_start();
    str(&fp.i, &sp.i, -4, false, true, false);
    fp.i = sp.i + 0;
    sp.i = sp.i - 28;
r3.i = r3.i | :
       lower16:
           LC0.i;
    r3.i = (:upper16:LC0.i << 16) | r3.i;
    ip.i = fp.i - 24;
    r3.i = 4;
    str(&r3.i, &fp.i, -8, false, false, false);
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i + 0;
    ldr(&fp.i, &sp.i, 4, false, false, true);
    return r0;

}

