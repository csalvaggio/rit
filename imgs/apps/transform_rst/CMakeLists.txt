rit_add_executable(transform_rst
  SOURCES
    transform_rst.cpp
)

target_link_libraries(transform_rst
  rit::ipcv_geometric_transformation 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
