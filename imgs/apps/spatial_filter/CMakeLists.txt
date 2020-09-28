rit_add_executable(spatial_filter 
  SOURCES
    spatial_filter.cpp
)

target_link_libraries(spatial_filter 
  rit::ipcv_spatial_filtering
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
