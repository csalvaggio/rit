#include <ctime>
#include <fstream>
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
  string map_filename = "";
  string gcp_filename = "";
  string dst_filename = "";
  int order = 1;
  int value = 0;

  string interpolation_string = "nearest";
  ipcv::Interpolation interpolation;

  string border_mode_string = "constant";
  ipcv::BorderMode border_mode;

  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "map-filename,p", po::value<string>(&map_filename), "map filename")(
      "gcp-filename,g", po::value<string>(&gcp_filename), "gcp filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename [default is empty]")(
      "polynomial-order,n", po::value<int>(&order),
      "order of mapping polynomial [default is 1]")(
      "interpolation,t", po::value<string>(&interpolation_string),
      "interpolation (nearest|bilinear) [default is nearest]")(
      "border-mode,m", po::value<string>(&border_mode_string),
      "border mode (constant|replicate) [default is constant]")(
      "border-value,b", po::value<int>(&value), "border value [default is 0]");

  po::positional_options_description positional_options;
  positional_options.add("source-filename", 1);
  positional_options.add("map-filename", 1);
  positional_options.add("gcp-filename", 1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(options)
                .positional(positional_options)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << "Usage: " << argv[0] << " [options] ";
    cout << "source-filename ";
    cout << "map-filename ";
    cout << "gcp-filename ";
    cout << endl;
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

  if (!boost::filesystem::exists(map_filename)) {
    cerr << "*** ERROR *** ";
    cerr << "Provided map file does not exists" << endl;
    return EXIT_FAILURE;
  }

  if (!boost::filesystem::exists(gcp_filename)) {
    cerr << "*** ERROR *** ";
    cerr << "Provided GCP file does not exists" << endl;
    return EXIT_FAILURE;
  }

  cv::Mat src = cv::imread(src_filename, cv::IMREAD_COLOR);
  cv::Mat map = cv::imread(map_filename, cv::IMREAD_COLOR);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Map filename: " << map_filename << endl;
    cout << "Size: " << map.size() << endl;
    cout << "Channels: " << map.channels() << endl;
    cout << "GCP filename: " << gcp_filename << endl;
    cout << "Order: " << order << endl;
    cout << "Interpolation: " << interpolation_string << endl;
    cout << "Border mode: " << border_mode_string << endl;
    cout << "Border value: " << value << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  uint8_t border_value = value;

  vector<float> sc;
  vector<float> sr;
  vector<float> mc;
  vector<float> mr;

  ifstream f;
  f.open(gcp_filename);
  if (f.is_open()) {
    string buffer;
    getline(f, buffer);
    getline(f, buffer);
    while (!f.eof()) {
      getline(f, buffer);
      if (buffer == "") {
        break;
      }
      size_t size;
      sc.push_back(stof(buffer, &size));
      buffer = buffer.substr(size);
      sr.push_back(stof(buffer, &size));
      buffer = buffer.substr(size);
      mc.push_back(stof(buffer, &size));
      buffer = buffer.substr(size);
      mr.push_back(stof(buffer, &size));
      buffer = buffer.substr(size);
    }
    f.close();
  } else {
    cout << "*** ERROR *** ";
    cerr << "GCP file could not be opened properly" << endl;
    return EXIT_FAILURE;
  }

  vector<cv::Point> src_points(sc.size());
  vector<cv::Point> map_points(mc.size());
  for (size_t point = 0; point < sc.size(); point++) {
    src_points[point].x = sc[point];
    src_points[point].y = sr[point];
    map_points[point].x = mc[point];
    map_points[point].y = mr[point];
  }

  clock_t startTime = clock();

  bool status = false;
  cv::Mat map1;
  cv::Mat map2;
  status = ipcv::MapGCP(src, map, src_points, map_points, order, map1, map2);

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

  cv::Mat overlay;
  cv::addWeighted(map, 0.5, dst, 0.5, 0.0, overlay, map.depth());

  if (status) {
    if (dst_filename.empty()) {
      cv::imshow(src_filename, src);
      cv::imshow(map_filename, map);
      cv::imshow(src_filename + " [Remapped]", dst);
      cv::imshow(src_filename + " [Overlay]", overlay);
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
