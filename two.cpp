#include<iostream>
#include<map>
using namespace std;
void findPairs(int arr[],int size,int sum);
int main()
{
  int arr[]={1,2,3, 4,5, 6, 7};
  int sum=9;
  cout<<"size "<<sizeof(arr)/sizeof(arr[0]);
  findPairs(arr,7,sum);
}
void findPairs(int arr[], int size, int sum)
{
  map<int, int> history;
  for(int i=0;i<size;i++)
   {
     if(!history[arr[i]])
        history[arr[i]]=1;
   }
  for(int i=0;i<size;i++)
   {
     int rem= sum-arr[i];
     if(history[rem])
      cout<<arr[i]<<"\t"<<rem<<"\n";
   }
} 

