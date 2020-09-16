# Configure the compiler options
# ------------------------------

include_guard(GLOBAL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Enable the compiler cache
if (NOT WIN32)
  find_program(CCACHE_FOUND ccache)
  if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
  endif()
endif()

# If we are using ninja or make, we still want colors
if (NOT WIN32)
  if (CMAKE_GENERATOR STREQUAL "Ninja" OR
      CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
  endif()
endif()
