#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/bilateral_filtering/BilateralFilter.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose = false;
  string src_filename = "";
  string dst_filename = "";
  double sigma_distance = 5;
  double sigma_range = 50;
  int filter_radius = -1;

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename")("sigma-distance,d",
                              po::value<double>(&sigma_distance),
                              "distance filter standard deviation")(
      "sigma-range,r", po::value<double>(&sigma_range),
      "range filter standard deviation")(
      "radius,R", po::value<int>(&filter_radius),
      "filter radius (if negative, use twice the standard deviation of the "
      "distance filter) [default is -1]");

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

  ipcv::BorderMode border_mode;
  border_mode = ipcv::BorderMode::REPLICATE;

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Distance filter standard deviation: " << sigma_distance << endl;
    cout << "Range filter standard deviation: " << sigma_range << endl;
    cout << "Filter radius: " << filter_radius << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  cv::Mat dst;

  clock_t startTime = clock();

  ipcv::BilateralFilter(src, dst, sigma_distance, sigma_range, filter_radius,
                        border_mode);

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  if (dst_filename.empty()) {
    cv::imshow(src_filename, src);
    cv::imshow(src_filename + " [Bilateral Filtered]", dst);
    cv::waitKey(0);
  } else {
    cv::imwrite(dst_filename, dst);
  }

  return EXIT_SUCCESS;
}
