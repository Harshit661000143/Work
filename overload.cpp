// example on this
#include <iostream>
using namespace std;

class Dummy {
  public:
    bool isitme (Dummy& param);
    int len;
    int breadth;
};

bool Dummy::isitme (Dummy& param)
{
  if (&param == this) return true;
  else return false;
}

int main () {
  Dummy *a= new Dummy;
  Dummy* b = new Dummy;
  Dummy test;
  test.len=500;
  test.breadth=100;
  Dummy test1;
  test1.len=5;
  test1.breadth=10;
  test1=test1+ test;
  cout<<test.len<<"\t"<<test.breadth<<"\t"<<test1.len<<"\t"<<test1.breadth<<"\t\n";
//  b=a;
  if ( b->isitme(*a) )
    cout << "yes, &a is b\n";
  return 0;
}
