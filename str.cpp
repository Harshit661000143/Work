#include <iostream>
#include <string>
#include "global.h"
#include <stdlib.h>
#include <cstdlib>
#include <sstream>

int main ()
{
  std::string str ("Test strin1");
  std::cout << "The size of str is " << str.length() << " bytes.\n";
  std::cout<<str[0]<<"\t"<<str[10]<<"\t"<<str[11]<<"\t"<<str.size()<<endl;
char s=str[10];
int a= atoi(&s)+1;
//str[10]=stoi(string(a));
  cout<<"a = "<<a<<endl;
//string str = string(intStr);
 // str[1+a;
//  memcpy(&str[(str.size)-1],a,

std::string s1 = std::to_string(a);
str[10]=s1[0];
  std::cout<<str[0]<<"\t"<<str[10]<<"\t"<<str[11]<<"\t"<<str.size()<<endl;
//cout<<"s1"<<s1<<endl;
std::string myString = "45";
int value = atoi(myString.c_str()); //value = 45 
cout<<"value="<<value;
std::string input = "abc,def,ghi";
std::istringstream ss(input);
std::string token;

while(std::getline(ss, token, ',')) {
    std::cout << token << '\n';
}

  return 0;
}
