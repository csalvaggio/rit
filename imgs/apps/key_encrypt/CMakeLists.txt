rit_add_executable(key_encrypt 
  SOURCES
    key_encrypt.cpp
)

target_link_libraries(key_encrypt 
  rit::ipcv_key_encryption
)
