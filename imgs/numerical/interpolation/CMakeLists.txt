rit_add_library(numerical_interpolation
  SOURCES
    Interp1.cpp
  HEADERS
    Interp1.h
    interpolation.h
)

target_link_libraries(numerical_interpolation
  PUBLIC
    CONAN_PKG::eigen
  PRIVATE
)
