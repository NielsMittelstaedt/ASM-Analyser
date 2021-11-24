#include <stdio.h>
#include <stdlib.h>

void pigeonholeSort(int arr[], int size)
{
    int i, j, min = arr[0], max = arr[0], range;

    // Getting range of the array using max and min
    for (i = 1; i < size; i++)
    {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }
    range = max - min + 1;

    // Make 'holes' and put array's numbers in holes
    int *holes = (int *)malloc(sizeof(int) * range);
    for (i = 0; i < range; i++)
    {
        holes[i] = 0;
    }
    for (i = 0; i < size; i++)
    {
        holes[arr[i] - min]++;
    }

    // Copy the numbers back to the original array
    j = 0;
    for (i = 0; i < range; i++)
    {
        while (holes[i] > 0)
        {
            arr[j] = i + min;
            holes[i]--;
            j++;
        }
    }

    free(holes);
}

int main()
{
    int i, n;

    n = 6;
    int *arr = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }

    printf("You entered: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    pigeonholeSort(arr, n);
    printf("\nSorted array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}