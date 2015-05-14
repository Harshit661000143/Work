#include "global.h"
#include <thread>
#include <exception>
#include <mutex>

std::mutex                       g_mutex;
std::vector<int>  jobs;
/*
void throw_function()
{
   throw std::exception();
}
*/
void func(int j)
{
//   try
  // {
//      std::lock_guard<std::mutex> lock(g_mutex);
      jobs.push_back(j);
  // }
  // catch(...)
  // {
  //    throw_function();
  // }
}

int main()
{

   std::thread t1(func,2);
   std::thread t(func,1);
   t.join();

   for(int e=0; e<=jobs.size();e++)
   {
     std::cout<<jobs.at(e);;    
   }

   return 0;
}
