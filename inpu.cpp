#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> *vecptr = new vector<string>(10);
int veclen;

void getinput()
{
 string temp;
 for(int i = 0; i < 3; i++)
    {
     cin>>temp;
     (*vecptr)[i] = temp;
    }
    veclen = (*vecptr).size();
}


int main()
{
 getinput();
    cout<<"veclen= "<<veclen<<"\t";
    map<int,int>
    for(int i = 0; i < veclen; i++)
    {
     string temp=(*vecptr)[i];
     for(int j=0;j<temp.size();j++)
     {
        if(isdigit(temp[j]))
         {
             cout<<temp[j]<<"\t";
         }
     }
     cout<<"\n";
  }

      

 return 0;
}
