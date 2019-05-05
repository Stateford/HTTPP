cmake_minimum_required(VERSION 3.6)

project(HTTPP)

# Versions
set (HTTPP_VERSION_MAJOR 0)
set (HTTPP_VERSION_MINOR 0)
set (HTTPP_VERSION_PATCH 1)

set (HTTPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (HTTPP_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_subdirectory(src)

set(HTTP_SOURCE_FILES src/main.cpp)

find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} ${HTTP_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} network)
