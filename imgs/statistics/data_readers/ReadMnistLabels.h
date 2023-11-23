/** Interface file for reading the MNIST label data.  Either the training
 *  or test data may be read with this function.
 *
 *  \file statistics/data_readers/ReadMnistLabels.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 Nov 2023
 */

#pragma once

#include <string>
#include <vector>

namespace statistics {

/** Read the MNIST labels
 *
 *  \param[in] filename  std::string containing the benchmark distributed
 *                       name of the file containing the label data to be
 *                       ingested
 *  \return              a std::vector of unsigned char(s) containing all
 *                       of the labels in the ingested MNIST data set
 */
std::vector<unsigned char> ReadMnistLabels(const std::string filename);
}
