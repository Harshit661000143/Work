/* sprintf example */
#include <stdio.h>
#include <iostream>
using namespace std;
int main ()
{
  char buffer[100] ;
double a= 0.000000000017787787878;
string name= "CHLE";
string n= "LOK";
    string s = name + " recieved total cost from " + n;

sprintf(buffer, " %s \t %.32f",s.c_str(),a);
cout<<buffer;
//  cout<<s<<endl;
  return 0;
}
