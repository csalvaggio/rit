set(SRCS
)

set(HDRS
  plot.h
)

add_subdirectory(plot2d)
add_subdirectory(plot3d)

rit_add_library(plot SOURCES ${SRCS} HEADERS ${HDRS})

target_link_libraries(plot
  PUBLIC
    rit::gnuplot-iostream
    CONAN_PKG::eigen
    CONAN_PKG::opencv
  PRIVATE
)
