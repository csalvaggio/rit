/** Aggregate interface file for MNIST functions
 *
 *  \file imgs/ipcv/mnist/Mnist.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 Nov 2023
 */

#pragma once

#include "imgs/ipcv/mnist/ReadMnistImages.h"
#include "imgs/ipcv/mnist/ReadMnistLabels.h"

// MNIST data set files relative to the "build" directory
const std::string MNIST_TRAIN_IMAGES_FILE =
    "../data/images/misc/mnist/train-images-idx3-ubyte";
const std::string MNIST_TRAIN_LABELS_FILE =
    "../data/images/misc/mnist/train-labels-idx1-ubyte";
const std::string MNIST_TEST_IMAGES_FILE =
    "../data/images/misc/mnist/t10k-images-idx3-ubyte";
const std::string MNIST_TEST_LABELS_FILE =
    "../data/images/misc/mnist/t10k-labels-idx1-ubyte";
