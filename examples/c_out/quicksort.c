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

reg r5, r4, r2, r0, r7, r1, r6, r8, r10, r9, r3;

int32_t LC1, LC2, LC0;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7, counter8, counter9, counter10, counter11, counter12, counter13, counter14, counter15, counter16, counter17, counter18;

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
    char* stack_ptr = (char*) malloc(200);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 199;
    fp = sp;

    LC1 = (int32_t) ((char*) malloc(32) - malloc_0);
    strcpy(malloc_0+LC1, "Order of Sorted elements: \000");

    LC2 = (int32_t) ((char*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC2, " %d\000");

    LC0 = (int32_t) ((char*) malloc(8*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {8,7,6,5,4,3,2,1};
    for(int i=0; i<8; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
}


void quicksort()
{
    cond_reg = r1.i > r2.i ? 1 : (r1.i < r2.i ? -1 : 0);
    if (cond_reg >= 0)
    {
        return;
    }
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&r5.i, &sp.i, 1*4, false, false, false);
    str(&r6.i, &sp.i, 2*4, false, false, false);
    str(&r7.i, &sp.i, 3*4, false, false, false);
    str(&r8.i, &sp.i, 4*4, false, false, false);
    str(&r9.i, &sp.i, 5*4, false, false, false);
    str(&r10.i, &sp.i, 6*4, false, false, false);
    str(&lr.i, &sp.i, 7*4, false, false, false);
    r5.i = r2.i;
    r6.i = r0.i;
L10:
    r7.i = (uint32_t)r1.i << 2;
    r4.i = r5.i;
    r0.i = r6.i + r7.i;
    ip.i = r1.i;
L3:
    cond_reg = r5.i > ip.i ? 1 : (r5.i < ip.i ? -1 : 0);
    ldr(&r2.i, &r6.i, ((uint32_t)ip.i << 2), false, false, false);
    ldr(&lr.i, &r0.i, 0, false, false, true);
    r3.i = (uint32_t)ip.i << 2;
    if (cond_reg > 0)
    {
        r9.i = 1;
    }
    if (cond_reg <= 0)
    {
        r9.i = 0;
    }
    cond_reg = r2.i > lr.i ? 1 : (r2.i < lr.i ? -1 : 0);
    r8.i = r6.i + r3.i;
    if (cond_reg > 0)
    {
        r9.i = 0;
    }
    cond_reg = r9.i > 0 ? 1 : (r9.i < 0 ? -1 : 0);
    if (cond_reg != 0)
    {
        r3.i = r3.i + 4;
    }
    if (cond_reg != 0)
    {
        r3.i = r6.i + r3.i;
    }
    if (cond_reg == 0)
    {
        goto L9;
    }
L4:
    r8.i = r3.i;
    ldr(&r2.i, &r3.i, 4, false, false, true);
    ip.i = ip.i + 1;
    cond_reg = r2.i > lr.i ? 1 : (r2.i < lr.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        cond_reg = ip.i > r5.i ? 1 : (ip.i < r5.i ? -1 : 0);
    }
    if (cond_reg < 0)
    {
        goto L4;
    }
L9:
    ldr(&r10.i, &r6.i, ((uint32_t)r4.i << 2), false, false, false);
    r3.i = (uint32_t)r4.i << 2;
    r9.i = r6.i + r3.i;
    cond_reg = r10.i > lr.i ? 1 : (r10.i < lr.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L5;
    }
    r3.i = r3.i - 4;
    r3.i = r6.i + r3.i;
L6:
    r9.i = r3.i;
    ldr(&r10.i, &r3.i, -4, false, false, true);
    r4.i = r4.i - 1;
    cond_reg = r10.i > lr.i ? 1 : (r10.i < lr.i ? -1 : 0);
    if (cond_reg > 0)
    {
        goto L6;
    }
L5:
    cond_reg = ip.i > r4.i ? 1 : (ip.i < r4.i ? -1 : 0);
    if (cond_reg < 0)
    {
        goto L19;
    }
    str(&r10.i, &r6.i, r7.i, false, false, false);
    r2.i = r4.i - 1;
    r0.i = r6.i;
    str(&lr.i, &r9.i, 0, false, false, true);
    quicksort();
    r1.i = r4.i + 1;
    cond_reg = r1.i > r5.i ? 1 : (r1.i < r5.i ? -1 : 0);
    if (cond_reg < 0)
    {
        goto L10;
    }
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, false, false, false);
    ldr(&pc.i, &sp.i, 7*4, false, false, false);
    sp.i += 32;
    return;
L19:
    str(&r10.i, &r8.i, 0, false, false, true);
    str(&r2.i, &r9.i, 0, false, false, true);
    goto L3;

}

void main()
{
    malloc_start();
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&r5.i, &sp.i, 1*4, false, false, false);
    str(&r6.i, &sp.i, 2*4, false, false, false);
    str(&lr.i, &sp.i, 3*4, false, false, false);
    sp.i = sp.i - 32;
    ldr(&r0.i, &ip.i, 0*4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, false, false, false);
    ip.i += 16;
    lr.i = sp.i;
    r5.i = (LC2 & 0xffff);
    r4.i = sp.i - 4;
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r6.i = sp.i + 28;
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    str(&r2.i, &lr.i, 2*4, false, false, false);
    str(&r3.i, &lr.i, 3*4, false, false, false);
    lr.i += 16;
    ldr(&r0.i, &ip.i, 0*4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, false, false, false);
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    str(&r2.i, &lr.i, 2*4, false, false, false);
    str(&r3.i, &lr.i, 3*4, false, false, false);
    r1.i = 0;
    r0.i = sp.i;
    r2.i = 7;
    quicksort();
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
L21:
    ldr(&r2.i, &r4.i, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    cond_reg = r4.i > r6.i ? 1 : (r4.i < r6.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L21;
    }
    r0.i = 0;
    sp.i = sp.i + 32;
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, false, false, false);
    sp.i += 16;
    return;
}

