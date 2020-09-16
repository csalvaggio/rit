rit_add_executable(transform_q2q
  SOURCES
    transform_q2q.cpp
)

target_link_libraries(transform_q2q
  rit::ipcv_geometric_transformation 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
