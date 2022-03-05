#include <stdio.h>
#include <stdlib.h>

void quicksort(int number[], int first, int last)
{
   int i, j, pivot, temp;

   if (first < last)
   {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
         while (number[i] <= number[pivot] && i < last)
            i++;
         while (number[j] > number[pivot])
            j--;
         if (i < j)
         {
            temp = number[i];
            number[i] = number[j];
            number[j] = temp;
         }
      }

      temp = number[pivot];
      number[pivot] = number[j];
      number[j] = temp;
      quicksort(number, first, j - 1);
      quicksort(number, j + 1, last);
   }
}

int main()
{
   int n = 1000000;
   int numbers[n];

   for (int i = 0; i < n; i++)
      numbers[i] = rand() % 10000;

   quicksort(numbers, 0, n - 1);

   printf("Sorted.\n");
   //for (int i = 0; i < n; i++)
   //   printf(" %d", numbers[i]);

   return 0;
}