#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t sp, fp;
int32_t cond_reg;
reg lr, pc;
char* malloc_0 = 0;

reg r0, r2, r3;

int counter0, counter1, counter2;

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

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(200);
    sp = (int32_t) (stack_ptr - malloc_0) + 199;
    fp = sp;
}

void ldr_stack(reg *target, int32_t address){
    target->i = 0;
    for(int i=0; i<4; i++)
        target->i += (stack[address+i] << 8*i) & 0xff;
}

void ldr(reg *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index){
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;
    target->i = 0;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;
    
    for(int j=0; j<bytes; j++)
        target->i += (*(ptr+j) << 8*j) & (0xff << 8*j);

    if (update || post_index)
        *address += offset;
}

void str(reg *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index){
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;

    for(int j=0; j<bytes; j++)
        *(ptr+j) = (target->i >> (8*j)) & 0xff;

    if(update || post_index)
        *address += offset;
}

reg main()
{
    sp -= 8;
    for(int i=0; i<4; i++)stack[sp+(0*4)+i] = (fp >> (8*i)) & 0xff;
    for(int i=0; i<4; i++)stack[sp+(1*4)+i] = (lr.i >> (8*i)) & 0xff;
    fp = sp + 4;
    sp = sp - 8;
    r0.i = 20;
    malloc_help();
    counter0 ++;
    r3.i = r0.i;
    for(int i=0; i<4; i++)stack[fp+(-12)+i] = (r3.i>>(8*i)) & 0xff;
    r3.i = 0;
    for(int i=0; i<4; i++)r3.i += (stack[fp+(-12)+i] << 8*i) & 0xff;
    r2.i = 12;
    for(int i=0; i<4; i++)*(malloc_0+r3.i+i) = (r2.i>>(8*i)) & 0xff;
    r3.i = 0;
    for(int i=0; i<4; i++)r3.i += (stack[fp+(-12)+i] << 8*i) & 0xff;
    r3.i = 0;
    for(int i=0; i<4; i++)r3.i += (*(malloc_0+r3.i+i) << 8*i) & 0xff;
    printf("%d", r3.i);
    for(int i=0; i<4; i++)stack[fp+(-8)+i] = (r3.i>>(8*i)) & 0xff;
    r0.i = 0;
    for(int i=0; i<4; i++)r0.i += (stack[fp+(-12)+i] << 8*i) & 0xff;
    free_help();
    counter1 ++;
    r3.i = 0;
    r0.i = r3.i;
    sp = fp - 4;
    fp = 0;
    for(int i=0; i<4; i++)fp+=(stack[sp+(0*4)+i] << 8*i) & 0xff;
    pc.i = 0;
    for(int i=0; i<4; i++)pc.i+=(stack[sp+(1*4)+i] << 8*i) & 0xff;
    sp += 8;
    counter2 ++;
    return r0;
}

