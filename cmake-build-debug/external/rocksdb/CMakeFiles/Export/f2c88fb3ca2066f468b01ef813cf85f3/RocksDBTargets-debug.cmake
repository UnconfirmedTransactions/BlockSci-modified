#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "RocksDB::rocksdb" for configuration "Debug"
set_property(TARGET RocksDB::rocksdb APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(RocksDB::rocksdb PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/librocksdb.a"
  )

list(APPEND _cmake_import_check_targets RocksDB::rocksdb )
list(APPEND _cmake_import_check_files_for_RocksDB::rocksdb "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/librocksdb.a" )

# Import target "RocksDB::rocksdb-shared" for configuration "Debug"
set_property(TARGET RocksDB::rocksdb-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(RocksDB::rocksdb-shared PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/librocksdb.so.6.6.4"
  IMPORTED_SONAME_DEBUG "librocksdb.so.6"
  )

list(APPEND _cmake_import_check_targets RocksDB::rocksdb-shared )
list(APPEND _cmake_import_check_files_for_RocksDB::rocksdb-shared "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/librocksdb.so.6.6.4" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
