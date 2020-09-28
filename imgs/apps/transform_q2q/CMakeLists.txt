rit_add_executable(transform_q2q
  SOURCES
    transform_q2q.cpp
)

target_link_libraries(transform_q2q
  rit::ipcv_geometric_transformation 
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
