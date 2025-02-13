#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Quick3D" for configuration "Release"
set_property(TARGET Qt6::Quick3D APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Quick3D PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6Quick3D.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6Quick3D.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::Quick3D )
list(APPEND _cmake_import_check_files_for_Qt6::Quick3D "${_IMPORT_PREFIX}/lib/Qt6Quick3D.lib" "${_IMPORT_PREFIX}/bin/Qt6Quick3D.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
