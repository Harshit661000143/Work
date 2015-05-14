#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
using namespace std;
int main ()
{
  double val= 0.00000043535446546;
  double val2=0.00000043535446451;
  if(val>val2){
cout<<"success"<<endl;
}
  std::string pi = "pi is " + std::to_string(val);
  std::string perfect = std::to_string(1+2+4+7+14) + " is a perfect number";
  std::cout << pi << '\n';
  std::cout << perfect << '\n';
  return 0;
}
