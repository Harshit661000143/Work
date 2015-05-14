#include "global.h"

int main(){
 char str[]="abcdac";
 set<char> hist;
 for(int i=0;i<strlen(str);++i){
  if(hist.find(str[i])!=hist.end()){
   
   cout<<"Duplicate\n";
   return 0;
  }
   hist.insert(str[i]);
}
cout<<" NO Duplicate\n";
return 0;
}
