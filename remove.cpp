#include "global.h"

int countways(int n)
{
  static int count = 0;
  if(n==0)
   count++;
  if(n<3)
   return 0;
  countways(n-3); 
  countways(n-5); 
  countways(n-10); 
  return count;
}




int main()
{
 int count = countways(13);
 cout<<"Count = "<<count<<"\n";
}

