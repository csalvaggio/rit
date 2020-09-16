rit_add_executable(demosaic_bilinear 
  SOURCES
    demosaic_bilinear.cpp
)

target_link_libraries(demosaic_bilinear 
  rit::ipcv_demosaicing
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
