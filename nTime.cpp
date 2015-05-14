/* gmtime example */
#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, gmtime */
#include <string>
#define MST (-7)
#define UTC (0)
#define CCT (+8)
#include <iostream>
using namespace std;



string currtime(int i){

  string Time; 
  time_t m_Time;
  struct tm * ptm;

  time ( &m_Time );
  ptm = gmtime(&m_Time);
  if(ptm->tm_hour+i<=0){
    Time=to_string(ptm->tm_hour+i+12);
  }
  else
    Time=to_string((ptm->tm_hour+i)%24);
  Time+=":";
  if((ptm->tm_min)<9) { 
    Time+="0" ;
  }
  Time+=to_string((ptm->tm_min));
  Time+=":";
  if((ptm->tm_sec)<9){
    Time+="0" ;
  }
  Time+=to_string((ptm->tm_sec));
  return Time;
}


int main ()
{



  cout<<"Chile :"<<currtime(-3)<<endl;
  cout<<"Fin :"<<currtime(3)<<endl;
  cout<<"Ore :"<<currtime(-7)<<endl;
  cout<<"Sing :"<<currtime(-4)<<endl;
  cout<<"IOWA :"<<currtime(-5)<<endl;
  return 0;
}
