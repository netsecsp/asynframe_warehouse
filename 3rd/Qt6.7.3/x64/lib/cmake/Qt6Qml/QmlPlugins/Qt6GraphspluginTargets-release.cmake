#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Graphsplugin" for configuration "Release"
set_property(TARGET Qt6::Graphsplugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Graphsplugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/qml/QtGraphs/graphsplugin.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::Graphsplugin )
list(APPEND _cmake_import_check_files_for_Qt6::Graphsplugin "${_IMPORT_PREFIX}/qml/QtGraphs/graphsplugin.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
