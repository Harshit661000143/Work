#include "global.h"

class stack
{
 public:
 int n;
 int *elements;
 int maxSize;
 void set()
 {
  maxSize=10;
  //n=0;
  elements= new int[maxSize];
 }
};
void  push(stack *s, int elem);
int  pop(stack *s);
void  printStack(stack *s);

void  push(stack *s, int elem)
{
  if(s->n>s->maxSize){
 // if (s->n > 13) {  
   cout<<"***Buffer Full***\n";
   return;
  }
 cout<<"n is "<<s->n<<" :: elem -";
 s->elements[s->n]=elem;
 cout<<s->elements[s->n];
  ++s->n;
  cout<<"Incrementing n=\t"<<s->n<<"\n";
  
} 
int  pop(stack *s)
{
  if(s->n<=0)
  {
   cout<<"***Buffer Empty***\n";
   return NULL;
  }
  return s->elements[s->n];
  s->n--;
} 
void printStack(stack *s)
{
  if(s->n==0){
   cout<<"Buffer Empty\n";
   return;
  }
  cout<<"****Printing stack****\n";
  loop(x,s->n)
   {
     cout<<s->elements[x]<<"\t";
   }
   cout<<"\n";
}



 
 
 


int main()
{
 int p;
 stack *s= (stack *)malloc(sizeof(stack));
 s->set();
 cout <<"S.maxSize=\t"<<s->maxSize<<"\n";
 loop(x,17)
   push(s,x);
 loop(x,17)
{
  int p = pop(s);
  cout<<p<<"\t";
  cout<<"\n";
}
 //s->push(40);
 printStack(s);

}
 
 
