# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindSubunit
# -----------
#
# Find Subunit
#
# Find Subunit headers and libraries.
#
# ::
#
#   SUBUNIT_FOUND          - True if Subunit found.
#   SUBUNIT_INCLUDE_DIRS   - Where to find subunit/child.h.
#   SUBUNIT_LIBRARIES      - List of libraries when using Subunit.
#   SUBUNIT_VERSION_STRING - The version of Subunit found.

# Written by Silvio Clecio
# Fri Jan 19 22:27:51 -03 2018

find_package(PkgConfig QUIET)
pkg_check_modules(PC_SUBUNIT QUIET libsubunit)

set(SUBUNIT_VERSION_STRING "${PC_SUBUNIT_VERSION}")

find_path(SUBUNIT_INCLUDE_DIR
        NAMES child.h
        HINTS ${PC_SUBUNIT_INCLUDEDIR} ${PC_SUBUNIT_INCLUDE_DIRS}
        PATH_SUFFIXES subunit)

find_library(SUBUNIT_LIBRARY
        NAMES subunit libsubunit
        HINTS ${PC_SUBUNIT_LIBDIR} ${PC_SUBUNIT_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Subunit
        REQUIRED_VARS SUBUNIT_LIBRARY SUBUNIT_INCLUDE_DIR
        VERSION_VAR SUBUNIT_VERSION_STRING)

if (SUBUNIT_FOUND)
    set(SUBUNIT_LIBRARIES ${SUBUNIT_LIBRARY})
    set(SUBUNIT_INCLUDE_DIRS ${SUBUNIT_INCLUDE_DIR})
endif ()

mark_as_advanced(SUBUNIT_INCLUDE_DIR SUBUNIT_LIBRARY)