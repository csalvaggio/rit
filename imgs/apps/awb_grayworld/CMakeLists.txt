rit_add_executable(awb_grayworld 
  SOURCES
    awb_grayworld.cpp
)

target_link_libraries(awb_grayworld 
  rit::ipcv_utils
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
