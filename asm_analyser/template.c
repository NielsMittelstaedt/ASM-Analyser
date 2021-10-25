#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef union {
    int32_t i;
    float f;
} reg;

reg sp, fp, lr, pc;
int32_t cond_reg;
char* malloc_0 = 0;

//REGISTERS

//COUNTERS

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(200);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 199;
    fp = sp;
}

void ldr(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index){
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

void str(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index){
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

//AUXFUNCTIONS

//TRANSLATIONS