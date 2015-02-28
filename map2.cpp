#include "global.h"
template<typename T>
int main()
{      
	int s=-1; 
        compare c2; 
        compare_val c3( -1 );
        compare_val c4( s );
			
	map<int,int,compare> mymap1;
	map<int,int,compare> mymap2( c2 );
	map<int,int,compare_val> mymap3( c3 );
	map<int,int,compare_val> mymap4( c4 );

	mymap1.size();
	mymap2.size();	
	mymap3.size();
	mymap4.size();	
	return 0;
}

