#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "blocksci" for configuration "Debug"
set_property(TARGET blocksci APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(blocksci PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libblocksci.so"
  IMPORTED_SONAME_DEBUG "libblocksci.so"
  )

list(APPEND _cmake_import_check_targets blocksci )
list(APPEND _cmake_import_check_files_for_blocksci "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libblocksci.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
