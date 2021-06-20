# CMakeLists.txt for libyui-mga/pkgconfig
#
# Support for pkg-config:
#
# Generate a libyui.pc file from libyui.pc.in and install it to
# /usr/lib64/pkgconfig.
#
# A .pc file specifies how to use a development package, in particular linker
# flags (-lyui-mga), compiler flags (including include directories) and paths.
# See man pkg-config.
#
# Notice that libyui-mga linking is needed for libyui-mga-* plugins 

if ( BUILD_WITH_LIBYUI_SOURCE )
  include( ../../VERSION.cmake )
endif()

include( ../VERSION.cmake )
include( GNUInstallDirs )       # set CMAKE_INSTALL_LIBDIR

if ( NOT BUILD_WITH_LIBYUI_SOURCE )
  FIND_PACKAGE(PkgConfig REQUIRED)

  PKG_CHECK_MODULES(YUI REQUIRED libyui)
  pkg_get_variable(YUI_SO_VERSION libyui soversion)
  pkg_get_variable(YUI_SO_MAJOR libyui soversion_major)
  #pkg_get_variable(YUI_SO_MINOR libyui soversion_minor)
  #pkg_get_variable(YUI_SO_PATCH libyui soversion_patch)

  ##### This is needed to be set for the libyui core
  SET( SONAME_MAJOR ${YUI_SO_MAJOR} )
  SET( SONAME ${YUI_SO_VERSION} )
endif()


set( PKGCONFIG_INSTALL_DIR ${DESTDIR}${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig )

# Generate libyui.pc where some CMake variables are expanded from libyui.pc.in,
# but only expand @VARIABLE@, not ${VARIABLE}
configure_file( libyui-mga.pc.in libyui-mga.pc @ONLY )

install( FILES ${CMAKE_CURRENT_BINARY_DIR}/libyui-mga.pc DESTINATION ${PKGCONFIG_INSTALL_DIR} )
