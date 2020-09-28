rit_add_executable(threshold 
  SOURCES
    threshold.cpp
)

target_link_libraries(threshold 
  rit::ipcv_otsus_threshold 
  rit::ipcv_utils 
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
