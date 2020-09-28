rit_add_executable(harris_corners
  SOURCES
    harris_corners.cpp
)

target_link_libraries(harris_corners
  rit::ipcv_corners
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
