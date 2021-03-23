rit_add_library(numerical_range
  SOURCES
    Range.cpp
  HEADERS
    Range.h
)

target_link_libraries(numerical_range
  PUBLIC
    Eigen3::Eigen
  PRIVATE
)
