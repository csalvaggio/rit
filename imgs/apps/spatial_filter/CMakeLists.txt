rit_add_executable(spatial_filter 
  SOURCES
    spatial_filter.cpp
)

target_link_libraries(spatial_filter 
  rit::ipcv_spatial_filtering
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
