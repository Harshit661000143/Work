#include "global.h"

void printPairs(vector<int> arr, int target){
  sort(arr.begin(),arr.end());
  vector<int>:: iterator left=arr.begin();
  vector<int>:: iterator right=arr.end()-1;
  //while(left!=arr.end() && right>=arr.begin()){
  while(left<right){
    int sum=(*left)+(*right);
    cout<<"sum = "<<sum<<"Left = "<<*left<<"Right = "<<*right<<endl;  
    if(sum==target){
      cout<<"Match "<<*left<<"\t"<<*right<<endl;
    left++;}
    if(sum<target)
     left++;
    if(sum>target)
    right--;
   }   
  cout<<"\n";
  for(int i=0;i<arr.size();i++){
   cout<<arr[i]<<endl;
   }
}


int main(){
 vector<int> arr;
 for(int i=0; i<10; i++){
  arr.push_back(rand()%10);
 }
 int target;
 cin>>target;
 
 printPairs(arr, target);
 return 0;
}
