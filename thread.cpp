#include <iostream>       // std::cout
#include <thread>         // std::thread
using namespace std;
class example{

private:
  std::thread *	 m_pThread;
public:
   example(){
  m_pThread = new std::thread(&example::startSimulation, this);
  m_pThread->join();
}
void startSimulation();
};

void example::startSimulation(){
  int i=0;
  for(;i<5;i++){
    cout<<"Printing\n ";
  }
} 
  // do stuff...


int main() 
{
/*
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (foo);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";
*/
  example e;
  
  example e1;
  example e2;
  return 0;
}
