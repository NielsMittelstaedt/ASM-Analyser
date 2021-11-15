#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef union {
    int32_t i;
    float f;
} reg;

int32_t tmp;
reg sp, fp, lr, pc, ip;
bool z, n, c, v;
char* malloc_0 = 0;

reg r1, r2, r3, r0;

void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index){
    char *ptr;
    ptr = malloc_0 + *address;
    *target = 0;

    if (!post_index)
        ptr += offset;
    
    for(int j=0; j<bytes; j++)
        *target += (*(ptr+j) << 8*j) & (0xff << 8*j);

    if (update || post_index)
        *address += offset;
}

void str(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index){
    char *ptr;
    ptr = malloc_0 + *address;

    if (!post_index)
        ptr += offset;

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

void main()
{
    malloc_start();

    fp.i = fp.i - 12;
    r0.i = fp.i;
    r1.i = 123;

    str(&r1.i, &r0.i, 0, 4, false, false);
    str(&r0.i, &fp.i, 4, 4, false, false);

    ldr(&r0.i, &fp.i, 4, 4, false, false);
    ldr(&r1.i, &r0.i, 0, 4, false, false);

    printf("r1: %d\n", r1.i);
}