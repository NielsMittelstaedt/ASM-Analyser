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

reg r3, r5, r2, r0, r6, r1, r4;

int32_t LC1, LC0;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7, counter8, counter9, counter10, counter11, counter12, counter13, counter14, counter15, counter16, counter17, counter18, counter19;

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

    LC1 = (int32_t) ((char*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = (int32_t) ((char*) malloc(6*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {5,3,9,2,6,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
}


void swap()
{
    ldr(&r3.i, &r0.i, ((uint32_t)r1.i << 2), false, false, false);
    ldr(&ip.i, &r0.i, ((uint32_t)r2.i << 2), false, false, false);
    str(&ip.i, &r0.i, ((uint32_t)r1.i << 2), false, false, false);
    str(&r3.i, &r0.i, ((uint32_t)r2.i << 2), false, false, false);
    return;

}

void heapify()
{
    sp.i -= 12;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&r5.i, &sp.i, 1*4, false, false, false);
    str(&lr.i, &sp.i, 2*4, false, false, false);
    goto L7;
L12:
    ldr(&r4.i, &r0.i, ((uint32_t)lr.i << 2), false, false, false);
    ldr(&r5.i, &r0.i, ((uint32_t)r2.i << 2), false, false, false);
    cond_reg = r5.i > r4.i ? 1 : (r5.i < r4.i ? -1 : 0);
    if (cond_reg >= 0)
    {
        goto L4;
    }
    cond_reg = r1.i > r3.i ? 1 : (r1.i < r3.i ? -1 : 0);
    if (cond_reg > 0)
    {
        goto L11;
    }
L9:
    ip.i = lr.i;
    r3.i = lr.i;
L5:
    cond_reg = r3.i > r2.i ? 1 : (r3.i < r2.i ? -1 : 0);
    if (cond_reg == 0)
    {
        ldr(&r4.i, &sp.i, 0*4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, false, false, false);
        ldr(&pc.i, &sp.i, 2*4, false, false, false);
        sp.i += 12;
        return;
    }
L13:
    ldr(&r4.i, &r0.i, ((uint32_t)r2.i << 2), false, false, false);
    ldr(&lr.i, &r0.i, ((uint32_t)ip.i << 2), false, false, false);
    str(&r4.i, &r0.i, ((uint32_t)ip.i << 2), false, false, false);
    str(&lr.i, &r0.i, ((uint32_t)r2.i << 2), false, false, false);
    r2.i = r3.i;
L7:
    r3.i = (uint32_t)r2.i << 1;
    lr.i = r3.i + 1;
    r3.i = r3.i + 2;
    cond_reg = lr.i > r1.i ? 1 : (lr.i < r1.i ? -1 : 0);
    ip.i = r3.i;
    if (cond_reg < 0)
    {
        goto L12;
    }
L4:
    cond_reg = r1.i > r3.i ? 1 : (r1.i < r3.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        ldr(&r4.i, &sp.i, 0*4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, false, false, false);
        ldr(&pc.i, &sp.i, 2*4, false, false, false);
        sp.i += 12;
        return;
    }
    ldr(&r4.i, &r0.i, ((uint32_t)r2.i << 2), false, false, false);
    ldr(&lr.i, &r0.i, ((uint32_t)r3.i << 2), false, false, false);
    cond_reg = r4.i > lr.i ? 1 : (r4.i < lr.i ? -1 : 0);
    if (cond_reg >= 0)
    {
        ldr(&r4.i, &sp.i, 0*4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, false, false, false);
        ldr(&pc.i, &sp.i, 2*4, false, false, false);
        sp.i += 12;
        return;
    }
    cond_reg = r3.i > r2.i ? 1 : (r3.i < r2.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L13;
    }
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&pc.i, &sp.i, 2*4, false, false, false);
    sp.i += 12;
    return;
L11:
    ldr(&r5.i, &r0.i, ((uint32_t)r3.i << 2), false, false, false);
    cond_reg = r4.i > r5.i ? 1 : (r4.i < r5.i ? -1 : 0);
    if (cond_reg >= 0)
    {
        goto L9;
    }
    goto L5;

}

void heapSort()
{
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&r5.i, &sp.i, 1*4, false, false, false);
    str(&r6.i, &sp.i, 2*4, false, false, false);
    str(&lr.i, &sp.i, 3*4, false, false, false);
    r4.i = (uint32_t)r1.i >> 1;
    cond_reg = r4.i > 0 ? 1 : (r4.i < 0 ? -1 : 0);
    if (cond_reg == 0)
    {
        goto L15;
    }
    r4.i = r4.i - 1;
L16:
    r2.i = r4.i;
    r4.i = r4.i - 1;
    heapify();
    cond_reg = r4.i > -(1) ? 1 : (r4.i < -(1) ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L16;
    }
L15:
    r5.i = r1.i - 1;
    cond_reg = r5.i < 0 ? -1 : (r5.i > 0 ? 1 : 0);
    if (cond_reg == 0)
    {
        ldr(&r4.i, &sp.i, 0*4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, false, false, false);
        ldr(&pc.i, &sp.i, 3*4, false, false, false);
        sp.i += 16;
        return;
    }
    r4.i = r0.i + ((uint32_t)r1.i << 2);
    r6.i = r0.i + 4;
L18:
    ldr(&ip.i, &r4.i, -4, false, true, false);
    r1.i = r5.i;
    ldr(&r3.i, &r0.i, 0, false, false, true);
    r2.i = 0;
    r5.i = r5.i - 1;
    str(&ip.i, &r0.i, 0, false, false, true);
    str(&r3.i, &r4.i, 0, false, false, true);
    heapify();
    cond_reg = r6.i > r4.i ? 1 : (r6.i < r4.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L18;
    }
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, false, false, false);
    sp.i += 16;
    return;
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
    sp.i = sp.i - 24;
    ldr(&r0.i, &ip.i, 0*4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, false, false, false);
    ip.i += 16;
    lr.i = sp.i;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + 24;
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    str(&r2.i, &lr.i, 2*4, false, false, false);
    str(&r3.i, &lr.i, 3*4, false, false, false);
    lr.i += 16;
    ldr(&r0.i, &ip.i, 0*4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, false, false, false);
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    r0.i = sp.i;
    r1.i = 6;
    heapSort();
L29:
    ldr(&r2.i, &r4.i, 4, false, false, true);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    cond_reg = r4.i > r6.i ? 1 : (r4.i < r6.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L29;
    }
    r0.i = 0;
    sp.i = sp.i + 24;
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, false, false, false);
    sp.i += 16;
    return;
}

