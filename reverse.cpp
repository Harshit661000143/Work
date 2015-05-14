#include "global.h"

int main(){
  string str="malayala";
  string str2=str;
  int len=str.length();
  cout<<str<<endl;
//  cout<<"len ="<<len<<endl;
  for(int i=0;i<len/2;i++){
   char temp;
   temp=str[i];
   str[i]=str[len-i-1];
   str[len-i-1]=temp;
//   cout<<"str[i] = "<<str[i]<<" str[len-i] = "<<str[len-i-1]<<endl;
 //  cout<<str<<" i = "<<i<<endl; 
  }
  cout<<str<<endl;

  cout<<str2<<endl;
  if(!str.compare(str2))
  cout<<"Palindrome "<<str<<endl;
  else
  cout<<"NOT Palindrome "<<str<<endl;
  return 0;
}
