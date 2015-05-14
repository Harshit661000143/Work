#include "global.h"
#include <thread>
#include <exception>
#include <mutex>
using namespace std;

std::mutex                       g_mutex;
class Example{

 vector<int> jobs;
 ExampleProxy *proxy;
 std::thread *	m_pThread;
 publici:
  Example(int i){
  m_pThread = new new std::thread(&Example::StartSimulation,i); 
}
 void StartSimulation(int j){
     std::lock_guard<std::mutex> lock(g_mutex);
     jobs.push_back(j);
 }
 void setProxy(ExampleProxy* P){
  proxy= P;
 }
};
class ExampleProxy{
 Example *p;
 public:
  int Initialize(Example* ptr){
  p=ptr;
 }
};

int main(){

  Example E(1);
  Example E2(20);
  Example E3(11);
  Example E4(23);
  return 0;
}
