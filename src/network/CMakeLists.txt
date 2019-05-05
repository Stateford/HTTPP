set (NETWORK_SOURCE
    header.cpp
    http.cpp
    https.cpp
    request.cpp
    response.cpp
    socket.cpp
    url.cpp
)

add_library(network ${NETWORK_SOURCE})
