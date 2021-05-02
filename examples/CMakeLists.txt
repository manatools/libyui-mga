# CMakeLists.txt for libyui-mga/examples

include( ../VERSION.cmake )
include( GNUInstallDirs )       # set CMAKE_INSTALL_INCLUDEDIR, ..._LIBDIR

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)

PKG_CHECK_MODULES(YUI REQUIRED libyui)
pkg_get_variable(YUI_SO_VERSION libyui soversion)
pkg_get_variable(YUI_SO_MAJOR libyui soversion_major)

##### This is needed to be set for the libyui core
SET( SONAME_MAJOR ${YUI_SO_MAJOR} )
SET( SONAME ${YUI_SO_VERSION} )

set( PKG_NAME                   libyui-mga${SONAME_MAJOR} )
set( EXAMPLES_INSTALL_DIR       ${DESTDIR}${CMAKE_INSTALL_PREFIX}/share/doc/packages/${PKG_NAME}/examples )

set( USE_FRESHLY_BUILT_LIBYUI   on )

if ( USE_FRESHLY_BUILT_LIBYUI )
  # Use the freshly built libyui from ../build/src, not the system libyui from
  # /usr/lib64; also set rpath.
  #
  # FIXME: This will still load the UI plug-ins from the system, not the
  # freshly built ones.
  set( LIBYUIMGA ${CMAKE_BINARY_DIR}/src/libyui-mga.so )
else()
  # Link against the system libyui in /usr/lib64. No rpath.
  set( LIBYUIMGA yui-mga )
endif()


set( LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include )

# Symlink ../../libyui/src to build/src/include/yui
# so the headers there can be included as <yui/YFoo.h>
file( MAKE_DIRECTORY ${LOCAL_INCLUDE_DIR}/yui )
file( CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/../src ${LOCAL_INCLUDE_DIR}/yui/mga SYMBOLIC )


# Build a simple example named EXAMPLE from one source file EXAMPLE.cc
# and install the source to the package's doc directory
#
function( add_example EXAMPLE )
  add_executable( ${EXAMPLE} ${EXAMPLE}.cc )
  target_link_directories( ${EXAMPLE}
    PUBLIC ${YUI_LIBRARY_DIRS}
  )
  target_link_libraries( ${EXAMPLE} ${LIBYUIMGA} ${YUI_LIBRARIES} )

  if ( USE_FRESHLY_BUILT_LIBYUI )
    # Prefer the headers in ../src over those in /usr/include
    target_include_directories( ${EXAMPLE}
      BEFORE PUBLIC ${LOCAL_INCLUDE_DIR}
      PUBLIC ${YUI_INCLUDE_DIRS}
    )
  endif()

  install( FILES ${EXAMPLE}.cc DESTINATION ${EXAMPLES_INSTALL_DIR} )
endfunction()

#----------------------------------------------------------------------

add_example( AboutDialog )
add_example( YCBTable )
add_example( MsgBoxDialog )
add_example( ManyWidgets )
add_example( MenuBar )
