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

reg r0, r4, r1, r8, r9, r2, r3, r10, r7, r5, r6;

int32_t LC1, LC0;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7, counter8, counter9, counter10, counter11, counter12, counter13, counter14, counter15, counter16, counter17, counter18, counter19, counter20, counter21, counter22, counter23, counter24, counter25, counter26;

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

    LC1 = (int32_t) ((char*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = (int32_t) ((char*) malloc(6*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {5,3,9,2,6,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
}

void free_help()
{
    free(malloc_0+r0.i);
}
void malloc_help()
{
    char* ptr = (char*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

void mergeSort(void);
void mergeSortpart0(void);
void main(void);

void mergeSort()
{
    cond_reg = r1.i > 1 ? 1 : (r1.i < 1 ? -1 : 0);
    if (cond_reg <= 0)
    {
        return;
    }
    mergeSortpart0();

}

void mergeSortpart0()
{
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&r5.i, &sp.i, 1*4, false, false, false);
    str(&r6.i, &sp.i, 2*4, false, false, false);
    str(&r7.i, &sp.i, 3*4, false, false, false);
    str(&r8.i, &sp.i, 4*4, false, false, false);
    str(&r9.i, &sp.i, 5*4, false, false, false);
    str(&r10.i, &sp.i, 6*4, false, false, false);
    str(&lr.i, &sp.i, 7*4, false, false, false);
    r4.i = (uint32_t)r1.i >> 1;
    r9.i = r0.i;
    r5.i = r1.i - ((uint32_t)r1.i >> 1);
    r10.i = (uint32_t)r4.i << 2;
    r7.i = (uint32_t)r5.i << 2;
    r0.i = r10.i;
    malloc_help();
    r8.i = r0.i;
    r0.i = r7.i;
    malloc_help();
    r1.i = r9.i - 4;
    r2.i = r8.i - 4;
    r3.i = 0;
    r6.i = r0.i;
L5:
    ldr(&r0.i, &r1.i, 4, false, true, false);
    r3.i = r3.i + 1;
    cond_reg = r4.i > r3.i ? 1 : (r4.i < r3.i ? -1 : 0);
    str(&r0.i, &r2.i, 4, false, true, false);
    if (cond_reg > 0)
    {
        goto L5;
    }
    cond_reg = r5.i > 0 ? 1 : (r5.i < 0 ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L6;
    }
    r2.i = r9.i + r10.i;
    r0.i = r7.i + r6.i;
    r3.i = r6.i;
L7:
    ldr(&r1.i, &r2.i, 4, false, false, true);
    str(&r1.i, &r3.i, 4, false, false, true);
    cond_reg = r0.i > r3.i ? 1 : (r0.i < r3.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L7;
    }
    r1.i = r4.i;
    r0.i = r8.i;
    mergeSort();
    r0.i = r6.i;
    r1.i = r5.i;
    mergeSort();
    r0.i = 0;
    r3.i = r0.i;
    r2.i = r0.i;
L11:
    ldr(&ip.i, &r8.i, ((uint32_t)r2.i << 2), false, false, false);
    ldr(&r1.i, &r6.i, ((uint32_t)r3.i << 2), false, false, false);
    cond_reg = ip.i > r1.i ? 1 : (ip.i < r1.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        str(&ip.i, &r9.i, ((uint32_t)r0.i << 2), false, false, false);
    }
    if (cond_reg <= 0)
    {
        r2.i = r2.i + 1;
    }
    if (cond_reg > 0)
    {
        r3.i = r3.i + 1;
    }
    if (cond_reg > 0)
    {
        str(&r1.i, &r9.i, ((uint32_t)r0.i << 2), false, false, false);
    }
    cond_reg = r4.i > r2.i ? 1 : (r4.i < r2.i ? -1 : 0);
    if (cond_reg > 0)
    {
        cond_reg = r5.i > r3.i ? 1 : (r5.i < r3.i ? -1 : 0);
    }
    r0.i = r0.i + 1;
    if (cond_reg > 0)
    {
        goto L11;
    }
    cond_reg = r4.i > r2.i ? 1 : (r4.i < r2.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L12;
    }
L17:
    r10.i = r8.i + r10.i;
    r1.i = r8.i + ((uint32_t)r2.i << 2);
    ip.i = r9.i + ((uint32_t)r0.i << 2);
L13:
    ldr(&lr.i, &r1.i, 4, false, false, true);
    cond_reg = r10.i > r1.i ? 1 : (r10.i < r1.i ? -1 : 0);
    str(&lr.i, &ip.i, 4, false, false, true);
    if (cond_reg != 0)
    {
        goto L13;
    }
    r0.i = r4.i + r0.i;
    r0.i = r0.i - r2.i;
L12:
    cond_reg = r5.i > r3.i ? 1 : (r5.i < r3.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L16;
    }
    r3.i = r6.i + ((uint32_t)r3.i << 2);
    r0.i = r9.i + ((uint32_t)r0.i << 2);
    r7.i = r6.i + r7.i;
L15:
    ldr(&r2.i, &r3.i, 4, false, false, true);
    cond_reg = r7.i > r3.i ? 1 : (r7.i < r3.i ? -1 : 0);
    str(&r2.i, &r0.i, 4, false, false, true);
    if (cond_reg != 0)
    {
        goto L15;
    }
L16:
    r0.i = r8.i;
    free_help();
    r0.i = r6.i;
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, false, false, false);
    ldr(&lr.i, &sp.i, 7*4, false, false, false);
    sp.i += 32;
    free_help();
L6:
    r1.i = r4.i;
    r0.i = r8.i;
    mergeSort();
    r0.i = r6.i;
    r1.i = r5.i;
    mergeSort();
    r0.i = 0;
    r3.i = r0.i;
    r2.i = r0.i;
    goto L17;

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
    mergeSortpart0();
L26:
    ldr(&r2.i, &r4.i, 4, false, false, true);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    cond_reg = r4.i > r6.i ? 1 : (r4.i < r6.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L26;
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

