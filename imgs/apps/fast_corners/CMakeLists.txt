rit_add_executable(fast_corners
  SOURCES
    fast_corners.cpp
)

target_link_libraries(fast_corners
  rit::ipcv_corners 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
