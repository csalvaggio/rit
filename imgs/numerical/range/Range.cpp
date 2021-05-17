/**
 * Implementation file for range creation functions
 *
 * \file  imgs/numerical/range/Range.cpp
 * \author  Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 * \date  23 March 2021
 *
 * \copyright  Copyright (C) 2021, Rochester Institute of Technology
 * \license  GPL
 *
 * \version  1.0.0
 *
 * \namespace  numerical
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

#include "imgs/numerical/range/Range.h"

namespace numerical {

std::vector<int> Range(int a, int b) {
  std::vector<int> v;
  v.reserve(b - a + 1);
  for (int element = a; element <= b; element++) {
    v.push_back(element);
  }
  return v;
}

std::vector<double> Range(double a, double b, std::size_t n) {
  std::vector<double> v;
  v.reserve(n);
  double increment = (b - a) / (n - 1);
  for (std::size_t idx = 0; idx < n; idx++) {
    v.push_back(a + idx * increment);
  }
  return v;
}

std::vector<int> Range(std::size_t n) {
  return Range(0, n - 1);
}

}
