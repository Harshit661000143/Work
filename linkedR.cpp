#include "global.h"


//template <typename t>
class Node{
  
  public:
  Node *next;
  int data;
   Node(){
    next = NULL;
  }
  void operator=(Node *newnode){
   next= newnode->next;
   data= newnode-> data;
 }
  Node* insert(int data){
   Node* newNode= new Node;
   newNode->data= data;
   newNode->next= this;
   return newNode;
   //this= newNode;
 }
 int getData(){
  return data;
}
};
int main(){
   Node *root = new Node;
  root=root->insert(10);
  root=root->insert(40);
  root=root->insert(50);
  root=root->insert(60);
  root=root->insert(20);
  while(root->next!=NULL){
     cout<<root->getData()<<endl;
     root= root->next;
 }
  return 0;
}
  
     
  

