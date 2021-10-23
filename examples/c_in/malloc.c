#include <stdlib.h>

int main ()
{
  char * buffer = (char*) malloc (5);
  buffer[0]=0;
  free (buffer);

  return 0;
}