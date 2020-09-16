/** Interface file for linear interpolation of one-dimensional data
 *
 *  \file numerical/interpolation/Interp1.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 21 February 2020
 */

#pragma once

#include <Eigen/Dense>

namespace numerical {

/** Perform linear interpolation of provided (x,y) data at provided locations
 *
 *  \param[in] xhat
 *      independent variable vector of type Eigen::VectorXd containing
 *      the values at which to interpolate
 *  \param[in] x
 *      independent variable vector of type Eigen::VectorXd
 *  \param[in] y
 *      dependent variable vector of type Eigen::VectorXd
 *
 *  \return
 *      interpolated dependent values (y-hat) at the provided independent
 *      values (x-hat) contained in a vector of type Eigen::VectorXd
 */
Eigen::VectorXd Interp1(const Eigen::VectorXd& xhat, const Eigen::VectorXd& x,
                        const Eigen::VectorXd& y);
}
