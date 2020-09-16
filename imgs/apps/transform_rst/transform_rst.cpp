#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>

#include "imgs/ipcv/geometric_transformation/GeometricTransformation.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose = false;
  string src_filename = "";
  string dst_filename = "";
  double angle = 0;
  double scale_x = 1;
  double scale_y = 1;
  double translation_x = 0;
  double translation_y = 0;
  int value = 0;

  string interpolation_string = "nearest";
  ipcv::Interpolation interpolation;

  string border_mode_string = "constant";
  ipcv::BorderMode border_mode;

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename [default is empty]")(
      "rotation,r", po::value<double>(&angle),
      "rotation angle (CCW) [deg] [default is 0]")(
      "scale-x,x", po::value<double>(&scale_x),
      "horizontal (x) scale [default is 1]")(
      "scale-y,y", po::value<double>(&scale_y),
      "vertical (y) scale [default is 1]")(
      "translation-x,H", po::value<double>(&translation_x),
      "horizontal (x) translation [default is 0]")(
      "translation-y,V", po::value<double>(&translation_y),
      "vertical (y) translation [default is 0]")(
      "interpolation,t", po::value<string>(&interpolation_string),
      "interpolation (nearest|bilinear) [default is nearest]")(
      "border-mode,m", po::value<string>(&border_mode_string),
      "border mode (constant|replicate) [default is constant]")(
      "border-value,b", po::value<int>(&value), "border value [default is 0]");

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

  if (interpolation_string == "nearest") {
    interpolation = ipcv::Interpolation::NEAREST;
  } else if (interpolation_string == "bilinear") {
    interpolation = ipcv::Interpolation::LINEAR;
  } else {
    cerr << "*** ERROR *** ";
    cerr << "Provided interpolation is not supported" << endl;
    return EXIT_FAILURE;
  }

  if (border_mode_string == "constant") {
    border_mode = ipcv::BorderMode::CONSTANT;
  } else if (border_mode_string == "replicate") {
    border_mode = ipcv::BorderMode::REPLICATE;
  } else {
    cerr << "*** ERROR *** ";
    cerr << "Provided border mode is not supported" << endl;
    return EXIT_FAILURE;
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
    cout << "Rotation: " << angle << " [deg] (CCW)" << endl;
    cout << "Scale X: " << scale_x << endl;
    cout << "Scale Y: " << scale_y << endl;
    cout << "Translation X: " << translation_x << endl;
    cout << "Translation Y: " << translation_y << endl;
    cout << "Interpolation: " << interpolation_string << endl;
    cout << "Border mode: " << border_mode_string << endl;
    cout << "Border value: " << value << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  double radians_per_degree = 3.14159265358979 / 180.0;
  angle *= radians_per_degree;

  uint8_t border_value = value;

  clock_t startTime = clock();

  bool status = false;
  cv::Mat map1;
  cv::Mat map2;
  status = ipcv::MapRST(src, angle, scale_x, scale_y, translation_x,
                        translation_y, map1, map2);

  cv::Mat dst;
//  cv::remap(src, dst, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT,
//            cv::Scalar(0, 0, 0) );
  status = ipcv::Remap(src, dst, map1, map2, interpolation, border_mode,
                       border_value);

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  if (status) {
    if (dst_filename.empty()) {
      cv::imshow(src_filename, src);
      cv::imshow(src_filename + " [RST]", dst);
      cv::waitKey(0);
    } else {
      cv::imwrite(dst_filename, dst);
    }
  } else {
    cerr << "*** ERROR *** ";
    cerr << "An error occurred while remapping image" << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
