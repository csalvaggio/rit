rit_add_executable(classify_ritcis_with_knn 
  SOURCES
    classify_ritcis_with_knn.cpp
)

target_link_libraries(classify_ritcis_with_knn
  rit::statistics_classifiers
  rit::statistics_data_readers
  rit::statistics_evaluators
  opencv_core
  opencv_highgui
)
