#
# Copyright (C) 2015 Cybernetica
#
# Research/Commercial License Usage
# Licensees holding a valid Research License or Commercial License
# for the Software may use this file according to the written
# agreement between you and Cybernetica.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of the GNU
# General Public License version 3.0 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU General Public License version 3.0 requirements will be
# met: http://www.gnu.org/copyleft/gpl-3.0.html.
#
# For further information, please contact us at sharemind@cyber.ee.
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(SharemindLibDataStoreManager CXX)

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

SET(LIBDATASTOREMANAGER_VERSION "0.1.0")

SET(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(SharemindCxxHeaders REQUIRED)
FIND_PACKAGE(SharemindLibProcessFacility REQUIRED)

SET(LIBDATASTOREMANAGER_EXTERNAL_LINK_LIBRARIES "")
LIST(APPEND LIBDATASTOREMANAGER_EXTERNAL_LINK_LIBRARIES
    ${SharemindCxxHeaders_LIBRARIES}
    ${SharemindLibProcessFacility_LIBRARIES}
)
SET(LIBDATASTOREMANAGER_EXTERNAL_INCLUDE_DIRS "")
LIST(APPEND LIBDATASTOREMANAGER_EXTERNAL_INCLUDE_DIRS
    ${SharemindCxxHeaders_INCLUDE_DIRS}
    ${SharemindLibProcessFacility_INCLUDE_DIRS}
)
SET(LIBDATASTOREMANAGER_EXTERNAL_DEFINITIONS "")
LIST(APPEND LIBDATASTOREMANAGER_EXTERNAL_DEFINITIONS
    ${SharemindCxxHeaders_DEFINITIONS}
    ${SharemindLibProcessFacility_DEFINITIONS}
)
LIST(REMOVE_DUPLICATES LIBDATASTOREMANAGER_EXTERNAL_LINK_LIBRARIES)
LIST(REMOVE_DUPLICATES LIBDATASTOREMANAGER_EXTERNAL_INCLUDE_DIRS)
LIST(REMOVE_DUPLICATES LIBDATASTOREMANAGER_EXTERNAL_DEFINITIONS)


SET(LIBDATASTOREMANAGER_INSTALL_LINK_LIBRARIES
    ${LIBDATASTOREMANAGER_EXTERNAL_LINK_LIBRARIES}
    "-L${CMAKE_INSTALL_PREFIX}/lib" "-lsharemind_datastoremanager")
SET(LIBDATASTOREMANAGER_INSTALL_INCLUDE_DIRS
    "${CMAKE_INSTALL_PREFIX}/include"
    ${LIBDATASTOREMANAGER_EXTERNAL_INCLUDE_DIRS})
SET(LIBDATASTOREMANAGER_INSTALL_DEFINITIONS
    ${LIBDATASTOREMANAGER_EXTERNAL_DEFINITIONS})
LIST(REMOVE_DUPLICATES LIBDATASTOREMANAGER_INSTALL_INCLUDE_DIRS)

INCLUDE_DIRECTORIES(${LIBDATASTOREMANAGER_EXTERNAL_INCLUDE_DIRS})
ADD_DEFINITIONS(
    ${LIBDATASTOREMANAGER_EXTERNAL_DEFINITIONS}
    "-DSHAREMIND_INTERNAL__"
)
ADD_COMPILE_OPTIONS(
  "-std=c++11" "-Wall" "-Wextra" "-O2" "-fPIC"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-ggdb>"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-fno-omit-frame-pointer>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-DNDEBUG>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-fomit-frame-pointer>"
)

FILE(GLOB_RECURSE LIBDATASTOREMANAGER_SOURCES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
FILE(GLOB_RECURSE LIBDATASTOREMANAGER_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
ADD_LIBRARY("libdatastoremanager" SHARED ${LIBDATASTOREMANAGER_SOURCES}
                                          ${LIBDATASTOREMANAGER_HEADERS})
SET_TARGET_PROPERTIES("libdatastoremanager" PROPERTIES
                      OUTPUT_NAME "sharemind_datastoremanager"
                      VERSION "${LIBDATASTOREMANAGER_VERSION}"
                      SOVERSION "0.1")
TARGET_LINK_LIBRARIES("libdatastoremanager"
                      ${LIBDATASTOREMANAGER_EXTERNAL_LINK_LIBRARIES})
INSTALL(TARGETS "libdatastoremanager" LIBRARY DESTINATION "lib")

INSTALL(FILES ${LIBDATASTOREMANAGER_HEADERS} DESTINATION "include/sharemind")

FILE(GLOB_RECURSE LIBDATASTOREMANAGER_INFILES
     "${CMAKE_CURRENT_SOURCE_DIR}/*.in")
ADD_CUSTOM_TARGET("include_LIBDATASTOREMANAGER_INFILES_in_IDE"
                  SOURCES ${LIBDATASTOREMANAGER_INFILES})

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibDataStoreManagerConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDataStoreManagerConfig.cmake"
  @ONLY)
INSTALL(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDataStoreManagerConfig.cmake"
  DESTINATION "lib/SharemindLibDataStoreManager")
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibDataStoreManagerConfigVersion.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDataStoreManagerConfigVersion.cmake"
  @ONLY)
INSTALL(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDataStoreManagerConfigVersion.cmake"
  DESTINATION "lib/SharemindLibDataStoreManager")
