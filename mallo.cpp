#include "global.h"

void doMalloc(int n, int *ptr)
{
 ptr=(int *)(malloc(sizeof(int)));
}
int main()
{
 int *p;
 doMalloc(10,p);
 loop(x,10,1)
 {
  p[x]=x;
 }
 loop(x,10,1)
 {
  cout<<p[x]<<"\n";
 }
 
}  
