rit_add_executable(read_and_display_ritcis 
  SOURCES
    read_and_display_ritcis.cpp
)

target_link_libraries(read_and_display_ritcis 
  rit::statistics_data_readers
  opencv_core
  opencv_highgui
)
