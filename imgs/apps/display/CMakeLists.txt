rit_add_executable(display 
  SOURCES
    display.cpp
)

target_link_libraries(display 
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
