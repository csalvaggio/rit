rit_add_executable(fast_corners
  SOURCES
    fast_corners.cpp
)

target_link_libraries(fast_corners
  rit::ipcv_corners 
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
