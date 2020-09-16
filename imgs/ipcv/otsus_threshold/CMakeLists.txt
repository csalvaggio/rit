rit_add_library(ipcv_otsus_threshold
  SOURCES
    OtsusThreshold.cpp
  HEADERS
    OtsusThreshold.h
)

target_link_libraries(ipcv_otsus_threshold 
  PUBLIC 
    CONAN_PKG::opencv
  PRIVATE
    rit::ipcv_utils
)
