#include <cmath>

#include "Triangle.h"

namespace shapes {

void Triangle::set_a(double a) {
  a_ = a;

  c_ = sqrt(a_ * a_ + b_ * b_ - 2 * a_ * b_ * cos(C_));
  A_ = acos((b_ * b_ + c_ * c_ - a_ * a_) / (2 * b_ * c_));
  B_ = acos((c_ * c_ + a_ * a_ - b_ * b_) / (2 * c_ * a_));
}

void Triangle::set_b(double b) {
  b_ = b;

  c_ = sqrt(a_ * a_ + b_ * b_ - 2 * a_ * b_ * cos(C_));
  A_ = acos((b_ * b_ + c_ * c_ - a_ * a_) / (2 * b_ * c_));
  B_ = acos((c_ * c_ + a_ * a_ - b_ * b_) / (2 * c_ * a_));
}

void Triangle::set_C(double C) {
  C_ = C * M_PI / 180.0;

  c_ = sqrt(a_ * a_ + b_ * b_ - 2 * a_ * b_ * cos(C_));
  A_ = acos((b_ * b_ + c_ * c_ - a_ * a_) / (2 * b_ * c_));
  B_ = acos((c_ * c_ + a_ * a_ - b_ * b_) / (2 * c_ * a_));
}

double Triangle::area() const {
  // Using Heron's formula
  return sqrt(Triangle::perimeter() / 2 * (Triangle::perimeter() / 2 - a_) *
              (Triangle::perimeter() / 2 - b_) *
              (Triangle::perimeter() / 2 - c_));
}

}  // namespace shapes
