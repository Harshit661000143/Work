#include "global.h"

const int MAX = 3;

int main ()
{
   int  var[] = {10, 100, 200};
   int  i;
   int **ptr=new int*[10];

  //  ptr=new int;
   /* let us have address of the first element in pointer */
//   *ptr = var[1];
    *ptr= new int;
    delete ptr;
 int size_out=10;
double*** desc = new double**[size_out];
for (int i=0; i<size_out; i++)
    desc[i] = new double*[size_out];


for (int i=0; i<size_out; i++)
    delete[] desc[i];

delete[] desc;
vector<double> row1;
row1.push_back(1.0); row1.push_back(2.0); row1.push_back(3.0);

vector<double> row2;
row2.push_back(4.0); row2.push_back(5.0); row2.push_back(6.0);

vector<vector<double> > vector_of_rows;
vector_of_rows.push_back(row1);
vector_of_rows.push_back(row2);

 //   **ptr=100;
//   delete[] ptr;
   i = 0;
 //   cout<<**ptr<<"\n";
#if 0
   while ( ptr <= &var[MAX - 1] )
   {

      printf("Address of var[%d] = %x\n", i, ptr );
      printf("Value of var[%d] = %d\n", i, ++(*ptr) );
    /* point to the previous location */
      ptr++;
      i++;
   }
   loop(x,3)
   {
    cout<<var[x]<<"\n";
   }
#endif
 
   return 0;
}
