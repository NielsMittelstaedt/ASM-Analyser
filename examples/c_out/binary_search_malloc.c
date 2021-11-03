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

reg r3, r2, r0, r1;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7, counter8, counter9, counter10, counter11, counter12;

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(400);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 399;
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

void free_help()
{
    free(malloc_0+r0.i);
}
void malloc_help()
{
    if (malloc_0 == 0) malloc_0 = (char*) malloc(1);
    char* ptr = (char*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

reg binarySearch()
{
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 24;
    str(&r0.i, &fp.i, -16, false, false, false);
    str(&r1.i, &fp.i, -20, false, false, false);
    str(&r2.i, &fp.i, -24, false, false, false);
    str(&r3.i, &fp.i, -28, false, false, false);
    ldr(&r2.i, &fp.i, -24, false, false, false);
    ldr(&r3.i, &fp.i, -20, false, false, false);
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg < 0)
    {
        goto L2;
    }
    ldr(&r2.i, &fp.i, -24, false, false, false);
    ldr(&r3.i, &fp.i, -20, false, false, false);
    r3.i = r2.i - r3.i;
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + r3.i;
    r3.i = r3.i >> 1;
    r2.i = r3.i;
    ldr(&r3.i, &fp.i, -20, false, false, false);
    r3.i = r3.i + r2.i;
    str(&r3.i, &fp.i, -8, false, false, false);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    ldr(&r2.i, &fp.i, -16, false, false, false);
    r3.i = r2.i + r3.i;
    ldr(&r3.i, &r3.i, 0, false, false, true);
    ldr(&r2.i, &fp.i, -28, false, false, false);
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L3;
    }
    ldr(&r3.i, &fp.i, -8, false, false, false);
    goto L4;
L3:
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    ldr(&r2.i, &fp.i, -16, false, false, false);
    r3.i = r2.i + r3.i;
    ldr(&r3.i, &r3.i, 0, false, false, true);
    ldr(&r2.i, &fp.i, -28, false, false, false);
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg >= 0)
    {
        goto L5;
    }
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r2.i = r3.i - 1;
    ldr(&r3.i, &fp.i, -28, false, false, false);
    ldr(&r1.i, &fp.i, -20, false, false, false);
    ldr(&r0.i, &fp.i, -16, false, false, false);
    r0.i = binarySearch(r0).i;
    r3.i = r0.i;
    goto L4;
L5:
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r1.i = r3.i + 1;
    ldr(&r3.i, &fp.i, -28, false, false, false);
    ldr(&r2.i, &fp.i, -24, false, false, false);
    ldr(&r0.i, &fp.i, -16, false, false, false);
    r0.i = binarySearch(r0).i;
    r3.i = r0.i;
    goto L4;
L2:
    r3.i = ~0;
L4:
    r0.i = r3.i;
    sp.i = fp.i - 4;
    ldr(&fp.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    return r0;
}

reg main()
{
    malloc_start();
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 16;
    r0.i = 20;
    malloc_help();
    r3.i = r0.i;
    str(&r3.i, &fp.i, -8, false, false, false);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r2.i = 2;
    str(&r2.i, &r3.i, 0, false, false, true);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = r3.i + 4;
    r2.i = 3;
    str(&r2.i, &r3.i, 0, false, false, true);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = r3.i + 8;
    r2.i = 4;
    str(&r2.i, &r3.i, 0, false, false, true);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = r3.i + 12;
    r2.i = 10;
    str(&r2.i, &r3.i, 0, false, false, true);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = r3.i + 16;
    r2.i = 40;
    str(&r2.i, &r3.i, 0, false, false, true);
    r3.i = 5;
    str(&r3.i, &fp.i, -12, false, false, false);
    r3.i = 40;
    str(&r3.i, &fp.i, -16, false, false, false);
    ldr(&r3.i, &fp.i, -12, false, false, false);
    r2.i = r3.i - 1;
    ldr(&r3.i, &fp.i, -16, false, false, false);
    r1.i = 0;
    ldr(&r0.i, &fp.i, -8, false, false, false);
    r0.i = binarySearch(r0).i;
    printf("%d", r0.i);
    str(&r0.i, &fp.i, -20, false, false, false);
    ldr(&r0.i, &fp.i, -8, false, false, false);
    free_help();
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - 4;
    ldr(&fp.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    return r0;
}

