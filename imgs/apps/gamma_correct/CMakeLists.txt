rit_add_executable(gamma_correct 
  SOURCES
    gamma_correct.cpp
)

target_link_libraries(gamma_correct 
  rit::ipcv_utils
  CONAN_PKG::boost
  CONAN_PKG::opencv
)
