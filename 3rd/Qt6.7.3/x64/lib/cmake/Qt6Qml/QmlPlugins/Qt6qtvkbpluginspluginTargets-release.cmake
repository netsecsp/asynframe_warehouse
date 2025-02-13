#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::qtvkbpluginsplugin" for configuration "Release"
set_property(TARGET Qt6::qtvkbpluginsplugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::qtvkbpluginsplugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/qml/QtQuick/VirtualKeyboard/Plugins/qtvkbpluginsplugin.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::qtvkbpluginsplugin )
list(APPEND _cmake_import_check_files_for_Qt6::qtvkbpluginsplugin "${_IMPORT_PREFIX}/qml/QtQuick/VirtualKeyboard/Plugins/qtvkbpluginsplugin.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
