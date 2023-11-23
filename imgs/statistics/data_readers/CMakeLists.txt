rit_add_library(statistics_data_readers
  SOURCES
    ReadMnistImages.cpp
    ReadMnistLabels.cpp
  HEADERS
    ReadMnistImages.h
    ReadMnistLabels.h
    Mnist.h
)

target_link_libraries(statistics_data_readers
  PUBLIC 
    opencv_core
  PRIVATE
)
