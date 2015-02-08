#include "global.h"

template <class T>
class Priority{
 
 public:
   T *myarray;
   map<int,T> history;
   Priority(int size)
   {
     myarray= new T[size];
   }
   int  getIndex(int key);
void  Storedata(T data,int key);
};
   
template <class T>
int Priority<T>:: getIndex(int key)
  {
     int index=0;
     
      loop(x,history.size(),1)
        {
          if(history[x]>key)
            continue;
          else
           {
              index=x;
              break;
           }
         }
      return index;
   }
template <class T>
void Priority<T>:: Storedata(T data,int key)
{
   int index=getIndex(key);
   for(int i=history.size();i>index;i--)
    {
        myarray[i]=myarray[i-1];
        history[i]=history[i-1];
    } 
   myarray[index]=data;
   history[index]=key;
}



    
  

int main () {
  Priority <double> myobject (10);
  myobject.Storedata(1.5,10);
  myobject.Storedata(20.9,100);
  myobject.Storedata(12.4,15);
  myobject.Storedata(12.5,15);
  myobject.Storedata(12.6,15);
  myobject.Storedata(1.2,115);
  myobject.Storedata(1.4,400);
  loop(x,myobject.history.size(),1)
   {
    cout<<"x= "<<x<<"\t"<<"history= "<<myobject.history[x]<<"\t"<<"myarray= "<<myobject.myarray[x]<<"\n";
   }
 
  
  return 0;
}
   
               
