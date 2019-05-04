#include "request.h"


namespace Network {

    Request::Request(const std::string& url) {
        _url = std::make_unique<URL>(URL(url));
        _socket = std::make_unique<Socket>(Socket(_url->getHost(), _url->getPortString()));
        _headers["Host"] = _url->getHost();
    }

    // move constructor
    Request::Request(Request&& other) {
        _socket = std::move(other._socket);
        _url = std::move(other._url);
        _headers["Host"] = _url->getHost();
        _method = other._method;
        _response = other._response;
    }

    Request::~Request() {};

    // move assignment
    Request& Request::operator=(Request&& other) {
        if(&other == this)
            return *this;

        _socket = std::move(other._socket);
        _url = std::move(other._url);
        _headers["Host"] = _url->getHost();
        _method = other._method;
        _response = other._response;

        return *this;
    }

    const std::string Request::createPacket() const {
        std::string temp;
        temp.reserve(400);

        switch(_method) {
            case GET:
                temp += "GET";
                break;
            default:
                break;
        }

        temp += " " + _url->getPath() + " HTTP/1.1\r\n";

        if(!_headers.isEmpty()) {
            for(const auto& p : _headers)
                temp += p.first + ": " + p.second + "\r\n";
        }
        temp += "\r\n\r\n";

        return temp;
    }
}
