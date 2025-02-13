#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QuickEffectsPrivate" for configuration "Release"
set_property(TARGET Qt6::QuickEffectsPrivate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QuickEffectsPrivate PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6QuickEffects.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Qml"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6QuickEffects.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::QuickEffectsPrivate )
list(APPEND _cmake_import_check_files_for_Qt6::QuickEffectsPrivate "${_IMPORT_PREFIX}/lib/Qt6QuickEffects.lib" "${_IMPORT_PREFIX}/bin/Qt6QuickEffects.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
