rit_add_executable(quantize 
  SOURCES
    quantize.cpp
)

target_link_libraries(quantize 
  rit::ipcv_quantization
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
