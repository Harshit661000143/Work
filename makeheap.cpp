#include "global.h"

struct vectorInfo
{
 int digitcount, stringsize, index;
};

struct Comp
{
   bool operator()(const vectorInfo& s1, const vectorInfo& s2)
   {
     // return s1.x < s2.x && s1.y == s2.y;
      return s1.digitcount > s2.digitcount;
   }
};
struct CompStringSize
{
   bool operator()(const vectorInfo& s1, const vectorInfo& s2)
   {
     // return s1.x < s2.x && s1.y == s2.y;
      return s1.stringsize < s2.stringsize;
   }
};

int main(){
#if 1
std::vector<vectorInfo> *vec= new vector<vectorInfo>;
vector<vectorInfo> *vecString=new vector<vectorInfo>;
loop(k,5,1){
vectorInfo a;
int i;
i=k;  
if(k==1){
   i=0;
   cout<<"change K= "<<i<<"\n";
}
a.digitcount=5-k;
a.stringsize=i;
a.index=k;
vec->push_back(a);
vecString->push_back(a);
}
#endif
cout<<"before\n";
loop(i,5,1)
cout<<vec->at(i).digitcount<<"\t"<<vec->at(i).stringsize<<"\t"<<vec->at(i).index<<"\n";
#if DEBUG
vector<int> vec;
vec.push_back(100);
vec.push_back(100);
vec.push_back(30);
vec.push_back(50);
vec.push_back(60);
#endif

  std::make_heap(vec->begin(), vec->end(),Comp());
  std::make_heap(vecString->begin(), vecString->end(), CompStringSize());
cout<<"Digit count sorted\n";
#if 1
loop(i,5,1)
cout<<vec->at(i).digitcount<<"\t"<<vec->at(i).stringsize<<"\t"<<vec->at(i).index<<"\n";
#endif
cout<<"Size sorted\n";
loop(i,5,1)
cout<<vecString->at(i).digitcount<<"\t"<<vecString->at(i).stringsize<<"\t"<<vecString->at(i).index<<"\n";
#if DEBUG
loop(i,5,1)
cout<<vec[i]<<"\n";
#endif


}
