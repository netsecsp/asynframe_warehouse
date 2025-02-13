#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::JsonRpcPrivate" for configuration "Release"
set_property(TARGET Qt6::JsonRpcPrivate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::JsonRpcPrivate PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6JsonRpc.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6JsonRpc.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::JsonRpcPrivate )
list(APPEND _cmake_import_check_files_for_Qt6::JsonRpcPrivate "${_IMPORT_PREFIX}/lib/Qt6JsonRpc.lib" "${_IMPORT_PREFIX}/bin/Qt6JsonRpc.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
