#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QuickControls2FusionStyleImpl" for configuration "Release"
set_property(TARGET Qt6::QuickControls2FusionStyleImpl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QuickControls2FusionStyleImpl PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6QuickControls2FusionStyleImpl.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Gui;Qt6::Qml;Qt6::Core"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6QuickControls2FusionStyleImpl.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::QuickControls2FusionStyleImpl )
list(APPEND _cmake_import_check_files_for_Qt6::QuickControls2FusionStyleImpl "${_IMPORT_PREFIX}/lib/Qt6QuickControls2FusionStyleImpl.lib" "${_IMPORT_PREFIX}/bin/Qt6QuickControls2FusionStyleImpl.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
