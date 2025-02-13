#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Coap" for configuration "Release"
set_property(TARGET Qt6::Coap APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Coap PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6Coap.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Network"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6Coap.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::Coap )
list(APPEND _cmake_import_check_files_for_Qt6::Coap "${_IMPORT_PREFIX}/lib/Qt6Coap.lib" "${_IMPORT_PREFIX}/bin/Qt6Coap.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
