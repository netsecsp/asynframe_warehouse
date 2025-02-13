#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::3DInput" for configuration "Release"
set_property(TARGET Qt6::3DInput APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::3DInput PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt63DInput.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt63DInput.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::3DInput )
list(APPEND _cmake_import_check_files_for_Qt6::3DInput "${_IMPORT_PREFIX}/lib/Qt63DInput.lib" "${_IMPORT_PREFIX}/bin/Qt63DInput.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
