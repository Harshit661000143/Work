#include<string.h>
#include <ctype.h>
#include <stdio.h>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;
static const char alphanum[] ="abcdefklmn123456778dhjbjhsfj";

/* a struct that holds each(index) strings information: digitcount, stringsize, index */

struct vectorInfo
{
 int digitcount, stringsize, index;
};

/* It creates a object of struct with the given values of digitcount, stringsize, index */
vectorInfo createInfo(int digitcount, int stringsizesize, int index)
{
  vectorInfo v;
  v.digitcount = digitcount;
  v.stringsize = stringsizesize;
  v.index = index;
  return v;
}
struct compdigits{
 bool operator()(const vectorInfo& v, const vectorInfo& v1){
   return v.digitcount > v1.digitcount;
 }
};

struct compstrings{
 bool operator()(const vectorInfo& v, const vectorInfo& v1){
   return v.stringsize < v1.stringsize;
 }
};
class BMW{

public:
 vector<string> *vectorofStrings;
 int lengthofvector;
 BMW(int n){
   vectorofStrings= new vector<string>(n);
   lengthofvector=n;
 }
 void generateRandom();
 void printString();
};
 
void BMW:: generateRandom(){ 
int length;
#if DEBUG
 cout<<sizeof(vectorofStrings)<<"\t"<<vectorofStrings[0].size()<<"\t";
#endif
 for(int i=0;i<lengthofvector;i++){
   if(i==0 || i==1)
     length=0;
   else
     length = (rand()%(10+i))+1;
   cout<<"show me length \t"<<length<<"\n";
#if DEBUG
   cout<<"IGNORE\n";
#endif
   string str;
   for(int j=0;j<length;j++){
     str+=alphanum[rand()%20];
   }
#if DEBUG
   cout<<str<<"IGNORE\n";
#endif
   (*vectorofStrings)[i] = str;
 }
}
void BMW:: printString() 
{
 for(int i=0;i<vectorofStrings->size();i++)
   cout<<"vector "<<(*vectorofStrings)[i]<<"\n"; 
}

string  exp(vector<string> *MyvectorofStrings){ 
 if(!MyvectorofStrings->size()){
   cout<<"EMPTY\n";
   return " ";
 }
 vector<vectorInfo> *vec= new vector<vectorInfo>;
 vector<vectorInfo> *vecString=new vector<vectorInfo>;
 for(int i=0;i<MyvectorofStrings->size();i++){ 
   int count=0, StringSize;
   string dummy=(*MyvectorofStrings)[i];
   StringSize= dummy.size();
#if DEBUG
   cout<<"vector: "<<dummy<<"\n"; 
#endif
   for(int j=0;j<dummy.size();j++){
     if(isdigit(dummy[j])){
            count++;
#if DEBUG             
            cout<<dummy[j]<<"\t";
#endif
     }
   }
#if DEBUG             
   cout<<"count: "<<count;
#endif
   cout<<"\n";
   vectorInfo v = createInfo(count,StringSize,i);
   vec->push_back(v);
   vecString->push_back(v);
   count=0;
 }
 cout<<"BEFORE\n";
 for(int i=0;i<vec->size();i++){
   cout<<vecString->at(i).digitcount<<"\t"<<vecString->at(i).stringsize<<"\t"<<vecString->at(i).index<<"\n";
 } 
 make_heap(vec->begin(), vec->end(), compdigits());
 make_heap(vecString->begin(), vecString->end(), compstrings());
#if DEBUG
 cout<<"String Size sorted\n";
 for(int i=0;i<vec->size();i++){
   cout<<vecString->at(i).digitcount<<"\t"<<vecString->at(i).stringsize<<"\t"<<vecString->at(i).index<<"\n";
 } 
 cout<<"Digit count sorted\n";
 for(int i=0;i<vec->size();i++){
   cout<<vec->at(i).digitcount<<"\t"<<vec->at(i).stringsize<<"\t"<<vec->at(i).index<<"\n";
 }
#endif
 if(vec->at(0).digitcount!=vec->at(1).digitcount){
   int nidex = vec->at(0).index;
#if 1 
   delete vec;
   delete vecString;
#endif
   cout<<"Smallest numeric count"<<"\n";
   return (*MyvectorofStrings)[nidex];
 }
 else if(vecString->at(0).stringsize!=vecString->at(1).stringsize){
   int nidex = vecString->at(0).index;
#if 1
   delete vec;
   delete vecString;
#endif
   cout<<"Largest string"<<"\n";
   return (*MyvectorofStrings)[nidex];
 } 
 else{
   cout<<"Smaller index"<<"\n";
   int nidex = vecString->at(0).index;
#if 1
   delete vec;
   delete vecString;
#endif
   return (*MyvectorofStrings)[nidex-1];
 }  
}


int main()
{
 BMW b(10);
 srand(time(NULL));
 b.generateRandom();
 b.printString();
#if 1
 vector<string> *vec;
 //string result= exp(b.vectorofStrings);
 string result= exp(vec);
 cout<<"Result=\t"<<result<<"\n";
#endif
 return 0;
} 
