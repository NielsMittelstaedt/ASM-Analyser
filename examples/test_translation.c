#include <stdio.h>

char i;
char *sp = &i;
char *fp = &i;
//fp = sp;

int f(int r0){
    // Variablen anlegen
    int r3;
    
    // str	fp, [sp, #-4]!
    sp -= 4;
    *sp = fp;
    // add	fp, sp, #0
    fp = sp + 0;
    // sub	sp, sp, #12
    sp = sp - 12;
    // str	r0, [fp, #-8]
    *(fp-8) = r0;
    // ldr	r3, [fp, #-8]
    r3 = *(fp-8);
    // add	r3, r3, #1
    r3 = r3 + 1;
    // mov	r0, r3
    r0 = r3;
    // add	sp, fp, #0
    sp = fp + 0;
    // ldr	fp, [sp], #4
    fp = *sp;
    sp += 4;
    // bx	lr
    return r0;
}

int main() {
    // lr: r14
    // fp: r11
    
    // Variablen anlegen
    int r0, r3;
    
    // push {fp, lr} -> push is short for stmdb sp!, {fp, lr}: stores 2 registers in the "decrement before" addressing mode, so the effective base address is sp-8. (lowest register at lowest address) It will store the contents of fp at sp-8 and lr at sp-4. Since the ! is present, it will then substract 8 from sp, leaving it pointing at the stored value of fp. 
    sp -= 4;
    *sp = fp;
    // add fp, sp, #4
    fp = sp + 4;
    // mov r0, #2
    r0 = 2;
    // bl f
    f(r0);
    // mov r3, #0
    r3 = 0;
    // mov r0, r3
    r0 = r3;
    // pop {fp, pc} -> pop is short for LDMIA sp! reglist: ldmia is the reverse. "Increment after" means the effective base address is sp, so it will load the registers from sp up to sp+4, then add 8 to sp. Note that is loads the stacked lr value directly into the pc, this way you restore the registers and perform the function return in a single instruction. Increasing sp means we shrink the stack.
    fp = *sp;
    sp += 4;
    
    return r0;
}