#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::BodymovinPrivate" for configuration "Release"
set_property(TARGET Qt6::BodymovinPrivate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::BodymovinPrivate PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6Bodymovin.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6Bodymovin.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::BodymovinPrivate )
list(APPEND _cmake_import_check_files_for_Qt6::BodymovinPrivate "${_IMPORT_PREFIX}/lib/Qt6Bodymovin.lib" "${_IMPORT_PREFIX}/bin/Qt6Bodymovin.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
