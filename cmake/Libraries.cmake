# Sets the library prefix cache variable IMGS_LIBRARY_PREFIX
#
# Arguments:
#  PREFIX The new library prefix. Should normally start with lib.
function(rit_set_library_prefix PREFIX)
  set(IMGS_LIBRARY_PREFIX ${PREFIX} CACHE STRING "" FORCE)
endfunction()

# Function for adding a library to the build process.
#
# Arguments:
#   LIB_NAME Name for the library
#   SOURCES  Named parameter for the source files that go into the library
#   HEADERS  Named parameter for the headers that go into the library
function(rit_add_library LIB_NAME)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs SOURCES HEADERS)
  cmake_parse_arguments(rit_add_library "${options}" "${oneValueArgs}"
                                        "${multiValueArgs}" ${ARGN})

  if (NOT DEFINED LIB_NAME)
    message(FATAL_ERROR "rit_add_library(): LIB_NAME not defined")
  endif()

  if (NOT DEFINED PROJECT_VERSION OR PROJECT_VERSION STREQUAL "")
    message(FATAL_ERROR
            "project() must be called with the VERSION option")
  endif()

  add_library(${LIB_NAME} ${rit_add_library_SOURCES} 
                          ${rit_add_library_HEADERS})
  add_library(${CMAKE_PROJECT_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})
  if (IMGS_LIBRARY_PREFIX)
    set_target_properties(${LIB_NAME} PROPERTIES PREFIX ${IMGS_LIBRARY_PREFIX})
  endif()

  set_target_properties(${LIB_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
  )

  target_include_directories(${LIB_NAME}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
      $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
      $<INSTALL_INTERFACE:include>
  )

  if (BUILD_SHARED_LIBS)
    set_target_properties(${LIB_NAME}
      PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )
    target_link_libraries(${LIB_NAME} PRIVATE ${CMAKE_DL_LIBS})
  endif()
endfunction()

# Function for adding a header-only library to the build process.
#
# Arguments:
#   LIB_NAME Name for the target
#   HEADERS  Named parameter for the headers that go into the library
function(rit_add_interface_library LIB_NAME)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs HEADERS)
  cmake_parse_arguments(rit_add_interface_library "${options}" 
                                                  "${oneValueArgs}"
                                                  "${multiValueArgs}" 
                                                  ${ARGN})

  if (NOT DEFINED LIB_NAME)
    message(FATAL_ERROR "rit_add_interface_library(): LIB_NAME not defined")
  endif()

  add_library(${LIB_NAME} INTERFACE)
  add_library(${CMAKE_PROJECT_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})
  target_include_directories(${LIB_NAME}
    INTERFACE
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
      $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
      $<INSTALL_INTERFACE:include>
  )
endfunction()
