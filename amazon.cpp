#include <iostream>
#include <stdio.h>
using namespace std;

struct node{
  node *next;
  int data;
};

node* newNode(int data){
  node *newNod= new node;
  newNod->next=NULL;
  newNod->data=data;
  return newNod;
}

node* push(node **prevNode,int data){
  node *newNod=newNode(data);
  newNod->next=*prevNode;
  *prevNode=newNod;
}

void print(node *head)
{
  while(head!=NULL)
  {
    cout<<head->data<<"\t";
    head = head->next;
  }
} 

void printReverse(node *head){
 if(head==NULL)
   return;
 printReverse(head->next);
 cout<<head->data;
 cout<<"\n";
}
  
void reverseList(node* &head){
  //while(head!=NULL){
  node *prev =NULL;  
  node *temp = (head)->next;
  (head)->next = prev;
  prev = head;
  while(temp!=NULL){
    node *tmp = temp->next;
    temp->next = prev;
    prev = temp;
    temp = tmp;
  }
  head= prev;
}

#if 1
void reverse(node* &head){
  node *first= head;
  if(head==NULL)
    return; 
  node *rest= first->next;
  if(rest==NULL)
    return; 
  reverse(rest);
  first->next->next = first;
  first->next=NULL;
  head = rest; 
  

}      
#endif
void sum(int &a, int &b)
{
  a=a+b;
}     
  
  
  



     

int main(){
 node *head=newNode(10);
 push(&head,12);
 push(&head,13);
 push(&head,14);
 push(&head,16);
 print(head);
 //printReverse(head);
 reverse(head);
 cout<<"\n";
 print(head);
 delete head;
 int a=2,b=3;
 sum(a,b);
 cout<<a<<"\n";
}
