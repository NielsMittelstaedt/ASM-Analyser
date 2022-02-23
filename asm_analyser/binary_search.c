#include <stdio.h>

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}
  
int main(void)
{
    int arr[] = { 2, 3, 4, 10, 40 };
    int n = 6, x = 40;
    printf("Result: %d\n", binarySearch(arr, 0, n - 1, x));
    return 0;
}