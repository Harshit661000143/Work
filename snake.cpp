#include "global.h"
#include <queue>
struct node{
 int v;
 int dist;
};
int getMinMoves(int *move, int len){
  queue<node> order;
  node start;
  start.v=0;
  start.dist=0;
  order.push(start); 
  bool visited[len];
  for(int i=0;i<len;i++)
   visited[i]=false;
  visited[0]=true;
  node root;
  while(!order.empty()){
   root= order.front();
    if (root.v==len-1)
     break;
    order.pop();
    for(int i=root.v;i<root.v+6 && i<len;i++){
     if(!visited[i]){
     node temp;
     move[i] == -1 ? temp.v=i : temp.v=move[i] ;
     temp.dist = root.dist+1;
     visited[i] = true;
     order.push(temp);
    }
  }
}
 return root.dist;
}


      




int main(){
  int move[30];
  int len=30;
  for(int i=0;i<len;i++)
    move[i]=-1;
  move[2]=23;
  move[4]=7;
  move[11]=25;
  move[19]=28;
  move[26]=0;
  move[20]=8;
  move[18]=6;
  move[16]=3;
  int m=getMinMoves(move,len);
  cout<<"Moves = "<<m<<endl;
 
}
  
  
  
  
 
 
