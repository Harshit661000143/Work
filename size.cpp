#include "global.h"

int main(){

  int *ptr = new int;
  *ptr=66; 
  char* cptr;
  cptr="ABC";
  cout<<sizeof(ptr)<<"\n"<<sizeof(cptr);
  cout<<*ptr;
  return 0;
}
