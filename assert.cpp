/* assert example */
#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <string.h>     /* assert */

void print_number(int* myInt) {
// assert(dummy.empty());
 // assert (myInt!=NULL);
 // printf ("%d\n",*myInt);
}

int main ()
{
  int a=10;
  int * b = NULL;
  int * c = NULL;

  b=&a;

  print_number (b);
  print_number (c);
 string dummy = " ";

  return 0;
}

