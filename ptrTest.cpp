#include "global.h"

int main(){
 int *ptr= new int[512];
 for(int i=0;i<512;i++)
  ptr[i]=i;
 cout<<ptr[128];
 cout<<*(ptr+128);
}
