# Install script for directory: /Users/lminta/Rtv1/gui/KiWi/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/lminta/.brew")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/lminta/Rtv1/gui/build/src/libKiWi.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKiWi.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKiWi.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libKiWi.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKiWi.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKiWi.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/KiWi" TYPE FILE FILES
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_gui.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_button.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_editbox.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_frame.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_label.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_macros.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_tilerenderer.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_widget.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_scrollbox.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_renderdriver_sdl2.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_renderdriver.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_rect.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_bool.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_toggle.h"
    "/Users/lminta/Rtv1/gui/KiWi/src/KW_checkbox.h"
    )
endif()

