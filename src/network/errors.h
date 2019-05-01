#pragma once
#include <exception>
#include <string>

namespace Network {

    class NetworkError : public std::exception
    {
        std::string message;
        public:
            NetworkError(std::string message) : std::exception() {
                this->message = message;
            }

            const char* what() const throw() { return message.c_str(); };
    };
}
