rit_add_executable(interpolate
  SOURCES
    interpolate.cpp
)

target_link_libraries(interpolate 
  rit::numerical_interpolation
)
