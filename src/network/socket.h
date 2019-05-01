#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


namespace Network {

    class Socket
    {
        private:
            static unsigned int _refrenceCount;
            int _sock;
            addrinfo _hints;
            addrinfo* _result;
        public:
            Socket(const std::string&, const std::string&);
            Socket(const Socket&);

            Socket& operator=(const Socket&);
            ~Socket() noexcept;

            int getSocket() { return _sock; }
    };
}
