/** Interface file for vector shifting
 *
 *  \file utils/shift_vector/ShiftVector.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 29 October 2020
 */

#include <iostream>

#include <Eigen/Dense>

using namespace std;

namespace utils {

/** Shift elements in a vector by a specified offset
 *
 *  \param[in] vector
 *    provided Eigen::Matrix (vector) to be shifted of type _Scalar
 *  \param[in] offset
 *    number of elements to shift the provided vector (positive offset
 *    shift elements to the right, negative offset shift elements to
 *    the left)
 *
 *  \return
 *    shifted vector of type _Scalar
 */
template <typename _Scalar, int _Rows, int _Cols>
Eigen::Matrix<_Scalar, _Rows, _Cols>
  ShiftVector(const Eigen::Matrix<_Scalar, _Rows, _Cols>& vector,
               const int offset) {
  auto n = vector.size();
  Eigen::Matrix<_Scalar, _Rows, _Cols> shifted_vector(n);
  for (int idx = 0; idx < n; idx++) {
    shifted_vector[idx] = vector[(n + (idx - offset)) % n];
  }
  return shifted_vector;
}
}
