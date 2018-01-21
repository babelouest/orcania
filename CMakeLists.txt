#
# Orcania Framework
#
# CMake file used to build all programs
#
# Copyright 2017 Nicolas Mora <mail@babelouest.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the MIT License
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

# Written by Silvio Clecio <silvioprog@gmail.com>
# Fri Jan 19 20:01:43 -03 2018

cmake_minimum_required(VERSION 3.5)

project(orcania C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

# library info

set(PROJECT_DESCRIPTION "Potluck with different functions for different purposes that can be shared among programs")
set(PROJECT_BUGREPORT_PATH "https://github.com/babelouest/orcania/issues")

set(LIBRARY_VERSION_MAJOR "1")
set(LIBRARY_VERSION_MINOR "1")
set(LIBRARY_VERSION_PATCH "1")
set(LIBRARY_VERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH}")
set(LIBRARY_SOVERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}")

add_definitions(-DLIBRARY_VERSION=\"${LIBRARY_VERSION}\")

# cmake modules

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

include(GNUInstallDirs)
include(CheckSymbolExists)

# check if _GNU_SOURCE is available

if (NOT _GNU_SOURCE)
    check_symbol_exists(__GNU_LIBRARY__ "features.h" _GNU_SOURCE)

    if (NOT _GNU_SOURCE)
        unset(_GNU_SOURCE CACHE)
        check_symbol_exists(_GNU_SOURCE "features.h" _GNU_SOURCE)
    endif ()
endif ()

if (_GNU_SOURCE)
    add_definitions(-D_GNU_SOURCE)
endif ()

# directories and source

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INC_DIR})

set(LIB_SRC
        ${INC_DIR}/orcania.h # allow many IDEs to find and edit it
        ${SRC_DIR}/base64.c
        ${SRC_DIR}/memory.c
        ${SRC_DIR}/orcania.c)

# static library

add_library(orcania_static STATIC ${LIB_SRC})
target_compile_definitions(orcania_static PUBLIC -DO_STATIC_LIBRARY)
set_target_properties(orcania_static PROPERTIES
        OUTPUT_NAME orcania)

# shared library

option(WITH_JANSSON "Use jansson library" ON)

if (WITH_JANSSON)
    include(FindJansson)
    find_package(Jansson)
    set(WITH_JANSSON ${JANSSON_FOUND})
    if (WITH_JANSSON)
        set(LIBS ${JANSSON_LIBRARIES})
        add_definitions(-DUSE_JANSSON=1)
    endif ()
endif ()

add_library(orcania SHARED ${LIB_SRC})
set_target_properties(orcania PROPERTIES
        COMPILE_OPTIONS -Wextra
        PUBLIC_HEADER ${INC_DIR}/orcania.h
        VERSION "${LIBRARY_VERSION}"
        SOVERSION "${LIBRARY_SOVERSION}")
if (WIN32)
    set_target_properties(orcania PROPERTIES SUFFIX "-${LIBRARY_VERSION_MAJOR}.dll")
endif ()
target_link_libraries(orcania ${LIBS})

# tests

option(BUILD_TESTING "Build the testing tree." OFF) # because we don not use include(CTest)

if (BUILD_TESTING)
    include(FindCheck)
    find_package(Check)
    if (CHECK_FOUND)
        include(FindSubunit)
        find_package(Subunit REQUIRED)

        enable_testing()

        set(CMAKE_CTEST_COMMAND ctest -V)

        set(TST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
        set(LIBS orcania ${LIBS} ${CHECK_LIBRARIES} ${SUBUNIT_LIBRARIES})
        if (NOT WIN32)
            find_package(Threads REQUIRED)
            set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})
        endif ()
        set(LIBS ${LIBS} m rt)

        set(TESTS
                str_test
                split_test
                memory_test)
        if (WITH_JANSSON)
            set(TESTS ${TESTS} jansson_test)
        endif ()

        configure_file(
                "${CMAKE_MODULE_PATH}/CTestCustom.cmake.in"
                "${CMAKE_CURRENT_BINARY_DIR}/CTestCustom.cmake"
                @ONLY)

        foreach (t ${TESTS})
            add_executable(${t} EXCLUDE_FROM_ALL ${TST_DIR}/${t}.c)
            target_include_directories(${t} PUBLIC ${TST_DIR})
            target_link_libraries(${t} PUBLIC ${LIBS})
            add_test(NAME ${t}
                    WORKING_DIRECTORY ${TST_DIR}
                    COMMAND ${t})
        endforeach ()
    endif ()
endif ()

# install target

configure_file(liborcania.pc.in liborcania.pc @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/liborcania.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install(TARGETS orcania orcania_static
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# uninstall target

if (NOT TARGET uninstall)
    configure_file(
            "${CMAKE_MODULE_PATH}/CMakeUninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)
    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif ()

# packaging

set(CPACK_PACKAGE_VERSION_MAJOR ${LIBRARY_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${LIBRARY_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${LIBRARY_VERSION_PATCH})

set(PACKAGE_FILE_NAME
        "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(PACKAGE_IGNORED_FILES
        "${CMAKE_CURRENT_BINARY_DIR}/;/.git/;.gitignore;/.idea/;~$;${CPACK_SOURCE_IGNORE_FILES}")

#set(CPACK_GENERATOR "TGZ;DEB;RPM")
#set(CPACK_DEBIAN_PACKAGE_MAINTAINER "silvioprog") # required
#set(CPACK_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})
set(CPACK_SOURCE_IGNORE_FILES ${PACKAGE_IGNORED_FILES})

include(CPack)

add_custom_target(dist
        COMMAND ${CMAKE_MAKE_PROGRAM} package_source)