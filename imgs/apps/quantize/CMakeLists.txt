rit_add_executable(quantize 
  SOURCES
    quantize.cpp
)

target_link_libraries(quantize 
  rit::ipcv_quantization
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
