#include "global.h"
//#include <iostream>

void func(int *p)
{
    std::cout << "Length of array = " << (sizeof(p)/sizeof(*p)) << std::endl;
}
//template<typename T>
char* deleteduplicates(char *string1, char* string2){
cout<<"length of string1 is in call "<<strlen(string1)<<"\n";
cout<<"length of string2 is in call"<<strlen(string2)<<"\n";
map<char,int> count;
while(*string2!=NULL)
  {
   // cout<<"A "<<*string1<<" \t";
   // cout<<"B "<<*string2<<" ";
    count[*string2]=1; 
    //cout<<"\n";
   // string1= string1+1;
    string2= string2+1;
  }
  char* result=new char;
   int x=0;int r=0;
  while(string1[x]!=NULL)
   { 
     if(!count[string1[x]]){
       result[r]=string1[x];
       cout<<"copying in result\n";
       r++;
     }
       
     x++;
   }
//  result[r]='\0';
  return result;
}

//template<typename T>
void playwithstring()
{
char* string1=new char;
char* string2=new char;
//typename enable_if<is_char<T>::value,bool>::type
loop(x,20,1){
 string1[x]=alphanum[rand()%10];
 string2[x]=alphanum[rand()%5];
}
//string1[10]='\0';
//string2[10]='\0';
loop(x,10,1)
{
 cout<<string1[x]<<"\t"<<string2[x]<<"\n";
}
char* result = deleteduplicates(string1,string2);
//T* result=deleteduplicates(string1, string2);
  cout<<"Printing Result \n";
  while(*result!=NULL)
  {
    cout<<*result<<" ";
    result=result+1;
  }

cout<<"\n";       
cout<<"length of string1 is "<<strlen(string1)<<"\n";
       

//map<char,int> count;
}
 




   
// cout<<string1[x]<<" ";






int main()
{
int a[7];
func(a);
int *p = new int[7];
std::cout << "Length of array in Main = " << (sizeof(p)/sizeof(*p)) << std::endl;
int b[7];
std::cout << "Length of Real array  = " << (sizeof(b)/sizeof(*b)) << std::endl;
int x = 10;
int * myPtr = new int[10];
char y = 'a';
char * myPtr2 = &y;

std::cout << sizeof(x) << "\n";
std::cout << sizeof(myPtr) << "\n";
std::cout << sizeof(y) << "\n";
std::cout << sizeof(myPtr2) << "\n";
playwithstring();
}

