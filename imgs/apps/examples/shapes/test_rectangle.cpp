#include <iostream>

#include "shapes.h"

using namespace std;

int main() {
  double l;
  double w;

  cout << "Define rectangle ..." << endl;
  cout << "Length: ";
  cin >> l;
  cout << "Width: ";
  cin >> w;

  shapes::Rectangle r(l, w);
  cout << "Length: " << r.length() << " // Width: " << r.width() << endl;
  cout << "The perimeter of the defined rectangle is " << r.perimeter() << endl;
  cout << "The area of the defined rectangle is " << r.area() << endl;
  cout << endl;

  cout << "Refine rectangle ..." << endl;
  cout << "Length: ";
  cin >> l;

  r.set_length(l);
  cout << "Length: " << r.length() << " // Width: " << r.width() << endl;
  cout << "The perimeter of the defined rectangle is " << r.perimeter() << endl;
  cout << "The area of the defined rectangle is " << r.area() << endl;
  cout << endl;

  cout << "Refine rectangle ..." << endl;
  cout << "Width: ";
  cin >> w;

  r.set_width(w);
  cout << "Length: " << r.length() << " // Width: " << r.width() << endl;
  cout << "The perimeter of the defined rectangle is " << r.perimeter() << endl;
  cout << "The area of the defined rectangle is " << r.area() << endl;
  cout << endl;
}
