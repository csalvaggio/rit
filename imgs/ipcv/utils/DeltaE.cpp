/** Implementation file for computing the delta E between two 3-channel images
 *
 *  \file ipcv/utils/DeltaE.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 04 Jan 2019
 */

#include <iostream>
#include <string>

#include <opencv2/imgproc.hpp>

#include "DeltaE.h"

using namespace std;

namespace ipcv {

double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              const cv::Mat& weights, cv::Mat& dE, int standard,
              std::string application) {
  if ((src1.rows != src2.rows) || (src1.cols != src2.cols) ||
      (src1.channels() != src2.channels())) {
    cerr << "Image dimensions must match exactly for PSNR computation" << endl;
    exit(EXIT_FAILURE);
  }

  if (src1.channels() != 3) {
    cerr << "Images must be 3-channel for delta E computation" << endl;
    exit(EXIT_FAILURE);
  }

  cv::Mat src1_normalized;
  src1.convertTo(src1_normalized, CV_32F, 1.0 / static_cast<float>(max_value));
  cv::Mat src2_normalized;
  src2.convertTo(src2_normalized, CV_32F, 1.0 / static_cast<float>(max_value));

  cv::Mat lab1;
  cv::cvtColor(src1_normalized, lab1, cv::COLOR_BGR2Lab);
  cv::Mat lab2;
  cv::cvtColor(src2_normalized, lab2, cv::COLOR_BGR2Lab);

  double deltae;

  switch (standard) {
    case 1976: {
      // Compute squared differences between L*a*b* for the two source images
      cv::Mat se;
      cv::subtract(lab1, lab2, se);
      cv::multiply(se, se, se);

      // Split into separate L*, a*, and b* squared difference channels
      cv::Mat channels_se[3];
      cv::split(se, channels_se);

      // Compute delta E
      dE = channels_se[0] + channels_se[1] + channels_se[2];
      cv::sqrt(dE, dE);
      break;
    }

    case 1994: {
      dE.create(src1.rows, src1.cols, CV_32F);

      double kL;
      double K1;
      double K2;
      if (application == "graphic_arts") {
        kL = 1.0;
        K1 = 0.045;
        K2 = 0.015;
      } else if (application == "textiles") {
        kL = 2.0;
        K1 = 0.048;
        K2 = 0.014;
      } else {
        cerr << "Specified application for delta E 1994 not supported: "
             << application << endl;
        exit(EXIT_FAILURE);
      }
      double kC = 1.0;
      double kH = 1.0;

      for (int r = 0; r < dE.rows; r++) {
        for (int c = 0; c < dE.cols; c++) {
          const auto& lab1_value = lab1.at<cv::Vec3f>(r, c);
          const auto& lab2_value = lab2.at<cv::Vec3f>(r, c);
          auto& dE_value = dE.at<float>(r, c);

          double Lstar1 = lab1_value[0];
          double astar1 = lab1_value[1];
          double bstar1 = lab1_value[2];

          double Lstar2 = lab2_value[0];
          double astar2 = lab2_value[1];
          double bstar2 = lab2_value[2];

          double deltaLstar = Lstar1 - Lstar2;

          double Cstar1 = sqrt(pow(astar1, 2.0) + pow(bstar1, 2.0));
          double Cstar2 = sqrt(pow(astar2, 2.0) + pow(bstar2, 2.0));
          double deltaCstarab = Cstar1 - Cstar2;

          double deltaastar = astar1 - astar2;
          double deltabstar = bstar1 - bstar2;

          double deltaHstarab =
              sqrt(pow(deltaastar, 2.0) + pow(deltabstar, 2.0) -
                   pow(deltaCstarab, 2.0));

          double SL = 1.0;
          double SC = 1.0 + K1 * Cstar1;
          double SH = 1.0 + K2 * Cstar1;

          dE_value = sqrt(pow(deltaLstar / kL / SL, 2.0) +
                          pow(deltaCstarab / kC / SC, 2.0) +
                          pow(deltaHstarab / kH / SH, 2.0));
        }
      }
      break;
    }

    case 2000: {
      dE.create(src1.rows, src1.cols, CV_32F);

      double tolerance = 1.0e-15;
      const double PI = 3.141592653589793238463;

      double kL = 1.0;
      double kC = 1.0;
      double kH = 1.0;

      for (int r = 0; r < dE.rows; r++) {
        for (int c = 0; c < dE.cols; c++) {
          const auto& lab1_value = lab1.at<cv::Vec3f>(r, c);
          const auto& lab2_value = lab2.at<cv::Vec3f>(r, c);
          auto& dE_value = dE.at<float>(r, c);

          double Lstar1 = lab1_value[0];
          double astar1 = lab1_value[1];
          double bstar1 = lab1_value[2];

          double Lstar2 = lab2_value[0];
          double astar2 = lab2_value[1];
          double bstar2 = lab2_value[2];

          double deltaLprimed = Lstar2 - Lstar1;

          double Lbar = (Lstar1 + Lstar2) / 2.0;

          double Cstar1 = sqrt(pow(astar1, 2.0) + pow(bstar1, 2.0));
          double Cstar2 = sqrt(pow(astar2, 2.0) + pow(bstar2, 2.0));
          double Cbar = (Cstar1 + Cstar2) / 2.0;

          double aprimed1 =
              astar1 +
              astar1 / 2.0 *
                  (1 - sqrt(pow(Cbar, 7.0) / (pow(Cbar, 7.0) + 6103515625)));
          double aprimed2 =
              astar2 +
              astar2 / 2.0 *
                  (1 - sqrt(pow(Cbar, 7.0) / (pow(Cbar, 7.0) + 6103515625)));

          double Cprimed1 = sqrt(aprimed1 * aprimed1 + bstar1 * bstar1);
          double Cprimed2 = sqrt(aprimed2 * aprimed2 + bstar2 * bstar2);
          double deltaCprimed = Cprimed2 - Cprimed1;
          double Cbarprimed = (Cprimed1 + Cprimed2) / 2.0;

          double hprimed1;
          if ((abs(bstar1) < tolerance) && (abs(aprimed1) < tolerance)) {
            hprimed1 = 0;
          } else {
            hprimed1 = atan2(bstar1, aprimed1) * 180 / PI;
            if (hprimed1 < 0) {
              hprimed1 += 360;
            }
          }
          double hprimed2;
          if ((abs(bstar2) < tolerance) && (abs(aprimed2) < tolerance)) {
            hprimed2 = 0;
          } else {
            hprimed2 = atan2(bstar2, aprimed2) * 180 / PI;
            if (hprimed2 < 0) {
              hprimed2 += 360;
            }
          }

          double deltahprimed = 0;
          if ((abs(Cprimed1) < tolerance) || (abs(Cprimed2) < tolerance)) {
            deltahprimed = 0;
          } else {
            double temp = abs(hprimed1 - hprimed2);
            if (temp <= 180) {
              deltahprimed = hprimed2 - hprimed1;
            } else if ((temp > 180) && (hprimed2 <= hprimed1)) {
              deltahprimed = hprimed2 - hprimed1 + 360;
            } else if ((temp > 180) && (hprimed2 > hprimed1)) {
              deltahprimed = hprimed2 - hprimed1 - 360;
            }
          }

          double Hbarprimed = 0;
          if ((abs(Cprimed1) < tolerance) || (abs(Cprimed2) < tolerance)) {
            Hbarprimed = hprimed1 + hprimed2;
          } else {
            double temp = abs(hprimed1 - hprimed2);
            if (temp <= 180) {
              Hbarprimed = (hprimed1 + hprimed2) / 2.0;
            } else if ((temp > 180) && ((hprimed1 + hprimed2) < 360)) {
              Hbarprimed = (hprimed1 + hprimed2 + 360) / 2.0;
            } else if ((temp > 180) && ((hprimed1 + hprimed2) >= 360)) {
              Hbarprimed = (hprimed1 + hprimed2 - 360) / 2.0;
            }
          }

          double deltaHprimed = 2 * sqrt(Cprimed1 * Cprimed2) *
                                sin((deltahprimed / 2) * PI / 180.0);

          double T = 1 - 0.17 * cos((Hbarprimed - 30) * PI / 180.0) +
                     0.24 * cos((2 * Hbarprimed) * PI / 180.0) +
                     0.32 * cos((3 * Hbarprimed + 6) * PI / 180.0) -
                     0.20 * cos((4 * Hbarprimed - 63) * PI / 180.0);

          double SL = 1 + (0.015 * pow(Lbar - 50, 2.0) /
                           sqrt(20 + pow(Lbar - 50, 2.0)));
          double SC = 1 + 0.045 * Cbarprimed;
          double SH = 1 + 0.015 * Cbarprimed * T;

          double RT =
              -2 *
              sqrt(pow(Cbarprimed, 7.0) / (pow(Cbarprimed, 7.0) + 6103515625)) *
              sin((60 * exp(-pow((Hbarprimed - 275) / 25, 2.0))) * PI / 180.0);

          dE_value =
              sqrt(pow(deltaLprimed / kL / SL, 2.0) +
                   pow(deltaCprimed / kC / SC, 2.0) +
                   pow(deltaHprimed / kH / SH, 2.0) +
                   RT * (deltaCprimed / kC / SC) * (deltaHprimed / kH / SH));
        }
      }
      break;
    }

    default:
      cerr << "Specified delta E standard not implemented: " << standard
           << endl;
      exit(EXIT_FAILURE);
  }

  // Weight the delta E map
  cv::Mat weight_map;
  weights.convertTo(weight_map, CV_32F);

  cv::multiply(dE, weight_map, dE);

  // Compute the mean of the weighted delta E map
  cv::Scalar temp = cv::sum(dE) / cv::sum(weight_map);
  deltae = static_cast<double>(temp.val[0]);

  return deltae;
}

double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              const cv::Mat& weights, int standard, std::string application) {
  cv::Mat dE;

  cv::Mat weight_map;
  weights.convertTo(weight_map, CV_32F);

  return DeltaE(src1, src2, max_value, weight_map, dE, standard, application);
}

double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              cv::Mat& dE, int standard, std::string application) {
  cv::Mat weights;
  weights.create(src1.rows, src1.cols, CV_32FC1);
  weights.setTo(cv::Scalar(1));

  return DeltaE(src1, src2, max_value, weights, dE, standard, application);
}

double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              int standard, std::string application) {
  cv::Mat dE;

  cv::Mat weights;
  weights.create(src1.rows, src1.cols, CV_32FC1);
  weights.setTo(cv::Scalar(1));

  return DeltaE(src1, src2, max_value, weights, dE, standard, application);
}
}
