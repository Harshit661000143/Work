#include <iostream>
using namespace std;
// a program to work out how to get a total value in to two buckets
// by James Brunskill
const int A = 5, B = 7;

int main()
{
  int la, lb, tot;
  int i=0;  
  
  cout << "There are two buckets A (" << A << " liters) and B (" << B << " liters) You can only do three things:" << endl;
  cout << "1. Completely Fill container A -FILL" << endl;
  cout << "2. Completely empty container B -EMPTY" << endl;
  cout << "3. Transfer contents of container A in to container B, untill B is Full or A is Empty - TRANSFER" << endl;
  cout << " Using these operations you can reach any number between 1 and 12 " << endl; 
  
  while (i == 0)
    { 
      cout << "Enter the amout of water you want in bucket both buckets put together:" << endl;
      cin >> tot;
      if(tot > 11)
	cout << "\nError too much water please try again\n";
      else 
        i = 1;
     }
   
  cout << "These are the steps you need to follow to get a total of " << tot << " litres in the buckets";
  
  cout << "\n\n\n| Step |     Operation     |  Litres in A  |  Litres in B  |  Total Litres  |\n";
  
  cout << i << "      |     Initial       |      ?        |       ?       |       ?        |" << endl; 
  i++;

  lb = 0; //empty b
  cout << i << "      |      EMPTY        |      ?        |       " << lb << "       |     ? + " << lb << "      |" << endl; 
  i++;  

  la = A; // fill a
  cout << i << "      |      FILL         |      " << la << "        |       " << lb << "       |       " << (la + lb) << "        |" << endl; 
  i++;
     
  while ((la + lb) !=  tot)
    {
      if(la == 0)
	{
	  la = A; // Fill a
	  // cout << "********There is 0 litres in a so fill it********" << endl;
	  cout << i << "      |      FILL         |      " << la << "        |       " << lb << "       |       " << (la + lb) << "     |" << endl; 
	  
	  i++;
	} 
      
      if(la == A)
	{
	  lb = la +lb;
	  la = 0;
	  
	  if(lb > B)
	    {
	      la = lb - B;
	      lb = B;
	    }
	  
	  // cout << "********A is full so transfer********" << endl;
	  
	  cout << i << "      |    TRANSFER       |      " << la << "        |       " << lb << "       |       " << (la + lb) << "     |" << endl; 
	  i++;
	}
      
      if(lb == B && (la +lb)!= tot)
	{  
	  lb = 0; // Empty b
	  
	  // cout << "********b is full so empty it********" << endl;
	  
	  cout << i << "      |      EMPTY        |      " << la << "        |       " << lb << "       |        " << (la + lb) << "     |" << endl; 
	  
	  i++;
	} 
      if (lb != B)
	{ 
	  lb = la + lb;
	  la = 0;
	  
	  if(lb > B)
	    {
	      la = lb - B;
	      lb = B;
	    }
	  
	  //cout << "****************B is not full so Transfer ***************************" << endl;
	  cout << i << "      |    TRANSFER       |      " << la << "        |       " << lb << "       |       " << (la + lb) << "     |" << endl; 
	  
	  i++;
	}    
      
      
    }
  return 0;
}














