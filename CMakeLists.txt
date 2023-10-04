# Copyright (c) 2023 LytroIO authors distributed under the GPL-3.0 license (https://opensource.org/license/gpl-3-0/)

cmake_minimum_required(VERSION 3.10...3.21)

#------------------------------------------------------------
# Start LytroIO project
#------------------------------------------------------------
project(lytroio
        VERSION "0.0.0"
        DESCRIPTION "A C++ library to process Lytro files"
        HOMEPAGE_URL "https://github.com/mtouzot/lytroIO"
        LANGUAGES CXX)
message(STATUS "Building LytroIO v${CMAKE_PROJECT_VERSION}")

include(GNUInstallDirs)

# Source and header dir
set(PROJECT_INCLUDE_DIR "include/lytroio")
set(PROJECT_SOURCE_DIR "src")

#------------------------------------------------------------
# Set default build to release
#------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release of Debug" FORCE)
endif()

#------------------------------------------------------------
# Compiler config
#------------------------------------------------------------

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# make sure __cplusplus is defined when using msvc and enable parallel build
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /MP")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME MATCHES "CYGWIN" OR CMAKE_SYSTEM_NAME MATCHES "MSYS")
    set(CMAKE_CXX_EXTENSIONS ON)
endif()

#------------------------------------------------------------
# Project config
#------------------------------------------------------------

# Define your library sources
set(PUBLIC_HEADERS
    include/lytroio/lytrostream/lytrodecoder.hpp
    include/lytroio/lytrostream/lytroelement.hpp
    include/lytroio/lytrostream/lytrofile.hpp
)

set(PRIVATE_HEADERS
    src/lytrostream/utils.hpp
)

set(SOURCES
    src/lytrostream/lytrodecoder.cpp
    src/lytrostream/lytroelement.cpp
    src/lytrostream/lytrofile.cpp
)

# Third-party libraries
add_subdirectory(libs)

# Create the library target
add_library(LytroIO ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})
target_link_libraries(LytroIO PRIVATE nlohmann_json::nlohmann_json)

# Add the include directories
target_include_directories(LytroIO
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set the library version
set_target_properties(LytroIO PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Debug")
else()
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Release")
endif()

# Install the library
install(TARGETS LytroIO
    EXPORT LytroIOConfig
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install public headers
install(DIRECTORY include/lytroio
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# Generate and install the CMake configuration files
install(EXPORT LytroIOConfig
    NAMESPACE LytroIO::
    DESTINATION lib/cmake/LytroIO
)

# Create a package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/LytroIOConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LytroIOConfigVersion.cmake
    DESTINATION lib/cmake/LytroIO
)

#------------------------------------------------------------
# Examples
#------------------------------------------------------------

option(BUILD_EXAMPLES "Build examples" OFF)

if(BUILD_EXAMPLES)
    message(STATUS "Building examples")
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)

#------------------------------------------------------------
# Doxygen config
#------------------------------------------------------------

option(BUILD_DOCS "Build documentation" ON)

if(BUILD_DOCS)
    # Check if Doxygen is installed
    find_package(Doxygen REQUIRED)
    if(DOXYGEN_FOUND)
        # Set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxygen.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # Request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message(STATUS "Doxygen build started")

        # Note the option ALL which allows to build the docs together
        # with the application
        add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else(DOXYGEN_FOUND)
    message(STATUS "Doxygen need to be installed to generate the doxygen documentation")
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)