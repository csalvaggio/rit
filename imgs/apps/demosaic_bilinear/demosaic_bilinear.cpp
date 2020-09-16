#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/demosaicing/Demosaic.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose = false;
  string src_filename = "";
  string dst_filename = "";
  string pattern = "GBRG";

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename")("pattern,p", po::value<string>(&pattern),
                              "pattern [default is GBRG]");

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

  cv::Mat src = cv::imread(src_filename, cv::IMREAD_UNCHANGED);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Pattern: " << pattern << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  clock_t startTime = clock();

  cv::Mat dst = ipcv::Bilinear(src, pattern);

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  if (dst_filename.empty()) {
    cv::imshow(src_filename, src);
    cv::imshow(src_filename + " [CFA Interpolated]", dst);
    cv::waitKey(0);
  } else {
    cv::imwrite(dst_filename, dst);
  }

  return EXIT_SUCCESS;
}
