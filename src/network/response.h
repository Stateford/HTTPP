#pragma once
#include <string>
#include "header.h"

namespace Network {
    
    class Response {
        private:
            Header _headers;
            std::string _content;
            unsigned short _status = 0;
        public:
            Response() = default;
            Response(const std::string&);

            void parseResponse(const std::string&);
            const std::string getContent() const { return _content; }
            const Header getHeader() const { return _headers; }
            unsigned short getStatus() const { return _status; }
    };
}
