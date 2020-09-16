rit_add_library(ipcv_key_encryption
  SOURCES
    KeyEncryption.cpp
  HEADERS
    KeyEncryption.h
)

target_link_libraries(ipcv_key_encryption 
  PUBLIC 
  PRIVATE
)
