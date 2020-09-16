rit_add_executable(demosaic_laroche_and_prescott 
  SOURCES
    demosaic_laroche_and_prescott.cpp
)

target_link_libraries(demosaic_laroche_and_prescott 
  rit::ipcv_demosaicing
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
