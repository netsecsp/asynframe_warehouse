#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::3DQuick" for configuration "Release"
set_property(TARGET Qt6::3DQuick APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::3DQuick PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt63DQuick.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt63DQuick.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::3DQuick )
list(APPEND _cmake_import_check_files_for_Qt6::3DQuick "${_IMPORT_PREFIX}/lib/Qt63DQuick.lib" "${_IMPORT_PREFIX}/bin/Qt63DQuick.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
