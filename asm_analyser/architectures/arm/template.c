#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <regex.h>

typedef union {
    int32_t i;
    float f;
} _arm_reg;

typedef struct {
    int32_t tmp;
    _arm_reg sp, fp, lr, pc, ip;
    bool z, n, c, v;
    uint8_t* malloc_0;

    //REGISTERS

    //LOCALDEFS

    int load_counter, store_counter;
    //COUNTDEFS

    //BPDEFS    
} _asm_analysis;

_asm_analysis _asm_analysis_ = {
    .malloc_0 = 0, .load_counter = 0, .store_counter = 0,
    //COUNTINIT
    //BPINIT
};

//AUXFUNCTIONS

void printf_help(const char *format, int32_t arg1, int32_t arg2, int32_t arg3)
{
    regex_t reg;
    if (regcomp(&reg, "(%([0-9]*)lf)|(%f)", REG_EXTENDED | REG_NOSUB) != 0) return;
    if (regexec(&reg, format, 0, 0, 0) == 0)
    {
        uint64_t arg = ((uint64_t)(uint32_t) arg3) << 32 | ((uint64_t)(uint32_t) arg2);
        double d_arg = *(double *)&arg;
        printf(format, d_arg);
        return;
    }
    else if(strstr(format, "%s")){
        printf(format, _asm_analysis_.malloc_0+arg1);
    }
    else if(strstr(format, "%c")){
        printf(format, arg1);
    }
    else{
        printf(format, arg1);
    }
    regfree(&reg);
}

// Debugging purposes
/*
void print_stack(int32_t start, int32_t bytes)
{
    int32_t size = bytes/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++){
        ldr4000(&cur_val, &start, i*4);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}*/

void malloc_start()
{
    //MALLOCSTART
}

void counter_summary()
{
    int basic_blocks = sizeof(_asm_analysis_.counters)/sizeof(_asm_analysis_.counters[0]);
    
    printf("\n__count_start__\n");
    printf("%d\n", basic_blocks);

    for (int i=0; i < basic_blocks; i++){
        printf("%d ", _asm_analysis_.block_sizes[i]);
    }
    printf("\n");

    for (int i=0; i < basic_blocks; i++){
        printf("%d ", _asm_analysis_.counters[i]);
    }
    printf("\n");
    printf("%d\n", _asm_analysis_.load_counter);
    printf("%d\n", _asm_analysis_.store_counter);

    /* BPSTART
    int branch_count = sizeof(_asm_analysis_.cond_branches)/sizeof(_asm_analysis_.cond_branches[0]);

    for (int i=0; i < branch_count; i++){
        printf("%d ", _asm_analysis_.cond_branches[i]);
    }
    printf("\n");
    for (int i=0; i < branch_count; i++){
        printf("%d ", _asm_analysis_.mispredictions[i]);
    }
    printf("\n");
    BPEND */
}

//FUNCTIONDECLS

//TRANSLATIONS