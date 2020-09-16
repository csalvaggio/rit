#include <iostream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool verbose;
  std::string src_filename;

  po::options_description visible_options("Options");
  visible_options.add_options()
      ("help,h", 
       "display this message")
      ("verbose,v", 
       po::bool_switch(&verbose)->default_value(false), 
       "verbose [default is silent]")
  ;

  po::options_description hidden_options("Hidden Options");
  hidden_options.add_options()
      ("source-filename,i", 
       po::value<std::string>(&src_filename)->default_value(""), 
       "source filename")
  ;

  po::options_description all_options("All Options");
  all_options
      .add(visible_options)
      .add(hidden_options)
  ;

  po::positional_options_description positional_options;
  positional_options.add("source-filename", 1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(all_options)
                .positional(positional_options)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << "Usage: " << argv[0] << " [options] source-filename" << endl;
    cout << visible_options << endl;
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
  }

  cv::imshow(src_filename, src);
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
