#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QGeoServiceProviderFactoryItemsOverlayPlugin" for configuration "Release"
set_property(TARGET Qt6::QGeoServiceProviderFactoryItemsOverlayPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QGeoServiceProviderFactoryItemsOverlayPlugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/plugins/geoservices/qtgeoservices_itemsoverlay.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::QGeoServiceProviderFactoryItemsOverlayPlugin )
list(APPEND _cmake_import_check_files_for_Qt6::QGeoServiceProviderFactoryItemsOverlayPlugin "${_IMPORT_PREFIX}/plugins/geoservices/qtgeoservices_itemsoverlay.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
