rit_add_executable(read_and_display_mnist 
  SOURCES
    read_and_display_mnist.cpp
)

target_link_libraries(read_and_display_mnist 
  rit::ipcv_mnist
  opencv_core
  opencv_highgui
)
