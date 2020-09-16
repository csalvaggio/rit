rit_add_executable(list_files
  SOURCES
    list_files.cpp
)

target_link_libraries(list_files
  $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)
