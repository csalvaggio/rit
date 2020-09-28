rit_add_library(ipcv_histogram_enhancement
  SOURCES
    LinearLut.cpp
    MatchingLut.cpp
  HEADERS
    LinearLut.h
    MatchingLut.h
    HistogramEnhancement.h
)

target_link_libraries(ipcv_histogram_enhancement 
  PUBLIC 
    opencv_core
  PRIVATE
    rit::ipcv_utils
)
