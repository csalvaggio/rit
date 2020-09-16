#include <algorithm>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

class OneTimePad {
  // Private data members
  size_t key_;
  size_t rows_;
  size_t words_per_row_;
  size_t characters_per_word_;
  string one_time_pad_;

  // Public methods
 public:
  // Constructor
  // key
  //   the seed for the random number generator
  // rows
  //   the number of rows in the one-time pad cryto-table
  // words_per_row
  //   the number of words in each row of the one-time pad crypto-table
  // characters_per_word
  //   the number of characters in each word of the one-time pad crypto-table
  OneTimePad(size_t key, size_t rows, size_t words_per_row,
             size_t characters_per_word) {
    key_ = key;
    rows_ = rows;
    words_per_row_ = words_per_row;
    characters_per_word_ = characters_per_word;

    srand(key_);
    for (size_t i = 0; i < rows_ * words_per_row_ * characters_per_word_; i++) {
      int p_random = rand() % 26;
      char random_character = char(p_random + 65);
      one_time_pad_ += random_character;
    }
  }

  // Destructor
  ~OneTimePad() {}

  // Accessor method to retrieve the random number generator seed
  int key() { return key_; }

  // Accessor method to retrieve the number of rows in the table
  int rows() { return rows_; }

  // Accessor method to retrieve the number of words in each row
  int words_per_row() { return words_per_row_; }

  // Accessor method to retrieve the number of characters in each word
  int characters_per_word() { return characters_per_word_; }

  // Accessor method to retrieve a table value at a specified position
  char at(int idx) {
    // Wrap to the beginning of the table if the specified index is
    // beyond the end of the one-time pad table
    idx %= rows_ * words_per_row_ * characters_per_word_;
    return one_time_pad_[idx];
  }

  // Method to search the table for a specified sequence of characters
  int find(string needle) { return one_time_pad_.find(needle); }

  // Method to extract a sub-string of characters from the table
  string substr(size_t position, size_t length) {
    return one_time_pad_.substr(position, length);
  }

  // A pretty print method for the one-time pad table
  void print() {
    for (size_t i = 0; i < rows_ * words_per_row_ * characters_per_word_; i++) {
      if (i != 0) {
        if (i % (words_per_row_ * characters_per_word_) == 0) {
          cout << endl;
        } else if (i % characters_per_word_ == 0) {
          cout << " ";
        }
      }
      cout << one_time_pad_[i];
    }
    cout << endl;
  }
};

// Method to look up a character from the trigraph given the 2 required
// input characters
char trigraph(char c1, char c2) {
  int p1 = int(c1) - 65;
  int p2 = int(c2) - 65;
  int p3 = (25 - p1 - p2) % 26;
  if (p3 < 0) p3 = 26 + p3;

  return char(p3 + 65);
}

int main(int argc, char* argv[]) {
  // Default command-line parameter values
  bool display_one_time_pad_and_exit = false;
  int key = 10;
  string message;

  // Parse the command-line parameter values
  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "display-one-time-pad,1", po::bool_switch(&display_one_time_pad_and_exit),
      "display one-time pad and exit [default is false]")(
      "key,k", po::value<int>(&key),
      "cypto-key [default is 10] (this should be changed to ensure security)")(
      "message,m", po::value<string>(&message),
      "message to code (including prepended word pair) (quotes are required if "
      "spaces are included)");

  po::positional_options_description positional_options;
  positional_options.add("message", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(options)
                .positional(positional_options)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << "Usage: " << argv[0] << " [options] message" << endl;
    cout << options << endl;
    return EXIT_SUCCESS;
  }

  // Create an instance of the one-time pad object using the random number
  // generator seed and specified number of rows, words per row, and
  // characters per word
  OneTimePad one_time_pad(key, 20, 5, 5);

  // Display the one-time pad if requested and exit
  if (display_one_time_pad_and_exit) {
    one_time_pad.print();
    return EXIT_SUCCESS;
  }

  // Check for a blank message and exit with an informational message if
  // encountered
  if (message.length() == 0) {
    cout << "*** No message provided, exiting ... "
         << "(use -h [ --help ] for assitance)" << endl;
    return EXIT_FAILURE;
  }

  // Echo original message
  cout << "Message: " << message << endl;

  // Strip whitespace from message and force characters to be uppercase
  message.erase(remove_if(message.begin(), message.end(), ::isspace),
                message.end());
  transform(message.begin(), message.end(), message.begin(), ::toupper);
  cout << "Message (stripped/upcased): " << message << endl;

  // Find the provided word pair in the one-time pad
  string one_time_pad_word_pair =
      message.substr(0, 2 * one_time_pad.characters_per_word());
  size_t one_time_pad_word_pair_position =
      one_time_pad.find(one_time_pad_word_pair);
  if (one_time_pad_word_pair_position == string::npos) {
    // If the word pair was not found, set position to 0, this will give
    // the wrong result, however, it will increase security by not reporting
    // an error that a cracking program might key off of
    one_time_pad_word_pair_position = 0;
  }

  // Create the coded message and initialize it with the user-selected
  // word pair
  string coded_message = one_time_pad.substr(one_time_pad_word_pair_position,
                                             one_time_pad_word_pair.length());

  // Set the one-time pad position to the word immediately following the
  // user-selected word pair
  int one_time_pad_character_position =
      one_time_pad_word_pair_position + one_time_pad_word_pair.length();

  // Code the provided message
  for (char message_character :
       message.substr(one_time_pad_word_pair.length(), -1)) {
    char one_time_pad_character =
        one_time_pad.at(one_time_pad_character_position);
    char trigraph_character =
        trigraph(one_time_pad_character, message_character);
    coded_message += trigraph_character;
    one_time_pad_character_position += 1;
  }

  // Display the coded message
  cout << "Coded message: " << coded_message << endl;

  return EXIT_SUCCESS;
}
