#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::3DLogic" for configuration "Release"
set_property(TARGET Qt6::3DLogic APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::3DLogic PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt63DLogic.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt63DLogic.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::3DLogic )
list(APPEND _cmake_import_check_files_for_Qt6::3DLogic "${_IMPORT_PREFIX}/lib/Qt63DLogic.lib" "${_IMPORT_PREFIX}/bin/Qt63DLogic.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
