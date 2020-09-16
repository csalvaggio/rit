rit_add_executable(diana
  SOURCES
    diana.cpp
)

target_link_libraries(diana
  CONAN_PKG::boost
)
