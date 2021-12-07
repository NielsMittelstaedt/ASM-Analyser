#include <stdio.h>

int main(){
    int arr[] = {9,1,3,7,2};   
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++){
        for (int j=i-1; j >= 0; j--){
            if(arr[j] > arr[j+1]){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }

    printf("Sorted array:");
    for(int i = 0; i < n; i++){
        printf(" %d", arr[i]);
    }

    return 0;
}