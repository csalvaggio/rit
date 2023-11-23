/** Interface file for reading the MNIST image data.  Either the training
 *  or test data may be read with this function.
 *
 *  \file statistics/data_readers/ReadMnistImages.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 Nov 2023
 */

#pragma once

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

namespace statistics {

/** Read the MNIST images
 *
 *  \param[in] filename  std::string containing the benchmark distributed
 *                       name of the file containing the image data to be
 *                       ingested
 *  \return              a std::vector of cv::Mat(s) containing all of the
 *                       images in the ingested MNIST data set
 */
std::vector<cv::Mat> ReadMnistImages(const std::string filename);
}
