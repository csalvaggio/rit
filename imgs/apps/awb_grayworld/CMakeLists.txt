rit_add_executable(awb_grayworld 
  SOURCES
    awb_grayworld.cpp
)

target_link_libraries(awb_grayworld 
  rit::ipcv_utils
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
