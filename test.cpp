#include<iostream>
using namespace std;
char *Function1();
int& callMe(int);
int main(){

int result=callMe(4);
cout <<"Result=\t"<<result<<"\n";
string str= Function1();
cout<<str[0]<<"\n";
}
int& callMe(int a)
{ 
  float *pt2= new float[10];
 cout<<"Size ptr=\t"<<sizeof(pt2)<<"\t"<<sizeof(int) <<"\n";
  int *ptr= new int;
  ptr=&a;
  return a;
}
char *Function1()
{ return "Some text";}
