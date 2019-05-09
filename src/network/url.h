#pragma once
#include <string>

namespace Network {
    enum Protocol {
        HTTP,
        HTTPS
    };

    class URL {
        private:
            std::string _hostname;
            std::string _path;
            Protocol _protocol = HTTP;
        public:
            URL(const std::string&);
            URL(const URL&); // copy constructor
            URL& operator=(const URL&); // copy assignment

            URL(URL&&); // move constructor
            URL& operator=(URL&&); // move assignment

            const std::string getHost() const { return _hostname; };
            const std::string getPath() const { return _path; };
            unsigned short getPort() const { return _protocol == HTTP ? 80 : 443; }
            const std::string getPortString() const { return _protocol == HTTP ? "80" : "443"; }
            const Protocol getProtocol() const { return _protocol; }
    };
}
