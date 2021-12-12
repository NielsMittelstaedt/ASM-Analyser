#include<stdio.h>

int main() {
    // puts
    puts("dies ist puts");
    
    // putchar
    putchar('c');

    // putc
    //putc('c', stdout);

    // nl
    printf("\n");
    
    // printf with different format specifiers
    // printf int
    int int1 = 14;
    printf("decimal: %d\n", int1);
    
    // printf float
    float float1 = 1.5;
    printf("float: %f\n", float1);
    
    // printf double
    double double1 = 1.23;
    printf("double: %lf\n", double1);

    // character
    char char1 = 'n';
    printf("char: %c\n", char1);

    // string
    char* string1 = "ich bin ein string1";
    printf("string: %s\n", string1);

	return 0;
}