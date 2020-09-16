#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string path = "/cis/faculty/cnspci/public_html/courses/common/images/";
  std::string extension = ".tif";

  const auto& directory_entries = std::filesystem::directory_iterator(path);

  std::vector<std::string> files;
  for (const auto& directory_entry : directory_entries) {
    if (directory_entry.path().extension() == extension) {
      files.push_back(directory_entry.path());
    }
  }
  std::sort(files.begin(), files.end());

  for (const auto& file : files) {
    std::cout << file << std::endl;
  }

  return EXIT_SUCCESS;
}
