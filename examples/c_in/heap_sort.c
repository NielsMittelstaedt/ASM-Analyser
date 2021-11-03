#include <stdlib.h>
#include <stdio.h>


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

int main() {
    unsigned int array[] = {5,3,9,2,6,1};
    int n = 6;
    heapSort(array, n);
    for(int i = 0; i < n; ++i) printf("%d ", array[i]);
}