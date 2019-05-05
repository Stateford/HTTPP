#pragma once
#include "request.h"


namespace Network {

    class UnimplementedError : public std::exception {
        private:
            std::string _message;

        public:
            UnimplementedError(const std::string& message) : std::exception() {
                _message = message;
            }

            const char* what() const throw() { return _message.c_str(); }
    };

    class Https : public Request {
        public:
            Https(const std::string& url) : Request(url) {};
            ~Https() = default;

            void request() override;
    };
}
