/**
 * Interface file (header-only) for the Circle class
 *
 * \file  Circle.h
 * \author  Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 * \date  18 February 2021
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

class Circle {
 public:
  /**
   * Default constructor
   *
   */
  Circle() { radius_ = 1; }

  /**
   * Constructor
   *
   * \param[in]  radius  initial value for the radius of the circle [unitless]
   */
  Circle(double radius) { radius_ = radius; }

  /**
   * Getter (accessor) for the radius
   *
   * \returns  the radius of the current instance [unitless]
   */
  double radius() const { return radius_; }

  /**
   * Setter (mutator) for the radius
   *
   * \param[in]  radius  new value for the radius of the current instance
   *   [unitless]
   */
  void set_radius(double radius) { radius_ = radius; }

  /**
   * Computes the area of the circle
   *
   * \returns  the area of the current instance [unitless]
   */
  double area() const { return M_PI * radius_ * radius_; }

  /**
   * Computes the perimeter of the circle
   *
   * \returns  the perimeter of the current instance [unitless]
   */
  double perimeter() const { return 2 * M_PI * radius_; }

 private:
  double radius_;
};

}  // namespace shapes
