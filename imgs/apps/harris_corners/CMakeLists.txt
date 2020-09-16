rit_add_executable(harris_corners
  SOURCES
    harris_corners.cpp
)

target_link_libraries(harris_corners
  rit::ipcv_corners 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
