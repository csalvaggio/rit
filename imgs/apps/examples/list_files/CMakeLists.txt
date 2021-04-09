rit_add_executable(list_files
  SOURCES
    list_files.cpp
)

target_link_libraries(list_files
  std::filesystem
)
