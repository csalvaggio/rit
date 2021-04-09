rit_add_interface_library(utils_file_csvfile
  HEADERS
    CsvFile.h
)

target_link_libraries(utils_file_csvfile
  INTERFACE 
    std::filesystem
)
