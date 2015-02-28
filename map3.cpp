#include "global.h"
//#include <vector>
//#include <map>

class compare_1 { // simple comparison function
   public:
      bool operator()(const int x,const int y) { return (x-y)>0; } // returns x>y
};

class compare_2 { // a more complicated comparison function which varies according to specified parameter s
   public:
      compare_2(int s_) : s(s_) {};		
      bool operator()(const int x,const int y) { return s*(x-y)>0; } // returns x>y if s>0, else x<y
   private:
      int s;
};

void changeMe(vector<int> *V)
{
 V->push_back(100);

 V->push_back(50);
 V->push_back(120);
}

int main()
{
  vector<int> *v = new vector<int>;
#if 0
   //v->at(2); //Retrieve using pointer to member
    v->operator[](2); //Retrieve using pointer to operator member
    v->size(); //Retrieve size
    vector<int> &vr = *v; //Create a reference
    vr[2]; //Normal access through reference
    delete &vr; //Delete the reference. You could do the same with
                //a pointer (but not both!)

   vector<int> *v =new vector;
#endif
   v->push_back(20);			
   v->push_back(10);			
   v->push_back(60);			
   v->push_back(40);
   for(int i=0;i<v->size();i++)
    {
      cout<<v->at(i)<<"\t";
    }
    cout<<"\n";
    sort(v->begin(),v->end());
   for(int i=0;i<v->size();i++)
    {
      cout<<v->at(i)<<"\t";
    }
    cout<<"\n";
    changeMe(v);	
    cout<<"\n";
    sort(v->begin(),v->end());
   for(int i=0;i<v->size();i++)
    {
      cout<<v->at(i)<<"\t";
    }
    cout<<"\n";
//   sort(v.begin(), v.end(), compare_1()); // ok
 //  sort(v.begin(), v.end(), compare_2(-1)); // ok
	
 //  map<int,int,compare_1> mymap1; // ok
 //  map<int,int,compare_2> mymap2(compare_2(-1)); // error: a call to a constructor cannot appear in a constant-expression
   return 0;
}
