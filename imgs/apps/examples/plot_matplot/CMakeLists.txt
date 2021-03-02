rit_add_executable(plot_matplot
  SOURCES
    plot_matplot.cpp
)

target_link_libraries(plot_matplot
  matplot 
  opencv_core
)
