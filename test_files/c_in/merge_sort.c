#include <stdio.h>
#include <stdlib.h>

void mergeSort(unsigned int* array, size_t length)
{
    if(length <= 1) return;
    int len_left = length/2;
    int len_right = length-len_left;
    unsigned int* left =(unsigned int*) malloc(sizeof(unsigned int)*len_left);
    unsigned int* right = (unsigned int*) malloc(sizeof(unsigned int)*len_right);
    for(int i = 0; i < len_left; ++i)
    {
       left[i] = array[i];
    }
    for(int j = 0; j < len_right; ++j)
    {
        right[j] = array[len_left+j];
    }
    mergeSort(left, len_left);
    mergeSort(right, len_right);

    //Merge left and right
    int i_left = 0; //Index im linken Array
    int i_right = 0; //Index im rechten Array
    int i = 0; //Index an dem nächstes Element eingefuegt wird
    while(i_left < len_left && i_right < len_right)
    {
        if(left[i_left] <= right[i_right])
        {
            array[i] = left[i_left];
            i_left++;
        }
        else
        {
            array[i] = right[i_right];
            i_right++;
        }
        i++;
    }
    while(i_left < len_left)
    {
        array[i] = left[i_left];
        i_left++;
        i++;
    }
    while(i_right < len_right)
    {
        array[i] = right[i_right];
        i_right++;
        i++;
    }
    free(left);
    free(right);
}

int main() {
    unsigned int array[] = {5,3,0,2,6,1};
    int n = 6;
    mergeSort(array, n);
    for(int i = 0; i < n; ++i) printf("%d ", array[i]);
}