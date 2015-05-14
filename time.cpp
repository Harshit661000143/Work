#include <iostream>
#include <ctime>

using namespace std;

int main( )
{
   // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   cout << "The local date and time is: " << dt << endl;

   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   cout << "The UTC date and time is:"<< dt << endl;

time(&now);
char ts[sizeof "1970-01-01T00:00:00+00:00"];
strftime(ts, sizeof ts, "%FT%T%z", gmtime(&now));
printf("Timestamp: %s\n\n", ts);
}
