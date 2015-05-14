#include "global.h"

set<char*> dictionary;

void swap(char *s, char*si){
  char t;
  t=*s;
  *s=*si;
  *si=t;
}

void exists(char *search,int i, int len){
  
//   cout<<search<<" i= "<<i<<" len= "<<len<<endl;
  if((i==len))
 {
   cout<<search<<endl;
   if(dictionary.find(search)!=dictionary.end()){
   cout<<search<<endl;
   //return true;
}   
 }
 else{
    for(int j=i;j<len;j++){
     swap(search+i, search+j);
      exists(search, i+1,len);  
     swap(search+i, search+j);
    }
 }
 }













int main(){
    //input 5 two-lengthed words 
        char *search = new char[3];
   dictionary.insert("hello");
   dictionary.insert("the");
   dictionary.insert("are");
   cout<<"Searching"<<endl;
        cin>>search;
   cout<<"Searching"<<endl;
   exists(search,0,strlen(search));
   // cout<<"Exists"<<endl;
   //else  
  //  cout<<"Doesn't Exists"<<endl;
  return 0;
}

    
