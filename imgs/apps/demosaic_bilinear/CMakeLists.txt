rit_add_executable(demosaic_bilinear 
  SOURCES
    demosaic_bilinear.cpp
)

target_link_libraries(demosaic_bilinear 
  rit::ipcv_demosaicing
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)
