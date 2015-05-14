#include "global.h"

int main(){
  vector<string>* test;
  test= new vector<string>;
  test[0].push_back("hello");
  test[0].push_back("harshit");
  test[0].pop_back();
/*
  test->push_back("hello");
  test->push_back("harshit");
*/
  for(vector<string>::iterator it=test[0].begin();it!=test[0].end();it++)
   cout<<*it;

//  cout<<test[0]<<"\t"<<test[1]<<endl;

  return 0;
}

