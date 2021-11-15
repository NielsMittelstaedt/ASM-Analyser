#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//Main
int main()
{
    const char src[50] = "http://www.tutorialspoint.com";
    char dest[50];
    memcpy(dest, src, 30);
    printf("%s", dest);

    return 0;
}