set (NETWORK_SOURCE
    header.cpp
    response.cpp
    url.cpp
    request.cpp
)

add_subdirectory(socket)

add_library(network ${NETWORK_SOURCE})
target_link_libraries(network socket)
