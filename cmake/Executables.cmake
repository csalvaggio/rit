# Function for adding an executable to the build process.
#
# Arguments:
#   EXE_NAME Name for the executable
#   SOURCES Named parameter for the source files that go into the executable
function(rit_add_executable EXE_NAME)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs SOURCES)
  cmake_parse_arguments(rit_add_executable "${options}" "${oneValueArgs}"
                                           "${multiValueArgs}" ${ARGN})

  if (NOT DEFINED EXE_NAME)
    message(FATAL_ERROR "rit_add_executable(): EXE_NAME not defined")
  endif()

  add_executable(${EXE_NAME} ${rit_add_executable_SOURCES})
  set_target_properties(${EXE_NAME}
    PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
  )

  target_include_directories(${EXE_NAME}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
      $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
  )
endfunction()
