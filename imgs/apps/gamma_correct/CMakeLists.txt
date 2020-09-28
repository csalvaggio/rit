rit_add_executable(gamma_correct 
  SOURCES
    gamma_correct.cpp
)

target_link_libraries(gamma_correct 
  rit::ipcv_utils
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
