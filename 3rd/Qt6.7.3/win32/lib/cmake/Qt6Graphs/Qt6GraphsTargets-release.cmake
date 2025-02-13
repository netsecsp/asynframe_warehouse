#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Graphs" for configuration "Release"
set_property(TARGET Qt6::Graphs APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Graphs PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6Graphs.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::QuickShapesPrivate;Qt6::Qml"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6Graphs.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::Graphs )
list(APPEND _cmake_import_check_files_for_Qt6::Graphs "${_IMPORT_PREFIX}/lib/Qt6Graphs.lib" "${_IMPORT_PREFIX}/bin/Qt6Graphs.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
