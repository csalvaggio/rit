rit_add_executable(craps
  SOURCES
    craps.cpp
)

target_link_libraries(craps
  Boost::program_options
)
