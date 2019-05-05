#include_directories(${HTTP_SOURCE_DIR}/inc)

add_subdirectory(network)

set(HTTPP_SOURCE_FILES main.cpp)

find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} ${HTTPP_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} network)
