cmake_minimum_required(VERSION 3.13)

project(asio_message_passing LANGUAGES CXX)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventSourceBuilds.cmake)

add_library(project_options INTERFACE)
add_library(project::options ALIAS project_options)

target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)
add_library(project::warnings ALIAS project_warnings)

include(cmake/Cache.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/StaticAnalyzers.cmake)

set_project_warnings(project_warnings)
enable_sanitizers(project_options)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

find_package(asio REQUIRED)
find_package(spdlog REQUIRED)
find_package(doctest REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/)

option(BUILD_TESTS "Build project tests" OFF)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/)
endif()

option(BUILD_EXAMPLES "Build project examples" OFF)

if(BUILD_EXAMPLES)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/)
endif()
