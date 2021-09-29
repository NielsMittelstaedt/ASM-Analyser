#include "stack/stack.h"
#include <stdio.h>

Array a;

int f(int a){
    return a+1;
}

int main() {
    initArray(&a, 2);

    for(int i = 0; i < 5; i++)
        insertArray(&a, i);

    for(int i = 0; i < 5; i++)
        printf("%d", a.array[i]);

	//printf("%d", f(2));
    f(2);
	return 0;
}