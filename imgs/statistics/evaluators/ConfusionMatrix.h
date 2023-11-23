/** Interface file for producing and displaying a confusion matrix for
 *  a provided set of truth and predicted class labels
 *
 *  \file statistics/evaluators/ConfusionMatrix.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 22 Nov 2023
 */

#pragma once

#include <vector>

namespace statistics {

/** Perform k-NN classification
 *
 *  \param[in] truth_labels      vector containing the enumerated truth labels
 *  \param[in] predicted_labels  vector containing the enumerated predicted
 *                               labels
 */

void ConfusionMatrix(const std::vector<unsigned char>& truth_labels,
                     const std::vector<unsigned char>& predicted_labels);
}
