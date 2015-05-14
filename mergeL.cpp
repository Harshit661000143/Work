#include "global.h"


struct node{
  node *next;
  int data;
};

class Linked{
 public:
 node *head;
 Linked(){
  head=NULL;
 }
 void createNode(int data){
  node *temp=new node;
  temp->data=data;
  temp->next=head;
  head=temp;
 }
 void printMe(){
  while(head!=NULL){
   cout<<head->data<<endl;
   head=head->next;
  }
 }
void reverseUtil(node* &h){
  if(h->next==NULL){
    return;
  }
  cout<<"ONCE"<<endl;
  reverseUtil(h->next);
  h->next->next=h;
  h->next=NULL;
}



 void reverseMe(){
   cout<<"Started";
   reverseUtil(head);
 }
};
int main(){
 Linked L;
 L.createNode(10);
 L.createNode(20);
 L.createNode(30);
 L.createNode(40);
 //L.printMe();
 L.reverseMe();
 L.printMe();
}
 
