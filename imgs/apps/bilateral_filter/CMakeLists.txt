rit_add_executable(bilateral_filter 
  SOURCES
    bilateral_filter.cpp
)

target_link_libraries(bilateral_filter 
  rit::ipcv_bilateral_filtering
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
