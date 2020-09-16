rit_add_executable(histogram_enhance
  SOURCES
    histogram_enhance.cpp
)

target_link_libraries(histogram_enhance
  rit::ipcv_histogram_enhancement 
  rit::ipcv_utils 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
