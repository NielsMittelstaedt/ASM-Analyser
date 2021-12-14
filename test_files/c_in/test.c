#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int mulmod(int a, int b, int mod)
{
    int x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/* 
 * modular exponentiation
 */
int modulo(int base, int exponent, int mod)
{
    int x = 1;
    int y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
 
/*
 * Miller-Rabin Primality test, iteration signifies the accuracy
 */
int Miller(int p,int iteration)
{
    int i;
    int s;
    if (p < 2)
    {
        return 0;
    }
    if (p != 2 && p % 2==0)
    {
        return 0;
    }
     s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (i = 0; i < iteration; i++)
    {
        int a = rand() % (p - 1) + 1, temp = s;
        int mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return 0;
        }
    }
    return 1;
}

void swap(unsigned int* ar, unsigned int i1, unsigned int i2) {
    unsigned int temp = ar[i1];
    ar[i1] = ar[i2];
    ar[i2] = temp;
}

void heapify(unsigned int *array, size_t length, int knot)
{
    int groesste=knot;
    int links=2*knot+1;
    int rechts=2*knot+2;

    if(links<length && array[groesste] < array[links])
    {
        groesste=links;
    }
    if(rechts<length && array[groesste] < array[rechts])
    {
        groesste=rechts;
    }

    if(groesste != knot)
    {
        swap(array,groesste,knot);
        heapify(array,length,groesste);
    }
}

void heapSort(unsigned int *array,size_t length)
{
    for(int i=(length)/2-1; i>=0; i--)
    {
        heapify(array,length,i);
    }
    for(int i=0; i<length-1; i++)
    {
        swap(array,0,length-i-1);
        heapify(array,length-i-1,0);
    }

}

int test(int* array) {
    heapSort(array, 10);

    for(int i = 0; i < 10; i++){
        printf("array[%d]: ", i);
        printf("%d\n", array[i]);
    }

    int result = 0;
    for(int i = 0; i < 10; i++){
        if (i%3){
            result *= array[i];
        }
        if (i%2 == 0){
            result += array[i];
        }
        else{
            result -= array[i];
        }
    }
    return result;
}

int fib(int n){
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int array[] = {1,34,6,2,6,2,7,2,17,7};

    int tmp = test(array);

    tmp = tmp*tmp*tmp*tmp*tmp*tmp*tmp;

    printf("tmp: %d\n", tmp);

    int crossSum = 0;
    int tmp1 = tmp;

    while (tmp1 != 0) 
    {
        crossSum = crossSum + tmp1 % 10;
        tmp1 = tmp1 / 10;
    }

    printf("crossSum: %d\n", crossSum);

    tmp /= crossSum*crossSum;
    printf("tmp2: %d\n", tmp);
    tmp /= fib(crossSum)/crossSum;
    printf("count: %d\n", test_count);

    if ( Miller( tmp, 10))
        printf("%d is prime\n", tmp);
    else
        printf("%d is not prime\n", tmp);

    printf("Ergebnis: %d\n", tmp);

	return 0;
}