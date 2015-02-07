#include "global.h"

struct Point {
   double x, y;
   struct Point& operator+=(const Point& rhs) { x += rhs.x; y += rhs.y; return *this; }
   struct Point& operator+=(const double& k) { x += k; y += k; return *this; }
   struct Point& operator=(const Point& rhs) { x = rhs.x; y = rhs.y; return *this; }
};

Point operator+(Point lhs, const Point& rhs) { return lhs += rhs; }
Point operator+(Point lhs, const double k) { return lhs += k; }
Point operator+(const double k, Point rhs) { return rhs += k; }

int main()
{
Point p;
p.x=1;
p.y=2;
Point p2;
p2.x=10;
p2.y=22;
Point p3;
p3= p+p2;
p=p2;
cout <<p3.x<<"\t"<<p3.y<<"\n";
cout <<p.x<<"\t"<<p.y<<"\n";
cout <<p2.x<<"\t"<<p2.y<<"\n";
}


