cmake_minimum_required(VERSION 2.8)
project(conservator)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

find_package(Threads REQUIRED)
find_package(Zookeeper REQUIRED)
find_package(Check REQUIRED)

enable_testing()

include_directories(${CHECK_INCLUDE_DIRS})
include_directories(${ZOOKEEPER_INCLUDE_DIR}/zookeeper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(conservator-framework SHARED
  conservator-framework/src/ConservatorFramework.cpp
  conservator-framework/src/ConservatorFrameworkFactory.cpp
  conservator-framework/src/GetDataBuilderImpl.cpp
  conservator-framework/src/ExistsBuilderImpl.cpp
  conservator-framework/src/CreateBuilderImpl.cpp
  conservator-framework/src/DeleteBuilderImpl.cpp
  conservator-framework/src/SetDataBuilderImpl.cpp
  conservator-framework/src/GetChildrenBuilderImpl.cpp
  conservator-framework/src/ChildrenDeletable.h
  conservator-framework/src/PathableAndWatchable.h
  conservator-framework/src/VectorPathableAndWatchable.h
  conservator-framework/src/VectorPathable.h
  conservator-framework/src/GetACLBuilder.h
  conservator-framework/src/GetACLBuilderImpl.h
  conservator-framework/src/StatablePathable.h
  conservator-framework/src/GetACLBuilderImpl.cpp
  conservator-framework/src/SetACLBuilder.h
  conservator-framework/src/ACLVersionable.h
  conservator-framework/src/SetACLBuilderImpl.cpp
  conservator-framework/src/SetACLBuilderImpl.h
  conservator-framework/src/Flagable.h)

add_subdirectory(conservator-framework/tests)

install(TARGETS conservator-framework DESTINATION lib)

# Do we need all headers?
install(DIRECTORY conservator-framework/src/ DESTINATION include/conservator
  FILES_MATCHING PATTERN "*h")
