// remove algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::remove
#include <vector>
#include <map>

using namespace std;
int main () {
  int myints[] = {10,20,30,30,20,10,10,20};      // 10 20 30 30 20 10 10 20

  // bounds of range:
  int* pbegin = myints;                          // ^
  int* pend = myints+sizeof(myints)/sizeof(int); // ^               
  std::cout<<"sizeof(myints)/sizeof(int) =  "<<sizeof(myints)/sizeof(int); //
  std::cout<<"sizeof(myints)/sizeof(int) =  "<<*(pend-1); //

  pend = std::remove (pbegin, pend, 10);         // 10 30 30 10 10 ?  ?  ?


map<int,vector<int> > hist;
 
vector<int> vc;
for(int i=0;i<10;i++){
  vc.push_back(i);
 }
cout <<"Print u\n";
for(int i=0;i<vc.size();i++){
 cout<<vc.at(i)<<endl;
 }
hist[0]=vc;
//hist[0].erase(remove(hist[0].begin(),hist[0].end(),4),hist[0].end());
//hist[0].erase(remove(hist[0].begin(),hist[0].end(),4));
hist[0]=remove(hist[0].begin(),hist[0].end(),4);
vector<int> vc1= hist[0];
cout <<"Print me\n";
for(int i=0;i<vc1.size();i++){
 cout<<vc1.at(i)<<endl;
 }





//availResource[nodeId]->vTasks.erase(remove(availResource[nodeId]->vTasks.begin(), availResource[nodeId]->vTasks.end(), *t), availResource[nodeId]->vTasks.end());
                                                 // ^              ^
  std::cout << "range contains:";
  for (int* p=pbegin; p!=pend; ++p)
    std::cout << ' ' << *p;
  std::cout << '\n';

  return 0;
}
