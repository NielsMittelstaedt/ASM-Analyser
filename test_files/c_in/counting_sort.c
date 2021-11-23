/*
  > Counting sort is a sorting technique based on keys between a specific range.
  > integer sorting algorithm
  > Worst-case performance O(n+k)
  > Stabilized by prefix sum array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i, n, l = 0;

    n = 6;

    int *a = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        a[i] = n - i;
        if (a[i] > l)
            l = a[i];
    }

    int *b = (int *)malloc((l + 1) * sizeof(int));
    memset(b, 0, (l + 1) * sizeof(b[0]));

    for (i = 0; i < n; i++) b[a[i]]++;  // hashing number to array index

    for (i = 0; i < (l + 1); i++)  // unstable , stabilized by prefix sum array
    {
        if (b[i] > 0)
        {
            while (b[i] != 0)  // for case when number exists more than once
            {
                printf("%d ", i);
                b[i]--;
            }
        }
    }

    free(a);
    free(b);
    return 0;
}
