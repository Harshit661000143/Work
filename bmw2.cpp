#include<string.h>
#include <ctype.h>
#include <stdio.h>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
using namespace std;
static const char alphanum[] ="abcdefklmn123456778dhjbjhsfj";

/* a struct that holds each(index) strings information: digitcount, stringsize, index */
struct vectorInfo{
 int digitcount, stringsize, index;
};

/* It creates a object of struct with the given values of digitcount, stringsize, index */
vectorInfo createInfo(int digitcount, int stringsizesize, int index){
  vectorInfo v;
  v.digitcount = digitcount;
  v.stringsize = stringsizesize;
  v.index = index;
  return v;
}

/* a compare function to sort strings with least number of digitcount */
struct compdigits{
 bool operator()(const vectorInfo& v, const vectorInfo& v1){
   return v.digitcount > v1.digitcount;
 }
};

/* a compare function to sort strings with largest number of stringsize */
struct compstrings{
 bool operator()(const vectorInfo& v, const vectorInfo& v1){
   return v.stringsize < v1.stringsize;
 }
};

/* a class which has following structure 
   vector of string
   length of vector
   constructor which initializes the vector for size given by user, also stores length of vector
   a function generateRandom(int inputType) to populate vector of strings, based on given InputType.
   a function printString() to print vector of strings.
   Test functions 
     a. testEmpty() 
     b. testInput()*/

class BMW{

public:
 vector<string> *vectorofStrings;
 int lengthofvector;
 BMW(int n){
   vectorofStrings= new vector<string>(n);
   lengthofvector=n;
 }
 void generateRandom(int inputType);
 void printString();
 bool testEmpty();
 bool testInput(int n);
};

/*  a function generateRandom() to populate vector of strings
 Three type of input are
 1 is making two strings of length 0, rest are of random length 
 2 is making two string of length 10, rest are of random length 
 3 is random length of all strings */

void BMW:: generateRandom(int inputType){ 
 int length;

 for(int i=0;i<lengthofvector;i++){
   if((inputType==1) && (i==0 || i==1))
/* Making length 0 for first two strings */
     length=0;
   else if((inputType==2) && (i==lengthofvector-1 || i==lengthofvector-2))
/* Making length 10 for first two strings */
     length=10;
   else
/* Now choose length randomly between 1 and 10 */
     length = (rand()%(10))+1;

/* create string of chosen length */
   string str;
   for(int j=0;j<length;j++){
     str+=alphanum[rand()%20];
   }

/* push string at vector's index */
   (*vectorofStrings)[i] = str;
 }
}

/* a function printString() to print vector of strings 
   return if vector is NULL or size is 0 */

void BMW:: printString() 
{
/* return empty */ 
 if((vectorofStrings==NULL) || (!vectorofStrings->size())){
   cout<<" Vector is empty \n";
   return;
 }
/* print vector */
 for(int i=0;i<vectorofStrings->size();i++)
   cout<<"Vector:\t"<<(*vectorofStrings)[i]<<"\n"; 
}

/* function that takes vector of strings 
   return null if vector is null or size is 0
   return string with least numeric characters else
   return string with largest string else
   return string with lower index */

