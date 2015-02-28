// derived classes
#include <iostream>
using namespace std;

class Polygon {
  protected:
  public:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b;}
 };

class Rectangle: protected Polygon {
  public:
    int area ()
      { return width * height; }
 };

class Triangle: public Polygon {
  public:
    int area ()
      { return width * height / 2; }
  };
  
int main () {
  Rectangle rect;
  Triangle trgl;
  rect.set_values (4,5);
  trgl.set_values (4,5);
 // cout << rect.width << '\n';
//  cout << rect.height << '\n';
  cout << rect.area() << '\n';
  cout << trgl.area() << '\n';
  return 0;
}
