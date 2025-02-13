#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::VirtualKeyboardSettings" for configuration "Release"
set_property(TARGET Qt6::VirtualKeyboardSettings APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::VirtualKeyboardSettings PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6VirtualKeyboardSettings.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Core;Qt6::Gui;Qt6::Qml;Qt6::Quick"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6VirtualKeyboardSettings.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::VirtualKeyboardSettings )
list(APPEND _cmake_import_check_files_for_Qt6::VirtualKeyboardSettings "${_IMPORT_PREFIX}/lib/Qt6VirtualKeyboardSettings.lib" "${_IMPORT_PREFIX}/bin/Qt6VirtualKeyboardSettings.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
