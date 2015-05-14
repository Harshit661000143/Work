
#include "global.h"

struct node{
  int data;
  node* next;
};
class Linked{
  public:
  node *head;
   Linked(){
    head=NULL;
   }
   void insert(int d){
    node *temp= new node;
    temp->data=d;
    temp->next=head;
    head=temp;
   }
  void printMe(){
  node *orig= head;
   while(head!=NULL)
   {  
     cout<<head->data<<endl;
     head=head->next;
   }   
   head=orig;
}
   void reverseme(node *h, node *& done){
  // static node* done;
   if(h->next==NULL){
   head=h;
   done= head;
   }
   else{
  reverseme(h->next, done);
   node *temp=h;
   temp->next=NULL;
   done->next=temp;
   done=done->next;
   }
}
   
   
};
int main(){
  Linked root;
  root.insert(10);
  root.insert(40);
  root.insert(50);
  root.insert(20);
  root.insert(30);
  root.printMe();
  root.reverseme(root.head, root.head);
  root.printMe();
}
