#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::qtquick3dparticleeffectsplugin" for configuration "Release"
set_property(TARGET Qt6::qtquick3dparticleeffectsplugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::qtquick3dparticleeffectsplugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/qml/QtQuick3D/ParticleEffects/qtquick3dparticleeffectsplugin.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::qtquick3dparticleeffectsplugin )
list(APPEND _cmake_import_check_files_for_Qt6::qtquick3dparticleeffectsplugin "${_IMPORT_PREFIX}/qml/QtQuick3D/ParticleEffects/qtquick3dparticleeffectsplugin.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
