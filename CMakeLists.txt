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

CMAKE_MINIMUM_REQUIRED(VERSION "3.0")
PROJECT(SharemindLibDataStoreManager VERSION "0.1.5" LANGUAGES "CXX")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers 1.4 REQUIRED)

FIND_PACKAGE(SharemindCxxHeaders 0.8.0 REQUIRED)
FIND_PACKAGE(SharemindDataStoreApi 0.1.0 REQUIRED)


# Headers:
FILE(GLOB_RECURSE SharemindLibDataStoreManager_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
INSTALL(FILES ${SharemindLibDataStoreManager_HEADERS}
        DESTINATION "include/sharemind"
        COMPONENT "dev")

# The library:
SharemindNewUniqueList(SharemindLibDataStoreManager_LINK_LIBRARIES
    ${SharemindCxxHeaders_LIBRARIES}
)
SharemindNewUniqueList(SharemindLibDataStoreManager_INCLUDE_DIRS
    ${SharemindCxxHeaders_INCLUDE_DIRS}
)
SharemindNewUniqueList(SharemindLibDataStoreManager_DEFINITIONS
    ${SharemindCxxHeaders_DEFINITIONS}
)
SharemindSetCxx14CompileOptions()
FILE(GLOB_RECURSE SharemindLibDataStoreManager_SOURCES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
SharemindAddSharedLibrary(LibDataStoreManager
    OUTPUT_NAME "sharemind_datastoremanager"
    SOURCES
        ${SharemindLibDataStoreManager_SOURCES}
        ${SharemindLibDataStoreManager_HEADERS}
    INCLUDE_DIRECTORIES
        ${SharemindLibDataStoreManager_INCLUDE_DIRS}
    LEGACY_DEFINITIONS
        ${SharemindLibDataStoreManager_DEFINITIONS}
    COMPILE_DEFINITIONS
        "SHAREMIND_INTERNAL_"
    LINK_LIBRARIES
        ${SharemindLibDataStoreManager_LINK_LIBRARIES}
)
TARGET_LINK_LIBRARIES(LibDataStoreManager PUBLIC Sharemind::DataStoreApi)

# Install CMake files:
SharemindCreateCMakeFindFiles(
    INCLUDE_DIRS
        "${CMAKE_INSTALL_PREFIX}/include"
        ${SharemindLibDataStoreManager_INCLUDE_DIRS}
    DEFINITIONS
        ${SharemindLibDataStoreManager_DEFINITIONS}
    LIBRARIES
        ${SharemindLibDataStoreManager_LINK_LIBRARIES}
        "-L${CMAKE_INSTALL_PREFIX}/lib"
        "-lsharemind_datastoremanager"
)


# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("lib"
    NAME "libsharemind-datastoremanager"
    DESCRIPTION "Sharemind Data Store Manager library"
    DEB_SECTION "libs"
    DEB_DEPENDS "libstdc++6 (>= 4.8.0)"
)
SharemindAddComponentPackage("dev"
    NAME "libsharemind-datastoremanager-dev"
    DESCRIPTION "Sharemind Data Store Manager library development headers"
    DEB_SECTION "libdevel"
    DEB_DEPENDS
        "libsharemind-datastoremanager (>= ${SharemindLibDataStoreManager_DEB_lib_PACKAGE_VERSION})"
        "libsharemind-cxxheaders-dev (>= 0.5.0)"
        "libstdc++-dev"
)
SharemindAddComponentPackage("debug"
    NAME "libsharemind-datastoremanager-dbg"
    DESCRIPTION "Sharemind Data Store Manager library debug symbols"
    DEB_SECTION "debug"
    DEB_DEPENDS
        "libsharemind-datastoremanager (>= ${SharemindLibDataStoreManager_DEB_lib_PACKAGE_VERSION})"
)
SharemindPackagingFinalize()
