set(SOCKET_SOURCE
    secure.cpp
    socket.cpp
)

find_package(OpenSSL REQUIRED)
add_library(socket ${SOCKET_SOURCE})
target_link_libraries(socket OpenSSL::SSL)
