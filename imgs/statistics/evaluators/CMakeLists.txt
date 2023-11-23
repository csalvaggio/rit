rit_add_library(statistics_evaluators
  SOURCES
    ConfusionMatrix.cpp
  HEADERS
    ConfusionMatrix.h
)

target_link_libraries(statistics_evaluators
  PUBLIC 
    opencv_core
  PRIVATE
)
