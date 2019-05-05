#pragma once
#include <exception>
#include <string>

namespace Network {

    class MethodError : public std::exception {
        private:
            std::string message;

        public:
            MethodError(const std::string& message) : std::exception() {
                this->message = message;
            }

            const char* what() const throw() { return message.c_str(); }
    };

    class NetworkError : public std::exception {
        private:
            std::string message;

        public:
            NetworkError(const std::string& message) : std::exception() {
                this->message = message;
            }

            const char* what() const throw() { return message.c_str(); }
    };
}
