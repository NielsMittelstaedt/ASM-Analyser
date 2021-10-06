#include <stdio.h>
#include <math.h>

typedef union {
    float f;
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } raw;
} conversionfloat;

unsigned int convertToInt(int* arr, int low, int high)
{
    unsigned f = 0, i;
    for (i = high; i >= low; i--) {
        f = f + arr[i] * pow(2, high - i);
    }
    return f;
}

float convert_to_float(int number)
{
    int c, k;
    unsigned int ieee[32];
    
    for (c = 31; c >= 0; c--)
    {
        k = number >> c;
        
        if (k & 1)
            ieee[31-c] = 1;
        else
            ieee[31-c] = 0;
    }
    
    conversionfloat var;
 
    unsigned f = convertToInt(ieee, 9, 31);
 
    var.raw.mantissa = f;
    f = convertToInt(ieee, 1, 8);
    var.raw.exponent = f;
    var.raw.sign = ieee[0];
    
    return var.f;
}

int main()
{
    printf("%f", convert_to_float(1065353216));
    return 0;
}