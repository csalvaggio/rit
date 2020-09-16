rit_add_executable(threshold 
  SOURCES
    threshold.cpp
)

target_link_libraries(threshold 
  rit::ipcv_otsus_threshold 
  rit::ipcv_utils 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
