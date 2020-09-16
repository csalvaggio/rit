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

void MouseCallBack(int event, int x, int y, int flags, void* user_data) {
  auto* vertices = reinterpret_cast<vector<cv::Point>*>(user_data);
  if (event == cv::EVENT_LBUTTONUP) {
    vertices->push_back(cv::Point(x, y));
    cout << "  Vertex #" << vertices->size() << " = (" << x << "," << y << ")"
         << endl;
  }
}

int main(int argc, char* argv[]) {
  bool verbose = false;
  string src_filename = "";
  string tgt_filename = "";
  string dst_filename = "";
  int value = 0;

  string interpolation_string = "nearest";
  ipcv::Interpolation interpolation;

  string border_mode_string = "constant";
  ipcv::BorderMode border_mode;

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "target-filename,T", po::value<string>(&tgt_filename), "target filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename [default is empty]")(
      "interpolation,t", po::value<string>(&interpolation_string),
      "interpolation (nearest|bilinear) [default is nearest]")(
      "border-mode,m", po::value<string>(&border_mode_string),
      "border mode (constant|replicate) [default is constant]")(
      "border-value,b", po::value<int>(&value), "border value [default is 0]");

  po::positional_options_description positional_options;
  positional_options.add("source-filename", 1);
  positional_options.add("target-filename", 1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(options)
                .positional(positional_options)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << "Usage: " << argv[0]
         << " [options] source-filename target-filename " << endl;
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

  if (!boost::filesystem::exists(tgt_filename)) {
    cerr << "*** ERROR *** ";
    cerr << "Provided target file does not exists" << endl;
    return EXIT_FAILURE;
  }

  cv::Mat src = cv::imread(src_filename, cv::IMREAD_COLOR);
  cv::Mat tgt = cv::imread(tgt_filename, cv::IMREAD_COLOR);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Target filename: " << tgt_filename << endl;
    cout << "Size: " << tgt.size() << endl;
    cout << "Channels: " << tgt.channels() << endl;
    cout << "Interpolation: " << interpolation_string << endl;
    cout << "Border mode: " << border_mode_string << endl;
    cout << "Border value: " << value << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  uint8_t border_value = value;

  string window_name = "Composited Image";
  cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

  vector<cv::Point> tgt_vertices;
  cv::setMouseCallback(window_name, MouseCallBack, &tgt_vertices);
  cout << endl;
  cout << "Select vertices of the targeted quadrilateral (CW) ..." << endl;
  while (tgt_vertices.size() < 4) {
    cv::imshow(window_name, tgt);
    cv::waitKey(10);
  }
  cout << "Target quadrilateral selected, performing perspective transform ..."
       << endl;
  cout << endl;

  vector<cv::Point> src_vertices(4);
  src_vertices[0].x = 0;
  src_vertices[0].y = 0;
  src_vertices[1].x = src.cols - 1;
  src_vertices[1].y = 0;
  src_vertices[2].x = src.cols - 1;
  src_vertices[2].y = src.rows - 1;
  src_vertices[3].x = 0;
  src_vertices[3].y = src.rows - 1;

  clock_t startTime = clock();

  bool status = false;
  cv::Mat map1;
  cv::Mat map2;
  status = ipcv::MapQ2Q(src, tgt, src_vertices, tgt_vertices, map1, map2);

  cv::Mat dst;
//  cv::remap(src, dst, map1, map2, cv::INTER_NEAREST, cv::BORDER_CONSTANT,
//            cv::Scalar(0, 0, 0) );
  status = ipcv::Remap(src, dst, map1, map2, interpolation, border_mode,
                       border_value);

  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  cv::Mat mask = 255 - (dst * 255);
  cv::Mat composite = (mask & tgt) + dst;

  if (status) {
    if (dst_filename.empty()) {
      cv::imshow(window_name, composite);
      cv::waitKey(0);
    } else {
      cv::imwrite(dst_filename, composite);
    }
  } else {
    cerr << "*** ERROR *** ";
    cerr << "An error occurred while remapping image" << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
