#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::WebChannel" for configuration "Release"
set_property(TARGET Qt6::WebChannel APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::WebChannel PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6WebChannel.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6WebChannel.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::WebChannel )
list(APPEND _cmake_import_check_files_for_Qt6::WebChannel "${_IMPORT_PREFIX}/lib/Qt6WebChannel.lib" "${_IMPORT_PREFIX}/bin/Qt6WebChannel.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
