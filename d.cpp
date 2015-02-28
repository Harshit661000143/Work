#include "global.h"
int Square(int x)
{ return x*x; }
int Cube(int x)
{ return x*x*x; }
int main()
{
int x =10;
int choice;
do
{
cout << "Enter 0 for square value, 1 for cube value: ";
cin >> choice;
} while (choice < 0 || choice > 1);
int (ptr); switch (choice)
{
case 0: ptr = Square; break;
case 1: ptr = Cube; break;
} cout << "The result is: " << ptr(x) <<"\n";
return 0; }
