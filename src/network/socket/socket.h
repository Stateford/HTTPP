#pragma once
#include "baseSocket.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <memory>


namespace Network {

    class Socket : public BaseSocket {
        private:
            int _sock;
            addrinfo _hints;
            addrinfo* _result;

            SOCK_TYPE _sock_type;

            void setHints();

        public:
            Socket();
            Socket(SOCK_TYPE);
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
