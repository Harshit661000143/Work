#include <iostream>
 
template<typename T>
T& operator+(const T& s1)
{
  s=s+s1;
  return *this;
}
void f(T s)
{
    std::cout << s+s << '\n';
}
 


 
int main()
{
    f<double>(1); // instantiates and calls f<double>(double)
    f('a'); // instantiates and calls f<char>(char)
    f(7); // instantiates and calls f<int>(int)
    void (*ptr)(std::string) = f; // instantiates f<string>(string)
}
