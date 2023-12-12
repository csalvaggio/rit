/** Interface file for producing and displaying a confusion matrix for
 *  a provided set of truth and predicted class labels
 *
 *  \file statistics/evaluators/ConfusionMatrix.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 10 Dec 2023
 */

#pragma once

#include <vector>

namespace statistics {

/** Perform k-NN classification
 *
 *  \param[in] truth_labels             vector containing the enumerated truth
 *                                      labels
 *  \param[in] predicted_labels         vector containing the enumerated
 *                                      predicted labels
 *  \param[in] ascii_offset_for_labels  additive offset for the label
 *                                      enumerations to allow for proper
 *                                      printing of character data (e.g. 65
 *                                      will allow the label enumeration of 0
 *                                      to be displayed as "A" [default is 0])
 */

void ConfusionMatrix(const std::vector<unsigned char>& truth_labels,
                     const std::vector<unsigned char>& predicted_labels,
                     const unsigned char ascii_offset_for_labels = 0);
}
