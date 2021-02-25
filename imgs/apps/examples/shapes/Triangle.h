/**
 * Interface file for the Triangle class
 *
 * \file  Triangle.h
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

namespace shapes {

class Triangle {
 public:
  /**
   * Constructor (default)
   *
   */
  Triangle() {
    // SAS triangle definition
    a_ = 1;
    C_ = M_PI / 2;
    b_ = 1;

    c_ = sqrt(a_ * a_ + b_ * b_ - 2 * a_ * b_ * cos(C_));
    A_ = acos((b_ * b_ + c_ * c_ - a_ * a_) / (2 * b_ * c_));
    B_ = acos((c_ * c_ + a_ * a_ - b_ * b_) / (2 * c_ * a_));
  }

  /**
   * Constructor
   *
   * \param[in]  a  the length of side a
   * \param[in]  C  the included angle of sides a and b [deg]
   * \param[in]  b  the length of side b
   */
  Triangle(double a, double C, double b) {
    // SAS triangle definition
    a_ = a;
    C_ = C * M_PI / 180.0;
    b_ = b;

    c_ = sqrt(a_ * a_ + b_ * b_ - 2 * a_ * b_ * cos(C_));
    A_ = acos((b_ * b_ + c_ * c_ - a_ * a_) / (2 * b_ * c_));
    B_ = acos((c_ * c_ + a_ * a_ - b_ * b_) / (2 * c_ * a_));
  }

  /**
   * Destructor
   *
   */
  ~Triangle(){};

  /**
   * Getter (accessor) for side a of the triangle
   *
   * \returns  the length of side a
   */
  double a() const { return a_; };

  /**
   * Setter (mutator) for side a of the triangle
   *
   * \param[in]  a  the length of side a
   */
  void set_a(double a);

  /**
   * Getter (accessor) for side b of the triangle
   *
   * \returns  the length of side b
   */
  double b() const { return b_; };

  /**
   * Setter (mutator) for side b of the triangle
   *
   * \param[in]  b  the length of side b
   */
  void set_b(double b);

  /**
   * Getter (accessor) for side c of the triangle
   *
   * \returns  the length of side c
   */
  double c() const { return c_; };

  /**
   * Getter (accessor) for angle A of the triangle
   *
   * \returns  the angle A (included angle of sides b and c) [deg]
   */
  double A() const { return A_; };

  /**
   * Getter (accessor) for angle B of the triangle
   *
   * \returns  the angle B (included angle of sides a and c) [deg]
   */
  double B() const { return B_; };

  /**
   * Getter (accessor) for angle C of the triangle
   *
   * \returns  the angle C (included angle of sides a and b) [deg]
   */
  double C() const { return C_; };

  /**
   * Setter (mutator) for angle C of the triangle
   *
   * \param[in]  c  the angle C (included angle of sides a and b) [deg]
   */
  void set_C(double C);

  /**
   * Computes the perimeter of the triangle
   *
   * \returns  the perimeter of the triangle
   */
  double perimeter() const { return a_ + b_ + c_; }

  /**
   * Computes the area of the triangle
   *
   * \returns  the area of the triangle
   */
  double area() const;

 private:
  double a_;
  double A_;
  double b_;
  double B_;
  double c_;
  double C_;
};

}  // namespace shapes
