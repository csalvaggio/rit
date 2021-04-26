/** Implementation file for linear interpolation of one-dimensional data
 *
 *  \file numerical/interpolation/Interp1.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 26 April 2021
 */

#include <stdexcept>

#include "Interp1.h"

namespace numerical {

Eigen::VectorXd Interp1(const Eigen::VectorXd& xhat, const Eigen::VectorXd& x,
                        const Eigen::VectorXd& y) {
  Eigen::VectorXd yhat = Eigen::VectorXd::Zero(xhat.size());

  if (xhat.minCoeff() < x.minCoeff()) {
    std::string msg = "Minimum independent coefficient out of range";
    throw std::runtime_error(msg);
  }

  if (xhat.maxCoeff() > x.maxCoeff()) {
    std::string msg = "Maximum independent coefficient out of range";
    throw std::runtime_error(msg);
  }

  for (size_t idx = 0; idx < static_cast<size_t>(xhat.size()); idx++) {
    // Binary search for interpolation interval (assumes ascending sort order)
    // Running time classification: O(log2 n)
    size_t low = 0;
    size_t high = x.size() - 1;
    size_t middle;
    while (low <= high) {
      middle = (low + high) / 2;
      if (xhat[idx] > x[middle]) {
        low = middle + 1;
      } else if (xhat[idx] < x[middle]) {
        high = middle - 1;
      } else {
        break;
      }
    }
    if (xhat[idx] < x[middle]) {
      middle = middle - 1;
    }
    if (middle == static_cast<size_t>(x.size() - 1)) {
      yhat[idx] = y[middle];
    } else {
      yhat[idx] = (y[middle + 1] - y[middle]) / (x[middle + 1] - x[middle]) *
                      (xhat[idx] - x[middle]) +
                  y[middle];
    }

    /*
    // Linear search for interpolation interval (no sort order assumption)
    // Running time classification: O(n)
    for (size_t jdx = 0; jdx < static_cast<size_t>(x.size() - 1); jdx++) {
      if (((x[jdx] <= xhat[idx]) && (xhat[idx] <= x[jdx + 1])) ||
          ((x[jdx + 1] <= xhat[idx]) && (xhat[idx] <= x[jdx]))) {
        yhat[idx] = (y[jdx + 1] - y[jdx]) / (x[jdx + 1] - x[jdx]) *
                        (xhat[idx] - x[jdx]) +
                    y[jdx];
        break;
      }
    }
    */
  }

  return yhat;
}
}
