/** Examplar usage of Boost program option
 *
 * \file imgs/apps/examples/program_options/program_options.cpp
 * \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 * \date 7 April 2021
 */

#include <iostream>
#include <string>

#include <boost/program_options.hpp>

using namespace std;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  bool boolean_parameter;
  int integer_parameter;
  std::string string_parameter;

  int value_1;
  double value_2;
  std::string value_3;

  // Implement command-line interface utilizing Boost program options library

  // Instantiate the "visible options" object that defines the program options
  // that are to be visible to the user
  po::options_description visible_options("Options");
  visible_options.add_options()
      ("help,h",
       "display this message")
      ("boolean-parameter,b",
       po::bool_switch(&boolean_parameter)->default_value(false),
       "boolean parameter value "
       "[default is false]")
      ("integer-parameter,i",
       po::value<int>(&integer_parameter)->default_value(1),
       "integer parameter value "
       "[default is 1]")
      ("string-parameter,s",
       po::value<std::string>(&string_parameter)->default_value("hello"),
       "string parameter value "
       "[default is 'hello']")
  ;

  // Instantiate the "hidden options" object that defines the program options
  // that are to be hidden from the user -or- that are to be used as
  // positional arguments
  po::options_description hidden_options("Hidden Options");
  hidden_options.add_options()
      ("value-1,1",
       po::value<int>(&value_1),
       "integer")
      ("value-2,2",
       po::value<double>(&value_2),
       "double")
      ("value-3,3",
       po::value<std::string>(&value_3),
       "string")
  ;

  // Instantiate the "all options" object (combining the "visible options"
  // and "hidden options" objects)
  po::options_description all_options("All Options");
  all_options
      .add(visible_options)
      .add(hidden_options)
  ;

  // Instantiate the "positional options" object, defining the REQUIRED
  // positional command-line parameters that must be provided by the user,
  // in order, as the last elements on the command line (these parameters
  // must also be defined above in the "hidden options" object)
  po::positional_options_description positional_options;
  positional_options.add("value-1", 1);
  positional_options.add("value-2", 1);
  positional_options.add("value-3", 1);

  // Instantiate the Boost program options variable map (command line to 
  // variable mapping definition)
  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(all_options)
                .positional(positional_options)
                .run(),
            vm);
  po::notify(vm);

  // Display usage message to the standard output if the --help or -h
  // optional parameter is specified by the user (positional argument
  // names must be specified here explicitly)
  if (vm.count("help")) {
    cout << "Usage: " << argv[0] << " [options] value-1 value-2 value-3"
         << endl;
    cout << visible_options << endl;
    return EXIT_SUCCESS;
  }

  // Check the 1st required positional parameter
  if (value_1 == 0) {
    cout << "*** value-1 not provided, exiting ... "
         << "(use -h [ --help ] for assitance)" << endl;
    return EXIT_FAILURE;
  }

  // Check the 2nd required positional parameter
  if (value_2 == 0) {
    cout << "*** value-2 not provided, exiting ... "
         << "(use -h [ --help ] for assitance)" << endl;
    return EXIT_FAILURE;
  }

  // Check the 3rd required positional parameter
  if (value_3.length() == 0) {
    cout << "*** value-3 not provided, exiting ... "
         << "(use -h [ --help ] for assitance)" << endl;
    return EXIT_FAILURE;
  }

  // Display the parameters provided to the program
  cout << "Optional Parameters" << endl;
  cout << "  boolean_parameter: " << boolean_parameter << endl;
  cout << "  integer_parameter: " << integer_parameter << endl;
  cout << "  string_parameter: " << string_parameter << endl;
  cout << endl;
  cout << "Postional Parameters" << endl;
  cout << "  value_1 (int): " << value_1 << endl;
  cout << "  value_2 (double): " << value_2 << endl;
  cout << "  value_3 (string): " << value_3 << endl;
}
