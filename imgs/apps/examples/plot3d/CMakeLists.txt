rit_add_executable(plot3d
  SOURCES
    plot3d.cpp
)

target_link_libraries(plot3d
  rit::ipcv_utils 
  rit::plot 
  opencv_core
)
