set (NETWORK_SOURCE
    header.cpp
    response.cpp
    url.cpp
    request.cpp
)

add_subdirectory(socket)
add_subdirectory(cookies)

add_library(network ${NETWORK_SOURCE})
target_link_libraries(network socket)
target_link_libraries(network cookies)
