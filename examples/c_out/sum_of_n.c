#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef union
{
    int32_t i;
    float f;
} reg;

reg sp, fp, lr, pc, ip;
int32_t cond_reg;
char* malloc_0 = 0;

void* lbl_stack[40];
int32_t lbl_idx = 39;
void* cur_lbl;

reg r1, r2, r3, r0;


int counter0, counter1, counter2, counter3, counter4;

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

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 999;
    fp = sp;

}


int main()
{
    malloc_start();
main:
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    lbl_idx -= 1;
    lbl_stack[lbl_idx] = cur_lbl;
    fp.i = sp.i + 4;
    r0.i = 9;
    cur_lbl = &&lbl1;
    f();
    lbl1:
    r3.i = 0;
    r0.i = r3.i;
    ldr(&fp.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    lbl_idx += 1;
    goto *lbl_stack[lbl_idx-1];
f:
    str(&fp.i, &sp.i, -4, false, true, false);
    fp.i = sp.i + 0;
    sp.i = sp.i - 20;
    str(&r0.i, &fp.i, -16, false, false, false);
    r3.i = 0;
    str(&r3.i, &fp.i, -12, false, false, false);
    r3.i = 1;
    str(&r3.i, &fp.i, -8, false, false, false);
    goto L2;
L3:
    ldr(&r2.i, &fp.i, -12, false, false, false);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = r2.i + r3.i;
    str(&r3.i, &fp.i, -12, false, false, false);
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r3.i = r3.i + 1;
    str(&r3.i, &fp.i, -8, false, false, false);
L2:
    ldr(&r2.i, &fp.i, -8, false, false, false);
    ldr(&r3.i, &fp.i, -16, false, false, false);
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L3;
    }
    ldr(&r3.i, &fp.i, -12, false, false, false);
    r0.i = r3.i;
    sp.i = fp.i + 0;
    ldr(&fp.i, &sp.i, 4, false, false, true);
    lbl_idx += 1;
    goto *lbl_stack[lbl_idx-1];
    return 0;
}