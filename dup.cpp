#include<iostream>
#include<set>
#define max(size1,size2) size1>size2 : size1 ? size2
using namespace std;
int main(int argc, char**argv){
    int size1, size2;
    if(argc!=3){
    size1= 3;
    size2= 3;
    }
    else{
        size1=atoi(argv[1]);
        size2=atoi(argv[2]);
    }
    int *arr1=new int[size1];
    int *arr2=new int[size2];
    for(int i=0;i<size1;i++){
       cin>>arr1[i]; 
    }
    for(int i=0;i<size2;i++){
       cin>>arr2[i]; 
    }
    set<int> history;
    for(int i=0; i<size1; i++){
      if(history.find(arr1[i])==history.end())
        history.insert(arr1[i]);
      else
        history.erase(arr1[i]);
    }
    for(int i=0; i<size2; i++){
      if(history.find(arr2[i])==history.end())
        history.insert(arr2[i]);
      else
        history.erase(arr2[i]);
    }
    for(set<int>:: iterator s=history.begin();s!=history.end();s++)
    cout<<*s<<"\t";
}    
      
