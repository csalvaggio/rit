rit_add_library(ipcv_demosaicing
  SOURCES
    Bilinear.cpp
    LarochePrescott.cpp
  HEADERS
    Bilinear.h
    LarochePrescott.h
    Demosaic.h
)

target_link_libraries(ipcv_demosaicing
  PUBLIC 
    CONAN_PKG::opencv
  PRIVATE
)
