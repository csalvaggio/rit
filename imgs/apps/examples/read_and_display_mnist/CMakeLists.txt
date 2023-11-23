rit_add_executable(read_and_display_mnist 
  SOURCES
    read_and_display_mnist.cpp
)

target_link_libraries(read_and_display_mnist 
  rit::statistics_data_readers
  opencv_core
  opencv_highgui
)
