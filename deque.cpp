#include "global.h"

struct node{
  int data;
  node *next;
  node *prev;
 };
class queue{
 
 public:
 node *rear;
 node *front;
 int capacity;
 
 queue(int n)
 {
   capacity=n;
   rear=NULL;
   front=NULL;
   cout<<"SIZE=\t"<<n;
 }
 void insertFront(int d)
 {
   node *newNode= new node;
   newNode->data=d;
   newNode->next=NULL;
   newNode->prev=NULL;
   if(front==NULL)
    {
      front=newNode;
      rear= newNode;      
    }
    else
    {
       newNode->prev=rear;
       newNode->next=front;
       front= newNode;
    }
  }

  void insertLast(int d)
  {
   node *newNode= new node;
   newNode->data=d;
   newNode->next=NULL;
    
void printQ(int size)
 {
   loop(x,size,1)
    {
      cout<<front->data<<"\n";
      front=front->next;
    }
 }
      
        
};
int main()
{
 queue q(10);
 loop(x,5,1)
  q.insertFront(x);
  q.printQ(5);
  

}
   





