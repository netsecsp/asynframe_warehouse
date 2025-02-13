#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Grpc" for configuration "Release"
set_property(TARGET Qt6::Grpc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Grpc PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6Grpc.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6Grpc.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::Grpc )
list(APPEND _cmake_import_check_files_for_Qt6::Grpc "${_IMPORT_PREFIX}/lib/Qt6Grpc.lib" "${_IMPORT_PREFIX}/bin/Qt6Grpc.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
