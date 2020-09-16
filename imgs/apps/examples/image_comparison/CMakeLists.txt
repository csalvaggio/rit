rit_add_executable(image_comparison
  SOURCES
    image_comparison.cpp
)

target_link_libraries(image_comparison
  rit::ipcv_utils 
  CONAN_PKG::opencv
)
