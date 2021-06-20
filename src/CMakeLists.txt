# CMakeLists.txt for libyui-mga/src

if ( BUILD_WITH_LIBYUI_SOURCE )
  include( ../../VERSION.cmake )
endif()

include( ../VERSION.cmake )
include( GNUInstallDirs )       # set CMAKE_INSTALL_INCLUDEDIR, ..._LIBDIR

if ( BUILD_WITH_LIBYUI_SOURCE )
  set( YUI_LIBRARY_DIRS ../../libyui/build/src )
  set( YUI_LIBRARIES yui )
else()
  FIND_PACKAGE(PkgConfig REQUIRED)

  PKG_CHECK_MODULES(YUI REQUIRED libyui)
  pkg_get_variable(YUI_SO_VERSION libyui soversion)
  pkg_get_variable(YUI_SO_MAJOR libyui soversion_major)
  #pkg_get_variable(YUI_SO_MINOR libyui soversion_minor)
  #pkg_get_variable(YUI_SO_PATCH libyui soversion_patch)

  message (STATUS "Using ${YUI_LIBRARY_DIRS}/libyui.so.${YUI_SO_VERSION}")

  ##### This is needed to be set for the libyui core
  SET( SONAME_MAJOR ${YUI_SO_MAJOR} )
  SET( SONAME ${YUI_SO_VERSION} )
endif()

set( TARGETLIB          libyui-mga )
set( TARGETLIB_BASE     yui-mga    )

set( HEADERS_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/yui/mga )

# if DESTDIR is set, CMAKE_INSTALL_INCLUDEDIR already contains it
# during "make install" (but not for other make targets!):
#
#    sudo make install DESTDIR=/work/foo
#
# -> the include files are installed to /work/foo/usr/include/...
# We need that for RPM builds to install everything to $RPM_BUILD_ROOT.


set( SOURCES
  YMGAMenuBar.cc
  YMGA_CBTable.cc
  YMGAAboutDialog.cc
  YMGAMsgBox.cc
  YMGAWidgetExtensionFactory.cc
)


set( HEADERS
  YMGAMenuItem.h
  YMGAMenuBar.h
  YMGA_CBTable.h
  YMGAAboutDialog.h
  YMGAMsgBox.h
  YMGAWidgetExtensionFactory.h
)


# Add shared lib to be built
add_library( ${TARGETLIB} SHARED ${SOURCES} ${HEADERS} )


#
# Include directories and compile options
#
if ( BUILD_WITH_LIBYUI_SOURCE )
  set( LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include )

  # Symlink ../../libyui/src to build/src/include/yui
  # so the headers there can be included as <yui/YFoo.h>
  file( MAKE_DIRECTORY ${LOCAL_INCLUDE_DIR} )
  file( CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/../../libyui/src ${LOCAL_INCLUDE_DIR}/yui SYMBOLIC )

  target_include_directories( ${TARGETLIB} BEFORE PUBLIC ${LOCAL_INCLUDE_DIR} )
else ()
  target_include_directories( ${TARGETLIB}
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
    PUBLIC ${YUI_INCLUDE_DIRS}
  )
endif()

# Add more compile options to this target in addition to those
# added in the toplevel CMakeLists.txt.
#
# Notice that CMake will automatically add -fPIC etc. where needed,
# like for this shared lib.
### target_compile_options( ${TARGETLIB} PUBLIC "-Dfoo" )

# Show the complete compiler commands with all arguments:
#   make VERBOSE=1

# Add more compile options to an individual source file:
### set_source_files_properties( YUI.cc PROPERTIES COMPILE_OPTIONS "-Dfoo" )


#
# Linking
#
# https://cmake.org/cmake/help/latest/command/link_directories.html suggests to use target_link_libraries
# and anyway LINK_DIRECTORIES command will apply only to targets created after it is called, so must be set
# before add_library in the case.
if ( BUILD_WITH_LIBYUI_SOURCE )
  # Find yui during a combined build
  target_link_directories( ${TARGETLIB}
    BEFORE PUBLIC ${YUI_LIBRARY_DIRS}
  )
else()
  target_link_directories( ${TARGETLIB}
    PUBLIC ${YUI_LIBRARY_DIRS}
  )
endif()


# Libraries that are needed to build this shared lib
#
# We only use the parts of Boost that are completely contained in header files
# without any binary part, so we don't need to link against any Boost lib.
# Should that become necessary, add Boost::filesystem or whatever lib is
# needed. See also
# https://cliutils.gitlab.io/modern-cmake/chapters/packages/Boost.html
#
# If in doubt what is really needed, check with "ldd -u" which libs are unused.
target_link_libraries( ${TARGETLIB}
  ${YUI_LIBRARIES}
  dl
  pthread
  )


# https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties
set_target_properties( ${TARGETLIB} PROPERTIES
  VERSION       ${SONAME}           # From ../../VERSION.cmake
  SOVERSION     ${SONAME_MAJOR}     # From ../../VERSION.cmake
  OUTPUT_NAME   ${TARGETLIB_BASE}
  )


#
# Install
#

# Install the headers first so the message about the lib does not scroll away
install( FILES   ${HEADERS}   DESTINATION ${HEADERS_INSTALL_DIR} )
install( TARGETS ${TARGETLIB} LIBRARY )
