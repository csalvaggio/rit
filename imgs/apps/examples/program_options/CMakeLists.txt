rit_add_executable(program_options
  SOURCES
    program_options.cpp
)

target_link_libraries(program_options
  Boost::program_options
)
