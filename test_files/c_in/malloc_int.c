#include <stdlib.h>

int main ()
{
  int* buffer = (int*) malloc (5 * sizeof(int));
  buffer[0]=12;
  int x = buffer[0];
  free (buffer);
  return 0;
} 