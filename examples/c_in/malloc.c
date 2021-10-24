#include <stdlib.h>

int main ()
{
  char * buffer = (char*) malloc (5);
  buffer[0]=12;
  buffer[1]=6;
  char x = buffer[0];
  char y = buffer[1];
  free (buffer);
  return 0;
} 