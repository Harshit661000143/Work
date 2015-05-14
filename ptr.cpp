//#include <cstdio>
#include <iostream>
using namespace std;
#include <string>
#include <math.h>

// select avg(c1*c1) from tab where c2='sunday'

int c1[16] = {-3,2,0,7,4,3,2,1,100,16,1,0,-13,6,2,3};
char* c2[16] = {"a","b","sunday","sunday","sunday","sunday","sunday","sunday","b","sunday",
            	"ahgijfdo","","sunday","","abc","monday"};



int main( int argn, char** argv )
{
  int *ptr= new int[10];
  for(int i=0;i<10;i++){
    ptr[i]=i;
  }
  int *ptr2=&(ptr[0]);
  for(int i=0;i<10;i++){
  cout<<"Output should be "<<ptr2[i]<<"\n";
  } 
  
  string str="sunday";
  // compute result of SQL query
  // select avg(c1*c1) from tab where c2='sunday'
 long sum=0, ctr=0;
 for(int i=0;i<16;i++){
  string temp=c2[i];
  if(!temp.compare("sunday")){
    ctr++;
    sum+=pow(c1[i],2);
}
cout<<sizeof(int)<<" \t size\n";
}
//cout<<”sum = ”<<sum<<endl;
 cout<<"AVG = "<<sum/ctr<<endl;
  return 0;
}

