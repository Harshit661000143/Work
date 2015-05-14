#include<iostream>
#include<map>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<vector>
#include<list>
#include <algorithm>
#include<set>
using namespace std;
#define loop(x,n,stride) for(int x = 0; x < n; x=x+stride)
static const char alphanum[] ="abcdefghijklmn";
inline int min(int a,int b, int c)
{
 int ret=a;
 if(b<ret)
  {
   if(c<b)
    ret=c;
   else
    ret=b;
  }
 else if(c<a)
    ret=c;  
 return ret;
} 
inline int max(int a, int b)
{
 if(a>b)
  return a;
 else
  return b;
}


