#pragma once
#include "baseSocket.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifdef __linux__
#include <netdb.h>
#include <memory>
typedef int sock;
#elif _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // include winsock lib
typedef SOCKET sock;
#endif



namespace Network {

    class Socket : public BaseSocket {
        private:
            sock _sock;
            addrinfo _hints;
            addrinfo* _result;

            SOCK_TYPE _sock_type;

            void setHints();
#ifdef _WIN32
            void windowsSetup() const;
            void windowsCleanup() const;
#endif

        public:
            Socket();
            Socket(const SOCK_TYPE);
            Socket(const Socket&);  // copy constructor
            Socket(Socket&&); // move constructor

            Socket& operator=(const Socket&);   // copy assignment
            Socket& operator=(Socket&&); // move assignment
            ~Socket() noexcept override;

            void connectSocket(const std::string&, const std::string&) override;
            void closeSocket() override;
            static void closeSocket(Socket&);

            int getSocket() { return _sock; }
            void send(const std::string&) const override;
            std::string recv() const override;
    };
}
