#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KiWi" for configuration ""
set_property(TARGET KiWi APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KiWi PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "/Users/lminta/Library/Frameworks/SDL2.framework;-framework Cocoa;/Users/lminta/Library/Frameworks/SDL2_ttf.framework;/Users/lminta/Library/Frameworks/SDL2_image.framework"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKiWi.dylib"
  IMPORTED_SONAME_NOCONFIG "libKiWi.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS KiWi )
list(APPEND _IMPORT_CHECK_FILES_FOR_KiWi "${_IMPORT_PREFIX}/lib/libKiWi.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
