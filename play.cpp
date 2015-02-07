#include "global.h"

const int MAX = 3;

int main ()
{
   int  var[] = {10, 100, 200};
   int  i;
   int **ptr=new int*;

  //  ptr=new int;
   /* let us have address of the first element in pointer */
//   *ptr = var[1];
    *ptr= new int*;
  //  **ptr=100;
   i = 0;
    cout<<**ptr<<"\n";
#if 0
   while ( ptr <= &var[MAX - 1] )
   {

      printf("Address of var[%d] = %x\n", i, ptr );
      printf("Value of var[%d] = %d\n", i, ++(*ptr) );
    /* point to the previous location */
      ptr++;
      i++;
   }
   loop(x,3)
   {
    cout<<var[x]<<"\n";
   }
#endif
 
   return 0;
}
