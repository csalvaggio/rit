#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include "imgs/statistics/data_readers/DataReaders.h"
#include "imgs/statistics/classifiers/Classifiers.h"
#include "imgs/statistics/evaluators/Evaluators.h"

int main() {
  std::vector<unsigned char> training_labels =
      statistics::ReadMnistLabels(MNIST_TRAIN_LABELS_FILE);
  std::cout << training_labels.size() << " MNIST training labels read"
            << std::endl;

  std::vector<cv::Mat> training_images =
      statistics::ReadMnistImages(MNIST_TRAIN_IMAGES_FILE);
  std::cout << training_images.size() << " MNIST training images read"
            << std::endl;

  std::vector<unsigned char> test_labels =
      statistics::ReadMnistLabels(MNIST_TEST_LABELS_FILE);
  std::cout << test_labels.size() << " MNIST test labels read" << std::endl;

  std::vector<cv::Mat> test_images =
      statistics::ReadMnistImages(MNIST_TEST_IMAGES_FILE);
  std::cout << test_images.size() << " MNIST test images read" << std::endl;

  int k = 3;
  double p = 2;
  auto predicted_test_labels =
      statistics::Knn(test_images, training_images, training_labels, k, p);

  if (predicted_test_labels.size()) {
    std::cout << std::endl;
    std::cout << "For a k-NN classifier using " << k << " neighbors ";
    std::cout << "and a Minkowski distance of order " << p << std::endl;
    statistics::ConfusionMatrix(test_labels, predicted_test_labels);
  }

  exit(EXIT_SUCCESS);
}
