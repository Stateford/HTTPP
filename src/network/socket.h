#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <memory>


namespace Network {

    class Socket
    {
        private:
            int _sock;
            bool _isOpen = false;
            addrinfo _hints;
            addrinfo* _result;

            std::string hostname;
            std::string port;

        public:
            Socket(const std::string&, const std::string&);
            Socket(const Socket&);  // copy constructor
            Socket(Socket&&); // move constructor

            Socket& operator=(const Socket&);   // copy assignment
            Socket& operator=(Socket&&); // move assignment
            ~Socket() noexcept;

            void connectSocket();
            static void closeSocket(Socket*);

            bool isOpen() { return _isOpen; }
            int getSocket() { return _sock; }
    };
}
