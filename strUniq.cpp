#include "global.h"

class Prepare
{
  public: 
  string stringA;
  void setString(string stringEX);
  string getString();
  bool isUnique();
};
void Prepare:: setString(string stringEX)
{
stringA=stringEX;
}
string Prepare:: getString()
{
 return stringA;
}
bool Prepare:: isUnique()
{
   map<char,int> history;
   loop(x,stringA.size())
    {
      if(history[stringA[x]])
         return false;
   else
    {
      history[stringA[x]]=1;
    }
  }
    
  return true;
   


}

int main()
{
 Prepare prep;
 Prepare prep2;
 prep.setString("gqdd");
 prep2.setString("dog");
 string result= prep.getString();
// cout<<"Result:=\t"<<result<<"\n";
// cout<<"Result:=\t"<<prep.isUnique()<<"\n";
 sort(prep.stringA.begin(),prep.stringA.end()); 
 sort(prep2.stringA.begin(),prep2.stringA.end());
 cout<<prep.stringA; 
 cout<<prep2.stringA; 
 cout<<"TRUTH"<<prep.stringA.compare(prep2.stringA)<<"\n";
 

}

   
