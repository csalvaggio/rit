/** Implementation file for producing and displaying a confusion matrix for
 *  a provided set of truth and predicted class labels
 *
 *  \file statistics/evaluators/ConfusionMatrix.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 22 Nov 2023
 */

#include <algorithm>
#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include "imgs/statistics/evaluators/ConfusionMatrix.h"

namespace statistics {

void ConfusionMatrix(const std::vector<unsigned char>& truth_labels,
                     const std::vector<unsigned char>& predicted_labels,
                     const unsigned char ascii_offset_for_labels) {
  // Determine the number of labels in the data set, set it to the maximum label
  // enumeration in either the truth or predicted label vector
  auto it_truth_labels =
      std::max_element(truth_labels.begin(), truth_labels.end());
  auto number_of_truth_labels = *it_truth_labels + 1;
  auto it_predicted_labels =
      std::max_element(predicted_labels.begin(), predicted_labels.end());
  auto number_of_predicted_labels = *it_predicted_labels + 1;

  std::size_t number_of_labels =
      (number_of_truth_labels > number_of_predicted_labels)
          ? number_of_truth_labels
          : number_of_predicted_labels;

  // Compute the confusion matrix
  cv::Mat confusion_matrix =
      cv::Mat::zeros(number_of_labels, number_of_labels, CV_64F);
  for (std::size_t idx = 0; idx < predicted_labels.size(); idx++) {
    confusion_matrix.at<double>(truth_labels[idx], predicted_labels[idx])++;
  }

  // Print the confusion matrix to the standard output

  // Find the field width needed to display the largest count
  double max_count;
  cv::minMaxLoc(confusion_matrix, NULL, &max_count, NULL, NULL);
  auto field_width = static_cast<std::size_t>(std::log10(max_count) + 1) + 1;

  // Print the title
  std::cout << "Confusion Matrix (Truth \\ Predicted):" << std::endl;

  // Print the predicted labels
  for (std::size_t character = 0; character < field_width; character++) {
    std::cout << " ";
  }
  std::cout << "  ";
  for (std::size_t predicted_label_idx = 0;
       predicted_label_idx < number_of_labels; predicted_label_idx++) {
    if (ascii_offset_for_labels == 0) {
      std::cout << std::setw(field_width) << predicted_label_idx;
    } else {
      std::cout << std::setw(field_width)
                << static_cast<unsigned char>(predicted_label_idx +
                                              ascii_offset_for_labels);
    }
  }
  std::cout << std::endl;

  // Print a separating horizontal line the width of the table
  for (std::size_t character = 0; character < field_width; character++) {
    std::cout << " ";
  }
  std::cout << "  ";
  for (std::size_t label_idx = 0; label_idx < number_of_labels; label_idx++) {
    for (std::size_t character = 0; character < field_width; character++) {
      std::cout << "-";
    }
  }
  std::cout << std::endl;

  // Print the truth label, a vertical separating line, and the number of
  // values predicted to represent the current truth value
  for (std::size_t truth_label_idx = 0; truth_label_idx < number_of_labels;
       truth_label_idx++) {
    if (ascii_offset_for_labels == 0) {
      std::cout << std::setw(field_width) << truth_label_idx << " |";
    } else {
      std::cout << std::setw(field_width)
                << static_cast<unsigned char>(truth_label_idx +
                                              ascii_offset_for_labels)
                << " |";
    }
    for (std::size_t predicted_label_idx = 0;
         predicted_label_idx < number_of_labels; predicted_label_idx++) {
      std::cout << std::setw(field_width);
      std::cout << confusion_matrix.at<double>(truth_label_idx,
                                               predicted_label_idx);
    }
    std::cout << std::endl;
  }

  // Compute and display the classification accuracy
  double correct = cv::trace(confusion_matrix)[0];
  double total = cv::sum(confusion_matrix)[0];
  double classification_accuracy = correct / total * 100;
  std::cout << "Classification accuracy = " << classification_accuracy << "%"
            << std::endl;
}
}
