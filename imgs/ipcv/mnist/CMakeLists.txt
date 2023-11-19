rit_add_library(ipcv_mnist
  SOURCES
    ReadMnistImages.cpp
    ReadMnistLabels.cpp
  HEADERS
    ReadMnistImages.h
    ReadMnistLabels.h
    Mnist.h
)

target_link_libraries(ipcv_mnist 
  PUBLIC 
    opencv_core
  PRIVATE
)
