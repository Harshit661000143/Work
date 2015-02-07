#include <iostream>
using namespace std;

class Base {
public:
    void NonVirtual() {
        cout << "Base NonVirtual called.\n";
    }
    virtual void Virtual() {
        cout << "Base Virtual called.\n";
    }
    virtual ~Base(){
        cout << "Deleting a Base\n";
       }
    virtual bool abstractMe(int n)=0;
    virtual int func(int a, int b=3, int c=7)=0;
};
class Derived : public Base {
public:
    void NonVirtual() {
        cout << "Derived NonVirtual called.\n";
    }
    void Virtual() {
        cout << "Derived Virtual called.\n";
    }
    bool abstractMe(int n)
    { 
      if(n==1)
         cout <<"\nI am abstracted\n";
      return true;
        
    } 
    ~Derived(){
        cout << "Deleting a Derived\n";
       }
    int func(int a, int b, int c) {
     return a+b+c;
    } 
};

int main() {
    Base* bBase = new Derived();
    Base* bDerived = new Derived();
    bDerived= bBase;
    bBase->NonVirtual();
    bBase->Virtual();
    bDerived->NonVirtual();
    bDerived->Virtual();
    bDerived->abstractMe(1);
    int result = bDerived->func(1);
    cout <<"****Result =\t"<<result<<"\n";
    int resultO = bDerived->func(1,5);
    cout <<"****Result =\t"<<resultO<<"\n";
    Derived* derive= new Derived();
    derive->abstractMe(1);
//    delete bBase;
 //   delete bDerived;

}

