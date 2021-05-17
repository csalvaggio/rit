/**
 * Interface file for range creation functions
 *
 * \file  imgs/numerical/range/Range.h
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

#pragma once

#include <vector>

namespace numerical {

/**
 * Function to produce a vector containing ordinal values in the range [a, b]
 *
 * \param[in] a  the lower limit of the ordinal range
 * \param[in] b  the upper limit of the ordinal range
 *
 * \return  a vector containing the requested ordinal range of values
 */
std::vector<int> Range(int a, int b);

/**
 * Function to produce a vector containing n discrete values in the range [a, b]
 *
 * \param[in] a  the lower limit of the ordinal range
 * \param[in] b  the upper limit of the ordinal range
 * \param[in] n  the number of points to include in the vector
 *
 * \return  a vector containing the requested range of values
 */
std::vector<double> Range(double a, double b, std::size_t n);

/**
 * Convenience function to produce a vector containing n ordinal values in the
 * range [0, n - 1]
 *
 * \param[in] n  the number of points to include in the vector
 *
 * \return  a vector containing the requested ordinal range of values
 */
std::vector<int> Range(std::size_t n);

}
