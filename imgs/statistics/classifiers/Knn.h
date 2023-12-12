/** Interface file for performing k-NN classification of a set of test
 *  images given a set of training images.
 *
 *  \file statistics/classifiers/Knn.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 22 Nov 2023
 */

#pragma once

#include <vector>

#include <opencv2/opencv.hpp>

namespace statistics {

/** Perform k-NN classification
 *
 *  \param[in] test_images      vector containing the images to be classified
 *  \param[in] training_images  vector containing the images to be used as
 *                              training data
 *  \param[in] training_labels  vector containing the enumerated labels for
 *                              each of the training images
 *  \param[in] k                the number of neighbors to be considered in
 *                              the majority vote for class assignment (the
 *                              "k" in k-NN
 *  \param[in] p                the order to use in the computation of the
 *                              Lp-norm (Minkowski distance) (NOTE: p = 1
 *                              represents the Manhattan distance or L1-norm,
 *                              p = 2 represents the Euclidean distance
 *                              or L2-norm; both of these choices will trigger
 *                              the use of the cv::norm() routine and will
 *                              run significantly faster than any other order)
 *                              [default is 2]
 *  \return                     vector containing the enumerated labels for
 *                              each of the classified test images
 */
std::vector<unsigned char> Knn(
    const std::vector<cv::Mat>& test_images,
    const std::vector<cv::Mat>& training_images,
    const std::vector<unsigned char>& training_labels, const int k,
    const double p = 2);
}
