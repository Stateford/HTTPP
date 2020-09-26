#pragma once
#include <map>
#include <string>


namespace Network {

    using header_const_iterator = std::map<std::string, std::string>::const_iterator;
    using header_iterator = std::map<std::string, std::string>::iterator;

    class Cookies 
    {
        private:
            std::map<std::string, std::string> _cookies;

        public:
            Cookies();

            std::string& operator[](const std::string&);

            bool isEmpty() const { return _cookies.empty(); }
            bool contains(const std::string&) const;

            header_iterator begin() { return _cookies.begin(); }
            header_iterator end() { return _cookies.end(); }
            header_const_iterator begin() const { return _cookies.begin(); }
            header_const_iterator end() const { return _cookies.end(); }
    };
}
