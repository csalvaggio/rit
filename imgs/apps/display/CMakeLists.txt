rit_add_executable(display 
  SOURCES
    display.cpp
)

target_link_libraries(display 
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
)
