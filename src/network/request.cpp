#include "request.h"


namespace Network {

    Request::Request(const std::string& url) {
        _url = std::make_shared<URL>(url);
        _socket = std::make_shared<Socket>(_url->getHost(), _url->getPortString());
        _headers["Host"] = _url->getHost();
        _method = GET;
    }

    // copy constructor
    Request::Request(const Request& other) {
        this->_socket = other._socket;
        this->_url = other._url;
        this->_headers = other._headers;
        this->_method = other._method;
        this->_response = other._response;
    }

    // move constructor
    Request::Request(Request&& other) {
        this->_socket = std::move(other._socket);
        this->_url = std::move(other._url);
        this->_headers = other._headers;
        this->_method = other._method;
        this->_response = other._response;
    }

    Request::~Request() {};

    Request& Request::operator=(const Request& other) {
        if(&other == this)
            return *this;

        this->_socket = other._socket;
        this->_url = other._url;
        this->_headers = other._headers;
        this->_method = other._method;
        this->_response = other._response;

        return *this;
    }

    // move assignment
    Request& Request::operator=(Request&& other) {
        if(&other == this)
            return *this;

        this->_socket = std::move(other._socket);
        this->_url = std::move(other._url);
        this->_headers = other._headers;
        this->_method = other._method;
        this->_response = other._response;

        return *this;
    }

    const std::string Request::createPacket() const {
        std::string temp;
        temp.reserve(400);

        switch(_method) {
            case GET:
                temp += "GET";
                break;
            case POST:
                temp += "POST";
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
