#include <iostream>

#include "shapes.h"

using namespace std;

int main() {
  double radius;
  cout << "Radius: ";
  cin >> radius;

  shapes::Circle c(radius);

  cout << "Area = " << c.area() << endl;
  cout << "Perimeter = " << c.perimeter() << endl;
} 
