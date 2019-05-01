#pragma once
#include <map>
#include <string>

namespace Network {
    enum ContentType {
        PLAIN,
        CSV,
        HTML,
        JSON
    };

    using header_const_iterator = std::map<std::string, std::string>::const_iterator;
    using header_iterator = std::map<std::string, std::string>::iterator;
    
    class Header {
        private:
            std::map<std::string, std::string> _headers;
            void _setDefault();
        public:
            Header();
            Header(const std::string&);

            void setContentType(ContentType);

            std::string& operator[](const std::string&);

            bool isEmpty() const { return _headers.empty(); }

            header_iterator begin() { return _headers.begin(); }
            header_iterator end() { return _headers.end(); }
            header_const_iterator begin() const { return _headers.begin(); }
            header_const_iterator end() const { return _headers.end(); }
    };
}
