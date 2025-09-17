cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

project(
    kinematics
    VERSION ${VERSION}
    LANGUAGES CXX C
)

# If user didn't set an install prefix, default to ../server/kinematics relative to this CMakeLists.txt
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../server/kinematics" CACHE PATH "Install path prefix" FORCE)
endif()

# only windows specific stuff
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_TESTS "Build tests" ON)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/version/version.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/version)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(wb_kinematics_static STATIC ${SOURCES})
target_include_directories(wb_kinematics_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(wb_kinematics_shared SHARED ${SOURCES})
target_include_directories(wb_kinematics_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# add tests
if(BUILD_TESTS)
   add_subdirectory(tests)
endif()

# Install the shared library and header file
install(TARGETS wb_kinematics_static wb_kinematics_shared
        EXPORT wb_kinematics-targets
        RUNTIME DESTINATION lib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

# Install all public headers (preserve include/wabo/...)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h"
)