#include "global.h"

int main(){
std::vector<int>* v = new std::vector<int>();

v->push_back(0);
v->push_back(12);
v->push_back(1);

int twelve = v->at(1);
int one = (*v)[0];
cout<<"twelve = "<<twelve<<" one = "<<one<<"\n";
vector<int> v1;
v1.push_back(906);
vector<int> * p = &v1;
cout << (*p)[0] << endl;
 

}
