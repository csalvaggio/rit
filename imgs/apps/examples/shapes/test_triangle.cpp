#include <iostream>

#include "shapes.h"

using namespace std;

int main() {
  double a;
  double C;
  double b;

  cout << "Comprison may be made at: "
       << "https://www.mathopenref.com/triangleareasas.html" << endl;
  cout << endl;

  cout << "Define triangle (SAS) ..." << endl;
  cout << "Side a: ";
  cin >> a;
  cout << "Angle C [deg]: ";
  cin >> C;
  cout << "Side b: ";
  cin >> b;

  shapes::Triangle t(a, C, b);
  cout << "a: " << t.a() << " // b: " << t.b() << " // c: " << t.c() << endl;
  cout << "A: " << t.A() * 180.0 / M_PI
       << " [deg] // B: " << t.B() * 180.0 / M_PI
       << " [deg] // C: " << t.C() * 180.0 / M_PI << " [deg]" << endl;
  cout << "The perimeter of the defined triangle is " << t.perimeter() << endl;
  cout << "The area of the defined triangle is " << t.area() << endl;
  cout << endl;

  cout << "Revise triangle (SAS) ..." << endl;
  cout << "Side a: ";
  cin >> a;
  t.set_a(a);

  cout << "a: " << t.a() << " // b: " << t.b() << " // c: " << t.c() << endl;
  cout << "A: " << t.A() * 180.0 / M_PI
       << " [deg] // B: " << t.B() * 180.0 / M_PI
       << " [deg] // C: " << t.C() * 180.0 / M_PI << " [deg]" << endl;
  cout << "The perimeter of the defined triangle is " << t.perimeter() << endl;
  cout << "The area of the defined triangle is " << t.area() << endl;
  cout << endl;

  cout << "Revise triangle (SAS) ..." << endl;
  cout << "Angle C [deg]: ";
  cin >> C;
  t.set_C(C);

  cout << "a: " << t.a() << " // b: " << t.b() << " // c: " << t.c() << endl;
  cout << "A: " << t.A() * 180.0 / M_PI
       << " [deg] // B: " << t.B() * 180.0 / M_PI
       << " [deg] // C: " << t.C() * 180.0 / M_PI << " [deg]" << endl;
  cout << "The perimeter of the defined triangle is " << t.perimeter() << endl;
  cout << "The area of the defined triangle is " << t.area() << endl;
  cout << endl;

  cout << "Revise triangle (SAS) ..." << endl;
  cout << "Side b: ";
  cin >> b;
  t.set_b(b);

  cout << "a: " << t.a() << " // b: " << t.b() << " // c: " << t.c() << endl;
  cout << "A: " << t.A() * 180.0 / M_PI
       << " [deg] // B: " << t.B() * 180.0 / M_PI
       << " [deg] // C: " << t.C() * 180.0 / M_PI << " [deg]" << endl;
  cout << "The perimeter of the defined triangle is " << t.perimeter() << endl;
  cout << "The area of the defined triangle is " << t.area() << endl;
  cout << endl;
}
