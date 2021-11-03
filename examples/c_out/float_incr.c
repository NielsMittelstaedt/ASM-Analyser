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

reg r3, r0, r2, r1;

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

void f2d()
{
    double double_val = (double) r0.f;
    int64_t int64_t_val = *(int64_t *)&double_val;
    r1.i = (int32_t) (int64_t_val >> 32);
    r0.i = (int32_t) int64_t_val;
}
void d2f()
{
    int64_t int64_t_val = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    double double_val = *(double *)&int64_t_val;
    r0.f = (float) double_val;
}
void dadd()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 + *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}

reg f()
{
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 8;
    str(&r0.i, &fp.i, -8, false, false, false);
    ldr(&r0.i, &fp.i, -8, false, false, false);
    f2d();
    r2.i = r2.i | 3626;
    r2.i = (21078 << 16) | r2.i;
    r3.i = r3.i | 4829;
    r3.i = (16385 << 16) | r3.i;
    dadd();
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    d2f();
    r3.i = r0.i;
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
    r0.i = 0;
    r0.i = (16512 << 16) | r0.i;
    r0.i = f(r0).i;
    r3.i = 0;
    r0.i = r3.i;
    ldr(&fp.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    return r0;
}

