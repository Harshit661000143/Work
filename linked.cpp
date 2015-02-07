#include "global.h"

struct node
{
 int data;
 node *next;
};
struct stack{
node **mainNode;
node **head;
node **last;
};           

  node* createnode(int elem){
  node *newNode= new node;
  newNode->next=NULL;
  newNode->data=elem;
  return newNode;
 } 

void push(stack &s,int elem)
{
 node *newNode = createnode(elem);
if(s.mainNode!=NULL){
   newNode->next=(*s.mainNode);
   *s.mainNode=newNode;
   s.head=s.mainNode;
 }
 else{
   s.mainNode=new node*; 
   *s.mainNode=newNode;
   s.last=&(newNode->next);
 }
}
void printNode(stack& s)
{ 
  node *n= *s.mainNode;
#if 1
  while(n->next)
  {
    cout<<n->data<<"\t";
    n=n->next;
  }
  if(!n->next)
    cout<<n->data<<"\n";
#endif
}
void deleteRecur(node **n, int key)
{
  if(*n){
  if((*n)->data==key)
    {
      *n=(*n)->next;
      deleteRecur(n,key);
    }
    else
     deleteRecur(&(*n)->next,key);
  }
 return;  
}     
    
void merge(stack &s, stack &s2)
 {
   *s.last=*s2.head;
 }    
   


int main()
{
 stack s[2];
 loop(x,2,1)
   s[x].mainNode=NULL;
 loop(x,5,1){
   push(s[0],x);
   push(s[1],5-x);}
// deleteRecur(&n,40);
 loop(x,2,1)
   printNode(s[x]);
 merge(s[0],s[1]);
 loop(x,2,1)
   printNode(s[x]);
}
 

