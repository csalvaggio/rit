#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/corners/Corners.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose = false;
  string src_filename = "";
  float sigma = 1;
  float k = 0.04;

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "sigma,s", po::value<float>(&sigma),
      "standard deviation for blur [default is 1]")(
      "parameter,k", po::value<float>(&k),
      "free parameter for Harris response [default is 0.04]");

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
    cerr << "*** ERROR *** ";
    cerr << "Provided source file does not exists" << endl;
    return EXIT_FAILURE;
  }

  cv::Mat src = cv::imread(src_filename, cv::IMREAD_COLOR);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Sigma: " << sigma << endl;
    cout << "k: " << k << endl;
  }

  clock_t startTime = clock();

  bool status = false;
  cv::Mat dst;
  status = ipcv::Harris(src, dst, sigma, k);

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  if (status) {
    cv::imshow(src_filename, src);
    cv::imshow(src_filename + " [Corners]", dst);
    cv::waitKey(0);

    // Find the corner coordinates using the returned corner response image

  } else {
    cerr << "*** ERROR *** ";
    cerr << "An error occurred while computing corners" << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
