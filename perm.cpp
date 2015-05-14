#include "global.h"

bool findPermut(string s, string a){

  sort(s.begin(),s.end());
  sort(a.begin(),a.end());
  if(!(s.compare(a))){
    return true;
  }
  return false;
}  


int main(int argc, char **argv){



string s, a;
s=argv[1];
a=argv[2];

bool res=findPermut(s,a);
cout<<res<<endl;
return 0;
}
