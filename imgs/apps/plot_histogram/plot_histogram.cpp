#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/utils/Utils.h"
#include "imgs/plot/plot.h"

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
      "destination filename (.eps and .png file formats are supported)");

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

  cv::Mat_<int> dc;
  dc = cv::Mat_<int>::zeros(3, 256);
  for (int i = 0; i < 256; i++) {
    dc.at<int>(0, i) = i;
    dc.at<int>(1, i) = i;
    dc.at<int>(2, i) = i;
  }

  cv::Mat_<int> h;
  auto start_time = std::clock();
  ipcv::Histogram(src, h);
  auto end_time = std::clock();
  cout << "Elapsed time to compute histogram: "
       << (end_time - start_time) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s]" << endl;

  cv::Mat_<double> pdf;
  ipcv::HistogramToPdf(h, pdf);

  cv::Mat_<double> cdf;
  ipcv::HistogramToCdf(h, cdf);

  for (int i = 0; i < 256; i++) {
    cout << dc(i) << " ";
    cout << h(i) << " ";
    cout << pdf(i) << " ";
    cout << cdf(i) << " ";
    cout << endl;
  }

  plot::plot2d::Params params;
  params.set_x_label("Digital Count");
  params.set_y_label("Number of Pixels");
  params.set_x_min(0);
  params.set_x_max(255);
  params.set_destination_filename(dst_filename);
  plot::plot2d::Plot2d(dc, h, params);

  return EXIT_SUCCESS;
}
