
/**
 * Implementation file for the Triangle class
 *
 * \file  Triangle.cpp
 * \author  Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 * \date  25 February 2021
 *
 * \copyright  Copyright (C) 2021, Rochester Institute of Technology
 * \license  GPL
 *
 * \version  1.0.0
 *
 * \namespace  shapes
 *
 * \warning
 *   This source code is provided "as is" and without warranties as to
 *   performance or merchantability. The author and/or distributors of
 *   this source code may have made statements about this source code.
 *   Any such statements do not constitute warranties and shall not be
 *   relied on by the user in deciding whether to use this source code.
 *
 * \warning
 *   This source code is provided without any express or implied warranties
 *   whatsoever. Because of the diversity of conditions and hardware under
 *   which this source code may be used, no warranty of fitness for a
 *   particular purpose is offered. The user is advised to test the source
 *   code thoroughly before relying on it. The user must assume the entire
 *   risk of using the source code.
 *
 */

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
