rit_add_executable(dist
  SOURCES
    dist.cpp
)

target_link_libraries(dist
  rit::ipcv_utils 
  CONAN_PKG::opencv
)
