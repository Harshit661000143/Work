#include "global.h"

bool helper(char s, char a)
{ 
return s<a;
}




int main(){

string s="helbo";
cout<<"size:\t"<<s.size();
sort(s.begin(), s.end());
for(int i=0;i<s.size()-1;i++){
  if(s[i]==s[i+1]){
   cout<<"Duplicate"<<endl;
   break;
 }
}

cout<<s<<endl;
return 0;
}
