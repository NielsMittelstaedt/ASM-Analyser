#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

void cocktailSort(int arr[], int size)
{
    int i, changed = TRUE, temp, start = 0, end = size - 1;

    while (changed)
    {
        changed = FALSE;
        for (i = start; i < end; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                changed = TRUE;
            }
        }
        end--;

        if (changed == FALSE)
        {
            break;
        }
        changed = FALSE;

        for (i = end - 1; i >= start; i--)
        {
            if (arr[i + 1] < arr[i])
            {
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                changed = TRUE;
            }
        }
        start++;
    }
}

int main()
{
    int i, n;
    n = 6;
    int *arr = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        arr[i] = n-i;
    }

    printf("You entered:  ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    cocktailSort(arr, n);
    printf("\nSorted array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}