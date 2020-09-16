cmake_minimum_required(VERSION 3.1)

project(rit VERSION 0.0.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS KEEP_RPATHS)

include(GNUInstallDirs)

include(cmake/CMakeUtils.cmake)

rit_set_library_prefix("librit_")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(imgs)
