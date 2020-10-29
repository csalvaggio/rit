rit_add_executable(shift_vector
  SOURCES
    shift_vector.cpp
)

target_link_libraries(shift_vector
  rit::utils_shift_vector
  Eigen3::Eigen
)
