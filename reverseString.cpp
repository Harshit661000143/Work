#include <iostream>
using namespace std;
void reverse(char *str){
  for(int i=0;i<strlen(str);i++){
   cout<<str[i]<<"\n";
  }
}
int main(){
  char *str="This is an example";
  reverse(str); 
  cout<<str;
}
  
