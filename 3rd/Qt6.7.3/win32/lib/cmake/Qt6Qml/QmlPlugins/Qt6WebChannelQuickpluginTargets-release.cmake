#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::WebChannelQuickplugin" for configuration "Release"
set_property(TARGET Qt6::WebChannelQuickplugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::WebChannelQuickplugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/qml/QtWebChannel/webchannelquickplugin.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::WebChannelQuickplugin )
list(APPEND _cmake_import_check_files_for_Qt6::WebChannelQuickplugin "${_IMPORT_PREFIX}/qml/QtWebChannel/webchannelquickplugin.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
