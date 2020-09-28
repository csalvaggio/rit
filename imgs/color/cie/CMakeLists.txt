rit_add_interface_library(color_cie
  HEADERS
    CIE.h
)

target_link_libraries(color_cie
  INTERFACE
    Eigen3::Eigen
)
