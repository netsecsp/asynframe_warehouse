#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::ScxmlQml" for configuration "Release"
set_property(TARGET Qt6::ScxmlQml APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::ScxmlQml PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6ScxmlQml.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6ScxmlQml.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::ScxmlQml )
list(APPEND _cmake_import_check_files_for_Qt6::ScxmlQml "${_IMPORT_PREFIX}/lib/Qt6ScxmlQml.lib" "${_IMPORT_PREFIX}/bin/Qt6ScxmlQml.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
