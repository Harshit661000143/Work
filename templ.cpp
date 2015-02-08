// class templates
#include <iostream>
using namespace std;

template <class T>
class mypair {
    T a, b;
  public:
    mypair (T first, T second)
      {a=first; b=second;}
    void getmax ();
};

template <class T>
void mypair<T>::getmax ()
{
  int retval;
  retval = a>b? a : b;
  return ;
}

int main () {
  mypair <double> myobject (100.0, 75.0);
//  cout << myobject.getmax();
  return 0;
}
