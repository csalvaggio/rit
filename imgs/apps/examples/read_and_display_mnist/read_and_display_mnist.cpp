#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include "imgs/ipcv/mnist/Mnist.h"

int main() {
  std::vector<unsigned char> train_labels =
      ipcv::ReadMnistLabels(MNIST_TRAIN_LABELS_FILE);
  std::cout << train_labels.size() << " MNIST train labels read" << std::endl;

  std::vector<cv::Mat> train_images =
      ipcv::ReadMnistImages(MNIST_TRAIN_IMAGES_FILE);
  std::cout << train_images.size() << " MNIST train images read" << std::endl;

  for (size_t i = 0; i < train_images.size(); i++) {
    std::cout << "Label [size]: " << static_cast<int>(train_labels[i]) << " "
              << train_images[i].size() << "\r" << std::flush;

    cv::imshow("Image", train_images[i]);
    int k = cv::waitKey(0);

    // Break on <ESC>
    if (k == 27) {
      std::cout << std::endl;
      break;
    }
  }

  exit(EXIT_SUCCESS);
}
