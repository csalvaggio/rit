rit_add_executable(transform_gcp
  SOURCES
    transform_gcp.cpp
)

target_link_libraries(transform_gcp
  rit::ipcv_geometric_transformation 
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
