rit_add_executable(test_range 
  SOURCES
    test_range.cpp
)

target_link_libraries(test_range 
  rit::numerical_range 
)
