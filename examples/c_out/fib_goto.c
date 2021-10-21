#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t stack[40];
int32_t sp = 39, fp = 39;
int32_t cond_reg, counter = 0;
reg lr, pc;

//void* lbl_stack[40];                // added
//int32_t lbl_idx = 39;               // added
//void* cur_lbl;                      // added

int lbl_stack[40];
int lbl_idx = 39;
int cur_lbl;

reg r0;
reg r5;
reg r4;
reg r6;

reg fib()
{
    sp -= 4;
    stack[sp+0] = r4.i;
    stack[sp+1] = r5.i;
    stack[sp+2] = r6.i;
    stack[sp+3] = lr.i;
    lbl_idx -= 1;                   // added
    lbl_stack[lbl_idx] = cur_lbl;   // added
    r4.i = r0.i;
    cond_reg = r0.i > 1 ? 1 : (r0.i < 1 ? -1 : 0);
    if (cond_reg <= 0)
    {
        r4.i = stack[sp+0];
        r5.i = stack[sp+1];
        r6.i = stack[sp+2];
        pc.i = stack[sp+3];
        sp += 4;
        lbl_idx += 1;               // added
        //goto *lbl_stack[lbl_idx-1]; // added
        switch (lbl_stack[lbl_idx-1])
        {
            case 1:
                goto lbl1;
            case 2:
                goto lbl2;
            default:
                break;
        }
    }
    r0.i = r0.i - 1;
    //cur_lbl = &&lbl1;               // added
    cur_lbl = 1;
    r0.i = fib(r0).i;
    lbl1:                           // added
    r5.i = r0.i;
    r0.i = r4.i - 2;
    //cur_lbl = &&lbl2;               // added
    cur_lbl = 2;
    r0.i = fib(r0).i;
    lbl2:                           // added
    r0.i = r5.i + r0.i;
    r4.i = stack[sp+0];
    r5.i = stack[sp+1];
    r6.i = stack[sp+2];
    pc.i = stack[sp+3];
    sp += 4;
    lbl_idx += 1;                   // added
    //goto *lbl_stack[lbl_idx-1];     // added
    switch (lbl_stack[lbl_idx-1])
    {
        case 1:
            goto lbl1;
        case 2:
            goto lbl2;
        default:
            break;
    }
    return r0;
}

reg main()
{
    sp -= 2;
    stack[sp+0] = r4.i;
    stack[sp+1] = lr.i;
    r0.i = 2;
    //cur_lbl = &&lbl3;               // added
    cur_lbl = 3;
    r0.i = fib(r0).i;
    lbl3:                           // added
    printf("%d", r0.i);
    r0.i = 0;
    r4.i = stack[sp+0];
    pc.i = stack[sp+1];
    sp += 2;
    return r0;
}

