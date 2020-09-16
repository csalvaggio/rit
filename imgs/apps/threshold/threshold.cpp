#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/otsus_threshold/OtsusThreshold.h"
#include "imgs/ipcv/utils/Utils.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose = false;
  string src_filename = "";
  string dst_filename = "";

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename");

  po::positional_options_description positional_options;
  positional_options.add("source-filename", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(options)
                .positional(positional_options)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << "Usage: " << argv[0] << " [options] source-filename" << endl;
    cout << options << endl;
    return EXIT_SUCCESS;
  }

  if (!boost::filesystem::exists(src_filename)) {
    cerr << "Provided source file does not exists" << endl;
    return EXIT_FAILURE;
  }

  cv::Mat src = cv::imread(src_filename, cv::IMREAD_COLOR);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  cv::Vec3b threshold;

  clock_t startTime = clock();

  ipcv::OtsusThreshold(src, threshold);

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  if (verbose) {
    cout << "Threshold values = ";
    cout << threshold << endl;
  }

  cv::Mat lut;
  lut.create(3, 256, CV_8UC1);
  for (int b = 0; b < 3; b++) {
    for (int dc = 0; dc < 256; dc++) {
      lut.at<uint8_t>(b, dc) = (dc <= threshold[b]) ? 0 : 255;
    }
  }

  cv::Mat dst;
  ipcv::ApplyLut(src, lut, dst);

  if (dst_filename.empty()) {
    cv::imshow(src_filename, src);
    cv::imshow(src_filename + " [Thresholded]", dst);
    cv::waitKey(0);
  } else {
    cv::imwrite(dst_filename, dst);
  }

  return EXIT_SUCCESS;
}
