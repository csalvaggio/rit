rit_add_executable(transform_gcp
  SOURCES
    transform_gcp.cpp
)

target_link_libraries(transform_gcp
  rit::ipcv_geometric_transformation 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
