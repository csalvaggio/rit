rit_add_executable(write_video
  SOURCES
    write_video.cpp
)

target_link_libraries(write_video
  CONAN_PKG::opencv
)
