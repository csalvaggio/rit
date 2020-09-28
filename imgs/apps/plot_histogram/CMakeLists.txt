rit_add_executable(plot_histogram 
  SOURCES
    plot_histogram.cpp
)

target_link_libraries(plot_histogram 
  rit::ipcv_utils 
  rit::plot 
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_imgcodecs
)
