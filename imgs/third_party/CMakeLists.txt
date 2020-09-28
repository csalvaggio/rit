rit_add_interface_library(gnuplot-iostream
  HEADERS
    gnupplot-iostream.h
)

target_link_libraries(gnuplot-iostream
  INTERFACE
    Boost::iostreams
    Boost::system
)
