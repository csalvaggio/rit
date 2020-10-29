rit_add_executable(eigenanalysis
  SOURCES
    eigenanalysis.cpp
)

target_link_libraries(eigenanalysis
  rit::plot 
  Eigen3::Eigen
  opencv_core
)
