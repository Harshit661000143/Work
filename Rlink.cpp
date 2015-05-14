#include "global.h"

struct node{
 int data;
 node *next;
};

node *front,  *back;
void pushNode(int data, node* &head){
 node* temp= new node;
 temp->data=data;
 if(head==NULL)
  temp->next=NULL;
 else
  temp->next = head;
 head=temp;
}

void printNode(node *head){
  while(head!=NULL){
  cout<<head->data<<endl;
  head=head->next;
 }
}

void reverseNode(node* &head){
  if(head==NULL) return;
  node *prev=NULL;
  node *cur=head;
  while(cur){
   node *tmp= cur->next;
   cur->next=prev;
   prev=cur;
   cur=tmp;
  }
  head=prev;
}


  void partitionNode(node *Head){
  if(Head ==NULL || Head->next==NULL)
   return;
  node *slow=Head;
  node *fast=Head->next;
  fast=fast->next;
  while(fast!=NULL){
   fast=fast->next;
   slow=slow->next;
   if(fast!=NULL)
     fast=fast->next;
  }
  back=Head;
  front=slow->next;
  
  slow->next=NULL;
 }      




    
  





int main(){

  node *Head=NULL;
  pushNode(10,Head);
  pushNode(20,Head);
  pushNode(30,Head);
  pushNode(70,Head);
  pushNode(60,Head);
  pushNode(110,Head);
  pushNode(90,Head);
  printNode(Head);
  reverseNode(Head);
  cout<<"Reversed\n";
  printNode(Head);
  partitionNode(Head);
  cout<<"partitioned at"<<endl;
  //cout<<back->data<<"--->"<<front->data<<endl;
  printNode(back);
  cout<<endl;
  printNode(front);
  reverseNode(back);
  reverseNode(front);
  printNode(back);
  cout<<endl;
  printNode(front);
//  cout<<"Reversed\n";
  return 0;
}

 
