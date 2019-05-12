#include "socket.h"
#include "../errors.h"
#include <vector>


namespace Network {

    Socket::Socket() : BaseSocket() {
        this->_sock_type = TCP;
#ifdef _WIN32
        windowsSetup();
#endif
    }

    Socket::Socket(const SOCK_TYPE type) : BaseSocket() {
        if(type < TCP || type > UDP)
            throw NetworkError("Invalid socket type");
        this->_sock_type = type;
#ifdef _WIN32
        windowsSetup();
#endif
    }

    // copy constructor
    Socket::Socket(const Socket& other) : BaseSocket() {
        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_sock_type = other._sock_type;
        this->_result = new addrinfo;
        *this->_result = *other._result;
    }

    // move constructor
    Socket::Socket(Socket&& other) : BaseSocket() {
        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_sock_type = other._sock_type;
        this->_result = other._result;
        other._result = nullptr;
    }

    // copy assignment
    Socket& Socket::operator=(const Socket& other) {
        if(&other == this)
            return *this;

        this->_sock = other._sock;
        this->_hints = other._hints;
        this->_sock_type = other._sock_type;

        if(this->_result != nullptr)
            freeaddrinfo(this->_result);
        this->_result = new addrinfo;
        *this->_result = *other._result;

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
        this->_sock_type = other._sock_type;
        other._result = nullptr;

        return *this;
    }

    void Socket::setHints() {
        _hints.ai_family = AF_INET;
        switch(_sock_type) {
            case TCP:
                _hints.ai_socktype = SOCK_STREAM;
                _hints.ai_protocol = IPPROTO_TCP;
                break;
            case UDP:
                _hints.ai_socktype = SOCK_DGRAM;
                _hints.ai_protocol = IPPROTO_UDP;
                break;
            default:
                throw NetworkError("Invalid sock type");
        }
    }

    void Socket::connectSocket(const std::string& hostname, const std::string& port) {
        setHints();
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
        _socketOpen = true;
    }

    void Socket::closeSocket() {
        ::close(_sock);
        _socketOpen = false;
    }

    Socket::~Socket() noexcept {
        try {
            if(_result != nullptr)
                freeaddrinfo(_result);
            close(_sock);
        } catch(std::exception e) {
            std::cout << "failed to close socket:\n" << e.what() << std::endl;
        }
#ifdef _WIN32
        windowsCleanup();
#endif
    }

    void Socket::send(const std::string& buffer) const {
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

    void Socket::closeSocket(Socket& sock) {
        close(sock._sock);
    }

#ifdef _WIN32
    void Socket::windowsSetup() const {
        WSADATA data;
        const int result = WSAStartup(MAKEWORD(2,2), &data);
        if(result != 0)
            throw NetworkError("Could not startup winsock library");
    }

    void Socket::windowsCleanup() const {
        WSACleanup();
    }

#endif
}
