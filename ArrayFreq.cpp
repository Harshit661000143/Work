#include "global.h"

int arr[]={1, 2, 3, 100, 3, 4, 10, 100, 3, 3, 1};
map<int, int> mapping;
multimap<int, int> reducing;
int main(){
 
  int len=sizeof(arr)/sizeof(arr[0]);

  for(int i=0; i< len; i++)
   cout<<arr[i]<<"\t";
   cout<<"\n";
  for(int i=0; i< len; i++){
    if(!mapping[arr[i]]){
       mapping[arr[i]]=1;
    }
    else{
       mapping[arr[i]]++;
    }
  }
  cout<<"Sorted Freq\n";
  for(map<int, int>:: iterator it=mapping.begin(); it!=mapping.end(); it++){
   // reducing[*it]=it->first;
   int freq= it->second;
   int num= it->first;
  reducing.insert(pair<int,int>(freq, num));
  // cout<<it->first<<" , "<<it->second<<endl;
  }
  for(multimap<int, int>:: reverse_iterator it=reducing.rbegin(); it!=reducing.rend(); it++){
    cout<<it->second<<endl;
  }
}
    
  
  
