rit_add_executable(plot2d
  SOURCES
    plot2d.cpp
)

target_link_libraries(plot2d
  rit::plot 
  opencv_core
)
