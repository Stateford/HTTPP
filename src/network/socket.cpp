#include "socket.h"
#include "errors.h"
#include <vector>


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
            connect(_sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        }
        freeaddrinfo(ptr);
    }

    Socket::~Socket() noexcept {
        try {
            if(_result != nullptr)
                freeaddrinfo(_result);
            close(_sock);
        } catch(std::exception e) {
            std::cout << "failed to close socket:\n" << e.what() << std::endl;
        }
    }

    void Socket::send(const std::string& buffer) {
        int result = ::send(_sock, &buffer[0], buffer.size(), 0);
        if(result == -1)
            throw NetworkError("failed to send");
    }

    std::string Socket::recv() const {
        std::string response;
        response.reserve(2048);

        int bytes = 0;
        do {
            std::vector<char> buffer(2048);

            bytes = ::recv(_sock, &buffer[0], buffer.capacity(), 0);
            if(bytes > 0)
                response += std::string(buffer.begin(), buffer.begin() + bytes);
            else if (bytes < 0)
                throw NetworkError("Error recieving data");
        } while(bytes > 0);

        return response;
    }
}
