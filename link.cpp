#include"global.h"

//template <class T>
class Linked{

 int data;
 Linked *next;
 Linked *prev;
 
 Linked()
 {
  next= new Linked;
  prev= new Linked;
 }
 ~Linked()
 {
   delete next;    
   delete prev;
 }
 Linked* push(int data);


};
//template <class T>
Linked* Linked:: push(int data)
{
  Linked *newNode = new Linked;
  newNode->data = data;
  newNode->next = this;
  this= newNode;
}
 int main(int argc, char**argv)
  {
    if(argc>1)
     {
       
       cout<<"YO command line arguments, Champ!\n";
       int random=atoi(argv[1]);
       cout<<"random= "<<random<<"\n";
     }
     Linked  *head=new Linked;
     //*head= new Linked;
     head->prev=NULL;
     head->next=NULL;
     head->push(20);
  }   
     
              



   } 
     
  

    