string findMyString(vector<string> *vectorofStrings){ 

/* return null if vector is null or size is 0 */
 if((vectorofStrings==NULL) || (vectorofStrings->empty())){
   cout<<" Vector is empty\n";
   return "";
 }

/* a vector to store the history of strings
   digitcount in a string
   stringsize in a string
   index      in a string */
 vector<vectorInfo> *DigitCount= new vector<vectorInfo>;
 vector<vectorInfo> *Stringsize=new vector<vectorInfo>;

/* iterate over my my vector list */
 for(int i=0;i<vectorofStrings->size();i++){ 
   int count = 0, stringsize;

/* take string at vectors index i */
   string temp=(*vectorofStrings)[i];

/* string size is stored */
   stringsize= temp.size();
   for(int j=0;j<stringsize;j++){
   /* if char at index "j" is digit increment count */   
     if(isdigit(temp[j])){
            count++;
     }
   }

   /* a function call to return a object of vectorInfo with the given data */
   vectorInfo v = createInfo(count,stringsize,i);
   
   /* push the same object in two vectors */
   DigitCount->push_back(v);
   Stringsize->push_back(v);
   /* reset the count to 0 for next string */
   count=0;
 }

 cout<<"\nStructure created for Input vector of strings\n";
 cout<<"Digitcount\tStringsize\t Vector's Index"<<"\n";
 for(int i=0;i<DigitCount->size();i++){
   cout<<DigitCount->at(i).digitcount<<"\t\t"<<DigitCount->at(i).stringsize<<"\t\t"<<DigitCount->at(i).index<<"\n";
 } 
/* create heap for DigitCount vector, comparing least number on head */
 make_heap(DigitCount->begin(), DigitCount->end(), compdigits());

/* create heap for Stringsize vector, comparing largest string on head */
 make_heap(Stringsize->begin(), Stringsize->end(), compstrings());
 
 cout<<"\nDigit count sorted: Least digit count at iondex 0\n";
 cout<<"Digitcount\tStringsize\t Vector's Index"<<"\n";
 for(int i=0;i<DigitCount->size();i++){
   cout<<DigitCount->at(i).digitcount<<"\t\t"<<DigitCount->at(i).stringsize<<"\t\t"<<DigitCount->at(i).index<<"\n";
 }

 cout<<"\nStringSize VectorInfo: Largest string at index 0\n";
 cout<<"Digitcount\tStringsize\t Vector's Index"<<"\n";
 for(int i=0;i<Stringsize->size();i++){
   cout<<Stringsize->at(i).digitcount<<"\t\t"<<Stringsize->at(i).stringsize<<"\t\t"<<Stringsize->at(i).index<<"\n";
 }
 
 /* if digit count at index 0 and 1 are same there are two strings with same least numeric characters, else index 0 is the only least numeric string */
 if(DigitCount->at(0).digitcount!=DigitCount->at(1).digitcount){
   int index = DigitCount->at(0).index;
   delete DigitCount;
   delete Stringsize;
   cout<<"\n Case 1. Smallest numeric count string printed\n";
   return (*vectorofStrings)[index];
 }
 
/* if string size at index 0 and 1 are same there are two strings with same size, else index 0 is the only largest string */
 else if(Stringsize->at(0).stringsize!=Stringsize->at(1).stringsize){
   int index = Stringsize->at(0).index;
   delete DigitCount;
   delete Stringsize;
   cout<<"\nCase 2. Largest string printed\n";
   return (*vectorofStrings)[index];
 } 
/* else return string at lower index */
 else{
   cout<<"\n Case3. Smaller index string printed"<<"\n";
   int index = Stringsize->at(0).index;
   delete DigitCount;
   delete Stringsize;
   if(index)
     return (*vectorofStrings)[index-1];
   else{
     cout<<"Largest string is at index 0, therefore cannot print lower index, return empty string\n";
     return "";
   }
 }  
}

bool BMW:: testEmpty(){
 vector<string> *vec;
 //vec=NULL;
 string result= findMyString(vec);
 if(result.empty()){
   cout<<"Empty test Passed\n";
   return true;
 }
 else{
   cout<<"Empty test Passed\n";
   return false;
 }
}
bool BMW:: testInput(int n){
 BMW b(10);
 b.generateRandom(n);
 string result= findMyString(b.vectorofStrings);
 switch(n){
   case 1:  
     if (result.compare("af3cldlna3")== 0){
       cout<<"Test Input "<< n <<" Passed\n";
       return true;
     }
     else{
       cout<<"Test Input "<< n <<" Failed\n";
       return false;
     }
     break;
   case 2:
     if (result.compare("ckne")== 0){
       cout<<"Test Input "<< n <<" Passed\n";
       return true;
     }
     else{
       cout<<"Test Input "<< n <<" Failed\n";
       return false;
     }
     break;
   default: cout<<"Sorry! It tests for two  types of Input making numeric count as 0 or string size as maximum";
 }  
}   
     
 

int main(){
 BMW b(0);
 b.testEmpty();
 cout<<"\n";
 b.testInput(1);
 cout<<"\n";
 b.testInput(2);
 return 0;
} 
