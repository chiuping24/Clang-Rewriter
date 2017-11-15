#include <iostream>
using namespace std;

void add5(int *a) {
  *a += 5;
}

class RectangleShape {  //comment
    int width, height;
  public:
    void setXY (int,int);
    int area() {return width*height;}
};

void RectangleShape::setXY (int x, int y) {
  width = x;
  height = y;
}

int main () {
  int value =4;
  RectangleShape rect_1; //class
  rect_1.setXY (3,4);  
  add5(&value);
  cout << "area: " << rect_1.area()<<"\n";
  return 0;
}
