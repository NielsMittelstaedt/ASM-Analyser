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

reg r4, r2, r3, r0, r1;

int32_t LC1, LC2, LC0;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7, counter8, counter9, counter10, counter11;

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

    LC1 = (int32_t) ((char*) malloc(22) - malloc_0);
    strcpy(malloc_0+LC1, "Ergebnis: %d\012\000");

    LC2 = (int32_t) ((char*) malloc(1*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC2[] = {__stack_chk_guard};
    for(int i=0; i<1; i++) str(&arrayLC2[i], &LC2, i*4, false, false, false);
    LC0 = (int32_t) ((char*) malloc(5*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
}


void binarySearch()
{
    cond_reg = r2.i > r1.i ? 1 : (r2.i < r1.i ? -1 : 0);
    if (cond_reg < 0)
    {
        goto L4;
    }
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    lr.i = r0.i;
    ip.i = r2.i - r1.i;
    ip.i = ip.i + ((uint32_t)ip.i >> 31);
    r0.i = r1.i + (ip.i >> 1);
    ldr(&ip.i, &lr.i, ((uint32_t)r0.i << 2), false, false, false);
    cond_reg = ip.i > r3.i ? 1 : (ip.i < r3.i ? -1 : 0);
    if (cond_reg == 0)
    {
        ldr(&r4.i, &sp.i, 0*4, false, false, false);
        ldr(&pc.i, &sp.i, 1*4, false, false, false);
        sp.i += 8;
        return;
    }
    if (cond_reg > 0)
    {
        r2.i = r0.i - 1;
    }
    if (cond_reg <= 0)
    {
        r1.i = r0.i + 1;
    }
    r0.i = lr.i;
    binarySearch();
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    return;
L4:
    r0.i = ~0;
    return;

}

void main()
{
    malloc_start();
    str(&lr.i, &sp.i, -4, false, true, false);
    sp.i = sp.i - 28;
    r3.i = (LC2 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC2 >> 16) << 16);
    ldr(&r3.i, &r3.i, 0, false, false, true);
    str(&r3.i, &sp.i, 20, false, false, false);
    r3.i = 0;
    lr.i = sp.i;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    ldr(&r0.i, &ip.i, 0*4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, false, false, false);
    ip.i += 16;
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    str(&r2.i, &lr.i, 2*4, false, false, false);
    str(&r3.i, &lr.i, 3*4, false, false, false);
    lr.i += 16;
    ldr(&r3.i, &ip.i, 0, false, false, true);
    str(&r3.i, &lr.i, 0, false, false, true);
    r3.i = 40;
    r2.i = 4;
    r1.i = 0;
    r0.i = sp.i;
    binarySearch();
    r2.i = r0.i;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    r3.i = (LC2 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC2 >> 16) << 16);
    ldr(&r2.i, &r3.i, 0, false, false, true);
    ldr(&r3.i, &sp.i, 20, false, false, false);
    r2.i = r3.i ^ r2.i;
    r3.i = 0;
    if (cond_reg != 0)
    {
        goto L12;
    }
    r0.i = 0;
    sp.i = sp.i + 28;
    ldr(&pc.i, &sp.i, 4, false, false, true);
L12:
    __stack_chk_fail();

}

