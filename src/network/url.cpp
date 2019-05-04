#include "url.h"
#include "errors.h"
#include <algorithm>
#include <iostream>

namespace Network {
    
    URL::URL(const std::string& url) {
        size_t protocolPosition = url.find("://");

        if(protocolPosition != std::string::npos) {
            std::string protocol = url.substr(0, protocolPosition);
            std::transform(protocol.begin(), protocol.end(), protocol.begin(), ::tolower);
            protocolPosition += 3;

            if(protocol != "http" || protocol != "https")
                throw NetworkError("URL Protocol was incorrect");
        }
        else {
            _protocol = HTTP;
            protocolPosition = 0;
        }

        const size_t hostnamePosition = url.find('/', protocolPosition);
        if(hostnamePosition != std::string::npos) {
            _hostname = url.substr(protocolPosition, hostnamePosition);
            _path = url.substr(hostnamePosition + 1);
        }
        else {
            _hostname = url.substr(protocolPosition);
            _path = "/";
        }
        std::cout << _hostname << std::endl;
        std::cout << _path << std::endl;
    }

    URL::URL(const URL& other) {
        _hostname = other._hostname;
        _path = other._path;
        _protocol = other._protocol;
    }

    URL& URL::operator=(const URL& other) {
        if(&other == this)
            return *this;

        _hostname = other._hostname;
        _path = other._path;
        _protocol = other._protocol;

        return *this;
    }

    URL::URL(URL&& other) {
        _hostname = other._hostname;
        _path = other._path;
        _protocol = other._protocol;
    }

    URL& URL::operator=(URL&& other) {
        if(&other == this)
            return *this;

        _hostname = other._hostname;
        _path = other._path;
        _protocol = other._protocol;

        return *this;
    }
}
