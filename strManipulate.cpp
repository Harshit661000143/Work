#include "global.h"
int main()
{
// char *space=" ";
 char str[64];
 char result[64];
 str[20]='\0';
 result[20]='\0';
 int count=0,i=0;
 loop(x,20,1)
  {
    str[x]=alphanum[rand()%5]; 
  }
  loop(x,20,1)
  {
   if(str[x]==str[x+1])
   {
     count++;
   }
   else
   {
        result[i]=str[x];
        ++count;
	//cout<<"counting: "<<count; 
        result[i+1]=+'0'+ count;
        
      //  cout<<"RESULT="<<result[i+1]<<"::"<<count<<"\n";
        i=i+2;
     count=0;
    }
   } 
   
 loop(x,20,1)
  cout<<str[x]<<",";   
 cout<<"\n";
 loop(x,40,1)
  cout<<result[x]<<",";   
 cout<<"\n";       
  
  }

    
