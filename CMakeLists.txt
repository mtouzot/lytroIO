# Copyright (c) 2023 lytroIO authors distributed under the GPL-3.0 license (https://opensource.org/license/gpl-3-0/)

cmake_minimum_required(VERSION 3.10...3.21)

#------------------------------------------------------------
# Start lytroIO project
#------------------------------------------------------------
project(lytroIO
        VERSION "0.0.0"
        DESCRIPTION "A C++ library to process Lytro files"
        HOMEPAGE_URL "https://github.com/mtouzot/lytroIO"
        LANGUAGES CXX)
message(STATUS "Building lytroIO v${CMAKE_PROJECT_VERSION}")

include(GNUInstallDirs)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/lytroio/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/lytroio/config.h)

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
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
    set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
    set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()

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
    include/lytroio/config.h
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
add_library(lytroIO ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})
target_link_libraries(lytroIO PRIVATE nlohmann_json::nlohmann_json)

# Add the include directories
target_include_directories(lytroIO
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set the library version
set_target_properties(lytroIO PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Debug")
else()
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Release")
endif()

# Install the library
install(TARGETS lytroIO
    EXPORT lytroIOConfig
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
install(EXPORT lytroIOConfig
    NAMESPACE lytroIO::
    DESTINATION lib/cmake/lytroIO
)

# Create a package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/lytroIOConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/lytroIOConfigVersion.cmake
    DESTINATION lib/cmake/lytroIO
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

option(BUILD_DOCS "Build documentation" OFF)

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