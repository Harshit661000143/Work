#include "global.h"

void replace(string &s){
int l,i;
 l=i=s.size()-1;
l=l+2*3;
for(;i>=0;i--){
if(s[i]==' '){
cout<<l<<endl;
s[l]='a';
s[l-1]='a';
s[l-2]='a';
l=l-3;
}
}
cout<<"Local s\t"<<s[9]<<endl;
}
int main(){
string s=" heloo ass";
replace(s);
cout<<s<<endl;
return 0;
}
