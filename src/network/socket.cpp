#include "socket.h"
#include "errors.h"

namespace Network {

    unsigned int Socket::_refrenceCount = 0;

    Socket::Socket(const std::string &hostname, const std::string &port) {
        _refrenceCount++;
        _hints.ai_family = AF_INET;
        _hints.ai_socktype = SOCK_STREAM;
        _hints.ai_protocol = IPPROTO_TCP;
        
        int result = getaddrinfo(hostname.c_str(), port.c_str(), &_hints, &_result);
        if(result == -1)
            throw NetworkError("Couldn't resolve DNS");
        
        addrinfo *ptr;
        for(ptr = _result; ptr != NULL; ptr = ptr->ai_next)
        {
            _sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            std::cout << _sock << std::endl;

            std::cout << "Sock status: " << _sock << std::endl;

            int status = connect(_sock, ptr->ai_addr, (int)ptr->ai_addrlen);
            std::cout << "connect status: " << status << std::endl;

        }
        freeaddrinfo(ptr);
    }

    Socket::Socket(const Socket& other) {
        _refrenceCount++;
        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_result = other._result;
    }

    Socket& Socket::operator=(const Socket& other)
    {
        if(&other == this)
            return *this;

        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_result = other._result;

        return *this;
    }

    Socket::~Socket() noexcept {
        _refrenceCount--;
        if(_refrenceCount == 0)
        {
            close(_sock);
            freeaddrinfo(_result);
        }
    }
}
