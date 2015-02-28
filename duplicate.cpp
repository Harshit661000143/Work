#include "global.h"

int* removeduplicates(int *array,int len);
void printArray(int *array,int len);
void removeduplicates2(int *array,int len);
int main()
{
 int n=10;
 int *array = new int[n];
 loop(x,n,1){
   if(rand()%3==0)
  array[x]=4;
   else if(rand()%3==1)
  array[x]=5;
   else
  array[x]=7;
}
// printArray(array, n); 
// int *newarry= removeduplicates(array, n); 
  int arr[10]={1,1,1,1,2,2,2,3,4,3};
 printArray(arr, n); 
  removeduplicates2(arr, n); 
// printArray(newarry, n); 
 printArray(arr, n); 
}

int* removeduplicates(int *array,int len){
  map<int,int> history;
  int *narray = new int[len];
  int ctr=0;
  loop(x,len,1){
   if(!history[array[x]]){
     cout<<"making "<<array[x]<<" as 1\n";
     history[array[x]]=1;
     narray[ctr]=array[x];
     ctr++;
    }
 }
 return narray;
}
void removeduplicates2(int *array,int len){
  map<int,int> history;
  int *narray = array;
  int ctr=0;
  loop(x,len,1){
   if(!history[narray[x]]){
     cout<<"making "<<narray[x]<<" as 1\n";
     history[array[x]]=1;
     //narray[ctr]=array[x];
    // ctr++;
    }
   else{
    int remove=x;
  //  int check=x-1;
      //cout<<"copying "<<narray[remove+1]<< " to " <<narray[remove]<<"\n";
    for(;remove<len-1;remove++)
     {
      //cout<<"copying "<<narray[remove+1]<< " to " <<narray[remove]<<"\n";
       if(!history[narray[remove+1]]){
      cout<<"copying "<<narray[remove+1]<< " to " <<narray[remove]<<"\n";
      narray[remove]=narray[remove+1];
       if(remove==x)
         history[remove]=1;
       }
     }
//     x=check;
     cout<<"x=: "<<x;
     cout<<"End\n";
     
  }
 } 
}
   

void printArray(int *array,int len){
  cout<<"Print Array\n";
  loop(x,len,1)
   cout<<array[x]<<"\t";
}

 
