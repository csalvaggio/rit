#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/histogram_enhancement/HistogramEnhancement.h"
#include "imgs/ipcv/utils/Utils.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose = false;
  string src_filename = "";
  string dst_filename = "";
  string enhancement_type = "linear";
  int percentage = 2;
  string tgt_filename = "";

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename")(
      "enhancement-type,e", po::value<string>(&enhancement_type),
      "enhancement type (linear|equalize|match) [default is linear]")(
      "percentage,p", po::value<int>(&percentage),
      "linear histogram percentage [default is 2]")(
      "target-filename,t", po::value<string>(&tgt_filename),
      "target filename for matching");

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

  if (enhancement_type != "linear" && enhancement_type != "equalize" &&
      enhancement_type != "match") {
    cerr << "*** ERROR *** ";
    cerr << "Provided enhancement type is not supported" << endl;
    return EXIT_FAILURE;
  }

  cv::Mat tgt;
  if (enhancement_type == "match") {
    if (tgt_filename.empty()) {
      cerr << "*** ERROR *** ";
      cerr << "A target filename must be provided for histogram matching"
           << endl;
      return EXIT_FAILURE;
    } else {
      if (!boost::filesystem::exists(tgt_filename)) {
        cerr << "*** ERROR *** ";
        cerr << "Provided target file does not exists" << endl;
        return EXIT_FAILURE;
      }
      tgt = cv::imread(tgt_filename, cv::IMREAD_COLOR);
    }
  }

  if (!boost::filesystem::exists(src_filename)) {
    cerr << "*** ERROR *** ";
    cerr << "Provided source file does not exists" << endl;
    return EXIT_FAILURE;
  }

  cv::Mat src = cv::imread(src_filename, cv::IMREAD_COLOR);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Enhancement type: " << enhancement_type << endl;
    if (enhancement_type == "linear") {
      cout << "Percentage: " << percentage << endl;
    }
    if (enhancement_type == "match") {
      cout << "Target filename: " << tgt_filename << endl;
    }
    cout << "Destination filename: " << dst_filename << endl;
  }

  clock_t startTime = clock();

  bool status = false;
  cv::Mat lut;
  if (enhancement_type == "linear") {
    status = ipcv::LinearLut(src, percentage, lut);
  } else if (enhancement_type == "equalize") {
    cv::Mat_<int> h(3, 256);
    h = 1;
    status = ipcv::MatchingLut(src, h, lut);
  } else if (enhancement_type == "match") {
    cv::Mat_<int> h;
    ipcv::Histogram(tgt, h);
    status = ipcv::MatchingLut(src, h, lut);
  }

  cv::Mat dst;
  if (status) {
    ipcv::ApplyLut(src, lut, dst);
  } else {
    cerr << "*** ERROR *** ";
    cerr << "No valid enhancement LUT was generated" << endl;
    return EXIT_FAILURE;
  }

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  if (dst_filename.empty()) {
    cv::imshow(src_filename, src);
    cv::imshow(src_filename + " [Enhanced]", dst);
    cv::waitKey(0);
  } else {
    cv::imwrite(dst_filename, dst);
  }

  return EXIT_SUCCESS;
}
