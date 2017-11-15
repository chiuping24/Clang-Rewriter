#include <iostream>
using namespace std;

void do_math(int *a) {
  *a += 5;
}

class Rectangle {  //comment
    int width, height;
  public:
    void set_values (int,int);
    int area() {return width*height;}
};

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}

int main () {
  int val =4;
  Rectangle rect; //class
  rect.set_values (3,4);  
  do_math(&val);
  cout << "area: " << rect.area()<<"\n";
  return 0;
}
