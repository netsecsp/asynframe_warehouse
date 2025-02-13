#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Quick3DParticleEffects" for configuration "Release"
set_property(TARGET Qt6::Quick3DParticleEffects APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Quick3DParticleEffects PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Qt6Quick3DParticleEffects.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Qt6Quick3DParticleEffects.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::Quick3DParticleEffects )
list(APPEND _cmake_import_check_files_for_Qt6::Quick3DParticleEffects "${_IMPORT_PREFIX}/lib/Qt6Quick3DParticleEffects.lib" "${_IMPORT_PREFIX}/bin/Qt6Quick3DParticleEffects.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
