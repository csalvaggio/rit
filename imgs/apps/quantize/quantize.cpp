#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/quantize/Quantize.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose = false;
  int display_levels = 256;
  int quantization_levels = 8;
  string src_filename = "";
  string dst_filename = "";

  string quantization_type_string = "uniform";
  ipcv::QuantizationType quantization_type;

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename")("quantization-levels,l",
                              po::value<int>(&quantization_levels),
                              "quantization levels [default is 8]")(
      "quantization-type,t", po::value<string>(&quantization_type_string),
      "quantization type (uniform | igs) [default is uniform]")(
      "display-levels,d", po::value<int>(&display_levels),
      "display levels [default is 256]");

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

  if (quantization_type_string == "uniform") {
    quantization_type = ipcv::QuantizationType::uniform;
  } else if (quantization_type_string == "igs") {
    quantization_type = ipcv::QuantizationType::igs;
  } else {
    cerr << "Provided quantization type is not supported" << endl;
    return EXIT_FAILURE;
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
    cout << "Quantization levels: " << quantization_levels << endl;
    cout << "Quantization type: " << quantization_type_string << endl;
    cout << "Destination filename: " << dst_filename << endl;
    cout << "Display levels: " << display_levels << endl;
  }

  cv::Mat dst;

  clock_t startTime = clock();

  ipcv::Quantize(src, quantization_levels, quantization_type, dst);

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  int scale = display_levels / quantization_levels;
  dst *= scale;

  if (dst_filename.empty()) {
    cv::imshow(src_filename, src);
    cv::imshow(src_filename + " [Quantized]", dst);
    cv::waitKey(0);
  } else {
    cv::imwrite(dst_filename, dst);
  }

  return EXIT_SUCCESS;
}
