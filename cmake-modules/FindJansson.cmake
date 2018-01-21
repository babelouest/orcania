#TODO: FIXME! please attach a license here!

#.rst:
# FindJansson
# -----------
#
# Find Jansson
#
# Find Jansson headers and libraries.
#
# ::
#
#   JANSSON_FOUND          - True if Jansson found.
#   JANSSON_INCLUDE_DIRS   - Where to find jansson.h.
#   JANSSON_LIBRARIES      - List of libraries when using Jansson.
#   JANSSON_VERSION_STRING - The version of Jansson found.

# Written by Silvio Clecio
# Sat Jan 20 12:32:26 -03 2018

find_package(PkgConfig QUIET)
pkg_check_modules(PC_JANSSON QUIET jansson)

find_path(JANSSON_INCLUDE_DIR
        NAMES jansson.h
        HINTS ${PC_JANSSON_INCLUDEDIR} ${PC_JANSSON_INCLUDE_DIRS})

find_library(JANSSON_LIBRARY
        NAMES jansson libjansson
        HINTS ${PC_JANSSON_LIBDIR} ${PC_JANSSON_LIBRARY_DIRS})

if (PC_JANSSON_VERSION)
    set(JANSSON_VERSION_STRING ${PC_JANSSON_VERSION})
elseif (JANSSON_INCLUDE_DIR AND EXISTS "${JANSSON_INCLUDE_DIR}/jansson.h")
    set(regex_jansson_version "^#define[ \t]+JANSSON_VERSION[ \t]+\"([^\"]+)\".*")
    file(STRINGS "${JANSSON_INCLUDE_DIR}/jansson.h" jansson_version REGEX "${regex_jansson_version}")
    string(REGEX REPLACE "${regex_jansson_version}" "\\1" JANSSON_VERSION_STRING "${jansson_version}")
    unset(regex_jansson_version)
    unset(jansson_version)
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Jansson
        REQUIRED_VARS JANSSON_LIBRARY JANSSON_INCLUDE_DIR
        VERSION_VAR JANSSON_VERSION_STRING)

if (JANSSON_FOUND)
    set(JANSSON_LIBRARIES ${JANSSON_LIBRARY})
    set(JANSSON_INCLUDE_DIRS ${JANSSON_INCLUDE_DIR})
endif ()

mark_as_advanced(JANSSON_INCLUDE_DIR JANSSON_LIBRARY)