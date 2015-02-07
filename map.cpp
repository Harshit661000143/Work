#include "global.h"

struct coord{
int x;
int y;
coord& operator=(const coord& b)
      {
         x= b.x;
         y= b.y;
         return *this;
      }
bool operator<(const coord& b)
      {
         if(x< b.x)
  //       y= b.y;
           return true;
         else
           return false;
      }
      coord(int a, int b)
      {
        x=a;
        y=b;
      }
};
struct classcomp {
  bool operator() (const coord& lhs, const coord& rhs) const
  { if((lhs.x <rhs.x) && (lhs.y < rhs.y))
    { cout<<"Creating inside compare\t"<<rhs.x<<"\t"<<rhs.y<<"\n";
     return true;
    }
    else 
	return false;
}
};
#if 0
coord  operator=(const coord &o) const
{
  coord nC= new coord;
  nC.x= 
 // if(x=o.x && y==o.y)
   return true;
  return false;
}
#endif 

int main()
{
 map<coord,bool,classcomp> test;
 
 coord ncoord(2,2);
test[ncoord]=true;
 coord ncoord2(2,1);
 if(test[ncoord2])
      cout<<"I am wrong\n";
// ncoord2=ncoord;
// test[ncoord2]=1;
 cout<<"TEST SIZE:="<<test.size()<<"\n";
 coord mycoord(1,1);
 if(test[mycoord])
  {
    cout<<"array:"<<test[mycoord]<<"\n";
  }
 
#if 0
 loop(x,test.size(),1)
 {
  cout<<test[x]<<"\n";
 }
#endif
}
