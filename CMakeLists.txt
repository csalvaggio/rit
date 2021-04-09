cmake_minimum_required(VERSION 3.1)

project(rit VERSION 0.0.0)

include(GNUInstallDirs)

include(cmake/CMakeUtils.cmake)

rit_set_library_prefix("librit_")

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS KEEP_RPATHS)
  rit_add_conan_alias(CONAN_TARGET boost NAMESPACE Boost ALIAS program_options)
  rit_add_conan_alias(CONAN_TARGET boost NAMESPACE Boost ALIAS iostreams)
  rit_add_conan_alias(CONAN_TARGET boost NAMESPACE Boost ALIAS filesystem)
  rit_add_conan_alias(CONAN_TARGET boost NAMESPACE Boost ALIAS system)
  rit_add_conan_alias(CONAN_TARGET opencv ALIAS opencv_core)
  rit_add_conan_alias(CONAN_TARGET opencv ALIAS opencv_highgui)
  rit_add_conan_alias(CONAN_TARGET opencv ALIAS opencv_imgcodecs)
  rit_add_conan_alias(CONAN_TARGET opencv ALIAS opencv_imgproc)
  rit_add_conan_alias(CONAN_TARGET opencv ALIAS opencv_videoio)
  rit_add_conan_alias(CONAN_TARGET eigen NAMESPACE Eigen3 ALIAS Eigen)
else()
  find_package(Boost REQUIRED 
    COMPONENTS 
      program_options 
      iostreams 
      filesystem 
      system
  )
  find_package(Eigen3 REQUIRED NO_MODULE)
  find_package(OpenCV REQUIRED)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(Filesystem REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(imgs)
