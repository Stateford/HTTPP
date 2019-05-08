set (NETWORK_SOURCE
    header.cpp
    http.cpp
    https.cpp
    request.cpp
    response.cpp
    url.cpp
)

add_subdirectory(socket)

add_library(network ${NETWORK_SOURCE})
