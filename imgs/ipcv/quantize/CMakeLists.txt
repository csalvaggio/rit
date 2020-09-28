rit_add_library(ipcv_quantization
  SOURCES
    Quantize.cpp
  HEADERS
    Quantize.h
)

target_link_libraries(ipcv_quantization 
  PUBLIC 
    opencv_core
  PRIVATE
)
