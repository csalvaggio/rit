rit_add_library(statistics_classifiers
  SOURCES
    Knn.cpp
  HEADERS
    Knn.h
)

target_link_libraries(statistics_classifiers
  PUBLIC 
    opencv_core
  PRIVATE
)
