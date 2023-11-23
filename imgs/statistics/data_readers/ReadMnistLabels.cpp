/** Implementation file for reading the MNIST label data.  Either the training
 *  or test data may be read with this function.
 *
 *  \file statistics/data_readers/ReadMnistLabels.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 Nov 2023
 */

#include "imgs/statistics/data_readers/ReadMnistLabels.h"

#include <iostream>
#include <fstream>

namespace statistics {

std::vector<unsigned char> ReadMnistLabels(const std::string filename) {
  // Open labels file
  std::ifstream file(filename, std::ios::binary);

  if (file.is_open()) {
    // Read magic number
    int magic_number = 0;
    file.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
    magic_number = __builtin_bswap32(magic_number);

    // Read number of labels
    int number_labels = 0;
    file.read(reinterpret_cast<char*>(&number_labels), sizeof(number_labels));
    number_labels = __builtin_bswap32(number_labels);

    // Read labels
    std::vector<unsigned char> labels(number_labels);
    file.read(reinterpret_cast<char*>(labels.data()), number_labels);

    // Close labels file
    file.close();

    // Return the vector of labels
    return (labels);
  } else {
    // Report error and terminate if file does not exist or could not be opened
    std::cerr << "Unable to open MNIST labels file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}
}
