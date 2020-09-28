rit_add_library(ipcv_corners
  SOURCES
    Fast.cpp
    Harris.cpp
  HEADERS
    Fast.h
    Harris.h
)

target_link_libraries(ipcv_corners 
  PUBLIC 
    opencv_core
    opencv_imgproc
  PRIVATE
)
