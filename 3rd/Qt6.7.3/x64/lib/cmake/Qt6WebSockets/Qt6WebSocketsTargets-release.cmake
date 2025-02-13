#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::WebSockets" for configuration "Release"
set_property(TARGET Qt6::WebSockets APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::WebSockets PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6WebSockets.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6WebSockets.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::WebSockets )
list(APPEND _cmake_import_check_files_for_Qt6::WebSockets "${_IMPORT_PREFIX}/lib/Qt6WebSockets.lib" "${_IMPORT_PREFIX}/bin/Qt6WebSockets.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
