/** Implementation file for reading the MNIST image data.  Either the training
 *  or test data may be read with this function.
 *
 *  \file statistics/data_readers/ReadMnistImages.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 Nov 2023
 */

#include "imgs/statistics/data_readers/ReadMnistImages.h"

#include <iostream>
#include <fstream>

namespace statistics {

std::vector<cv::Mat> ReadMnistImages(const std::string filename) {
  // Open images file
  std::ifstream file(filename, std::ios::binary);

  if (file.is_open()) {
    // Read magic number
    int magic_number = 0;
    file.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
    magic_number = __builtin_bswap32(magic_number);

    // Read number of images
    int number_images = 0;
    file.read(reinterpret_cast<char*>(&number_images), sizeof(number_images));
    number_images = __builtin_bswap32(number_images);

    // Read number of rows in each image
    int number_rows = 0;
    file.read(reinterpret_cast<char*>(&number_rows), sizeof(number_rows));
    number_rows = __builtin_bswap32(number_rows);

    // Read number of columns in each image
    int number_cols = 0;
    file.read(reinterpret_cast<char*>(&number_cols), sizeof(number_cols));
    number_cols = __builtin_bswap32(number_cols);

    // Read images
    std::vector<cv::Mat> images;
    for (int i = 0; i < number_images; ++i) {
      cv::Mat tp = cv::Mat::zeros(number_rows, number_cols, CV_8UC1);
      for (int r = 0; r < number_rows; ++r) {
        for (int c = 0; c < number_cols; ++c) {
          unsigned char temp = 0;
          file.read((char*)&temp, sizeof(temp));
          tp.at<uchar>(r, c) = (int)temp;
        }
      }
      images.push_back(tp);
    }

    // Close images file
    file.close();

    // Return the vector of images
    return (images);
  } else {
    // Report error and terminate if file does not exist or could not be opened
    std::cerr << "Unable to open MNIST images file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}
}
