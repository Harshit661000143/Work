#include "global.h"


class Heap
{
 public:
 int heapSize;
 int capacity;
 int *elements;
 public:
 int extractMin();
 void decreaseKey(int key, int newVal); 
 void insertKey(int val);
 void deletekey(int key);
 void minHeapify(int key);
 void printArray();
 int getMin(){ return elements[0];}
 int parent(int i) {return (i-1)/2; 
 }
 int left(int i) {return 2*i+1;
 } 
 int right(int i) {return 2*i+2;
 }
 void swap(int *ptr, int *ptr1)
 {
  int tmp=*ptr;
  *ptr= *ptr1;
  *ptr1=tmp;
 }
  Heap(int n)
{
 capacity=n;
 heapSize=0;
 elements= new int[n];
}
};

void Heap:: decreaseKey(int key, int newVal)
{
 elements[key]=newVal;
 while((key!=0) && (elements[parent(key)]>elements[key]))
  {
    swap(&elements[parent(key)],&elements[key]);
    key=parent(key);
  }
}
 void Heap:: insertKey(int val)
{
  if(heapSize ==capacity)
   {
     cout<<"Buffer Overflow\n";
     return;
   }
   elements[heapSize]=val;
   int i=heapSize;
   heapSize++;
   while(i!=0 && elements[parent(i)]>elements[i])
   {
     swap(&elements[parent(i)],&elements[i]);
     i=parent(i);
   }
}
void Heap:: printArray()
{
  loop(x,heapSize,1)
   {
    cout<<elements[x]<<"\t";
   }
   cout<<"\n";
}
int Heap:: extractMin()
{
  if(heapSize<=0)
   {
     cout<<"Buffer Empty\n";
     return -1;
   }
   if(heapSize==1)
   {
    heapSize--;
    return elements[heapSize];
   }
   int result=elements[0];
   elements[0]=elements[heapSize-1];
   heapSize--;
   minHeapify(0);
   return result;
}
void Heap:: minHeapify(int k)
{
  int l=left(k);
  int r=right(k);
  int small=k;
 if((l<heapSize)&&elements[l]<elements[k])  
  {
   small=l;
  }
if((r<heapSize)&&(elements[r]<elements[small]))
  {
   small=r;
  }
  if (small!=k)
    {
      swap(&elements[small],&elements[k]);
      minHeapify(small);
    }
}
 void Heap:: deletekey(int key)
{
elements[key]=-99;
while(parent(key)<heapSize && parent(key)>=0)

{
minHeapify(parent(key));  

key=parent(key);
if(key==0)
break;
cout<<"key changed to  "<<key<<"\n";
}
}

 
int main()
{
  Heap h(10);
  h.insertKey(30);
  h.insertKey(20);
  h.insertKey(15);
  h.insertKey(5);
  h.insertKey(35);
  h.insertKey(25);
  h.insertKey(10);
  h.insertKey(50);
  h.printArray();
  h.deletekey(5);
  h.printArray();
  h.extractMin();
  h.printArray();
//  h.extractMin();
//  h.extractMin();
 // h.printArray();
  Heap *t=new Heap(10);
  cout<<"Capacity "<<t->capacity<<"\n";
  
}
  






