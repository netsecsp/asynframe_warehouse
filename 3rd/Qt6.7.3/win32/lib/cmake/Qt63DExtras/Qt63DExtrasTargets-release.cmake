#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::3DExtras" for configuration "Release"
set_property(TARGET Qt6::3DExtras APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::3DExtras PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt63DExtras.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt63DExtras.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::3DExtras )
list(APPEND _cmake_import_check_files_for_Qt6::3DExtras "${_IMPORT_PREFIX}/lib/Qt63DExtras.lib" "${_IMPORT_PREFIX}/bin/Qt63DExtras.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
