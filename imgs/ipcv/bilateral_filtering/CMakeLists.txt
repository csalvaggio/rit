rit_add_library(ipcv_bilateral_filtering
  SOURCES
    BilateralFilter.cpp
  HEADERS
    BilateralFilter.h
)

target_link_libraries(ipcv_bilateral_filtering 
  PUBLIC 
    opencv_core
  PRIVATE
)
