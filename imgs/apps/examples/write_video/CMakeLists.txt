rit_add_executable(write_video
  SOURCES
    write_video.cpp
)

target_link_libraries(write_video
  opencv_core
  opencv_highgui
  opencv_imgcodecs
  opencv_videoio
)
