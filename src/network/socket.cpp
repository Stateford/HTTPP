#include "socket.h"
#include "errors.h"


namespace Network {

    Socket::Socket(const std::string &hostname, const std::string &port) {
        _hints.ai_family = AF_INET;
        _hints.ai_socktype = SOCK_STREAM;
        _hints.ai_protocol = IPPROTO_TCP;
        this->hostname = hostname;
        this->port = port;
    }

    // copy constructor
    Socket::Socket(const Socket& other) {
        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_result = new addrinfo;
        *this->_result = *other._result;

        this->hostname = other.hostname;
        this->port = other.port;
    }

    // move constructor
    Socket::Socket(Socket&& other) {
        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_result = other._result;
        other._result = nullptr;

        this->hostname = other.hostname;
        this->port = other.port;
    }

    // copy assignment
    Socket& Socket::operator=(const Socket& other) {
        if(&other == this)
            return *this;

        this->_sock = other._sock;
        this->_hints = other._hints;

        if(this->_result != nullptr)
            freeaddrinfo(this->_result);
        this->_result = new addrinfo;
        *this->_result = *other._result;

        this->hostname = other.hostname;
        this->port = other.port;

        return *this;
    }

    // move assignment
    Socket& Socket::operator=(Socket&& other) {
        std::cout << "move assignment" << std::endl;
        if(&other == this)
            return *this;

        if(this->_result != nullptr)
            freeaddrinfo(this->_result);

        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_result = other._result;
        other._result = nullptr;

        this->hostname = other.hostname;
        this->port = other.port;

        return *this;
    }

    void Socket::connectSocket() {
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
        _isOpen = true;
    }

    Socket::~Socket() noexcept {
        if(_isOpen && _result != nullptr)
            close(_sock);
        else if(_result != nullptr)
            freeaddrinfo(_result);
    }
}
