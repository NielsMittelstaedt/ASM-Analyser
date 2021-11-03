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

reg r0, r6, r1, r3, r2, r5, r4;

int32_t LC1, LC2, LC0;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7, counter8, counter9, counter10, counter11, counter12, counter13, counter14, counter15;

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

    LC1 = (int32_t) ((char*) malloc(19) - malloc_0);
    strcpy(malloc_0+LC1, "Sorted array:\000");

    LC2 = (int32_t) ((char*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC2, " %d\000");

    LC0 = (int32_t) ((char*) malloc(5*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {9,1,3,7,2};
    for(int i=0; i<5; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
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
    lr.i = sp.i + 4;
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    str(&r2.i, &lr.i, 2*4, false, false, false);
    str(&r3.i, &lr.i, 3*4, false, false, false);
    lr.i += 16;
    r1.i = r0.i;
    ldr(&r3.i, &sp.i, 8, false, false, false);
    ldr(&r2.i, &ip.i, 0, false, false, true);
    cond_reg = r0.i > r3.i ? 1 : (r0.i < r3.i ? -1 : 0);
    str(&r2.i, &lr.i, 0, false, false, true);
    if (cond_reg > 0)
    {
        r1.i = r3.i;
    }
    if (cond_reg > 0)
    {
        str(&r3.i, &sp.i, 4, false, false, false);
    }
    if (cond_reg > 0)
    {
        r3.i = r0.i;
    }
    if (cond_reg > 0)
    {
        str(&r0.i, &sp.i, 8, false, false, false);
    }
L5:
    ldr(&r2.i, &sp.i, 12, false, false, false);
    cond_reg = r3.i > r2.i ? 1 : (r3.i < r2.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L4;
    }
    r0.i = r3.i;
    str(&r3.i, &sp.i, 12, false, false, false);
    str(&r2.i, &sp.i, 8, false, false, false);
    r3.i = r2.i;
    r2.i = r0.i;
L4:
    cond_reg = r1.i > r3.i ? 1 : (r1.i < r3.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L9;
    }
    r0.i = r1.i;
    str(&r1.i, &sp.i, 8, false, false, false);
    str(&r3.i, &sp.i, 4, false, false, false);
    r1.i = r3.i;
    r3.i = r0.i;
L9:
    ldr(&r0.i, &sp.i, 16, false, false, false);
    cond_reg = r2.i > r0.i ? 1 : (r2.i < r0.i ? -1 : 0);
    if (cond_reg > 0)
    {
        goto L7;
    }
L8:
    cond_reg = r3.i > r2.i ? 1 : (r3.i < r2.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L15;
    }
    ip.i = r3.i;
    str(&r3.i, &sp.i, 12, false, false, false);
    str(&r2.i, &sp.i, 8, false, false, false);
    r3.i = r2.i;
    r2.i = ip.i;
L15:
    cond_reg = r1.i > r3.i ? 1 : (r1.i < r3.i ? -1 : 0);
    if (cond_reg > 0)
    {
        goto L11;
    }
L14:
    ldr(&ip.i, &sp.i, 20, false, false, false);
    cond_reg = r0.i > ip.i ? 1 : (r0.i < ip.i ? -1 : 0);
    if (cond_reg > 0)
    {
        str(&r0.i, &sp.i, 20, false, false, false);
    }
    if (cond_reg > 0)
    {
        r0.i = ip.i;
    }
    if (cond_reg > 0)
    {
        str(&ip.i, &sp.i, 16, false, false, false);
    }
L13:
    cond_reg = r2.i > r0.i ? 1 : (r2.i < r0.i ? -1 : 0);
    if (cond_reg > 0)
    {
        str(&r0.i, &sp.i, 12, false, false, false);
    }
    if (cond_reg > 0)
    {
        str(&r2.i, &sp.i, 16, false, false, false);
    }
    r5.i = (LC2 & 0xffff);
    if (cond_reg > 0)
    {
        r2.i = r0.i;
    }
    cond_reg = r3.i > r2.i ? 1 : (r3.i < r2.i ? -1 : 0);
    r0.i = 1;
    if (cond_reg > 0)
    {
        str(&r3.i, &sp.i, 12, false, false, false);
    }
    if (cond_reg > 0)
    {
        str(&r2.i, &sp.i, 8, false, false, false);
    }
    if (cond_reg > 0)
    {
        r3.i = r2.i;
    }
    cond_reg = r1.i > r3.i ? 1 : (r1.i < r3.i ? -1 : 0);
    if (cond_reg > 0)
    {
        str(&r1.i, &sp.i, 8, false, false, false);
    }
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    if (cond_reg > 0)
    {
        str(&r3.i, &sp.i, 4, false, false, false);
    }
    printf(malloc_0+r1.i, r2.i);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = sp.i + 4;
    r6.i = sp.i + 24;
L19:
    ldr(&r2.i, &r4.i, 4, false, false, true);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    cond_reg = r4.i > r6.i ? 1 : (r4.i < r6.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L19;
    }
    r0.i = 0;
    sp.i = sp.i + 24;
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, false, false, false);
    sp.i += 16;
    return;
L7:
    ip.i = r2.i;
    str(&r2.i, &sp.i, 16, false, false, false);
    str(&r0.i, &sp.i, 12, false, false, false);
    r2.i = r0.i;
    r0.i = ip.i;
    goto L8;
L11:
    ip.i = r1.i;
    r1.i = r3.i;
    r3.i = ip.i;
    goto L14;

}

