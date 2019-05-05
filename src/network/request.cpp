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
        this->_body = other._body;
    }

    // move constructor
    Request::Request(Request&& other) {
        this->_socket = std::move(other._socket);
        this->_url = std::move(other._url);
        this->_headers = other._headers;
        this->_method = other._method;
        this->_response = other._response;
        this->_body = other._body;
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
        this->_body = other._body;

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
        this->_body = other._body;

        return *this;
    }

    void Request::setBody(const std::string& body) {
        _body = body;
    }

    const std::string Request::createPacket(){ 
        std::string temp;
        temp.reserve(400);

        switch(_method) {
            case GET:
                temp += "GET";
                break;
            case POST:
                temp += "POST";
                break;
            case PUT:
                temp += "PUT";
                break;
            case DELETE:
                temp += "DELETE";
                break;
            case HEAD:
                temp += "HEAD";
                break;
            case CONNECT:
                temp += "CONNECT";
                break;
            case OPTIONS:
                temp += "OPTIONS";
                break;
            case TRACE:
                temp += "TRACE";
                break;
            case PATCH:
                temp += "PATCH";
                break;
            default:
                break;
        }

        temp += " " + _url->getPath() + " HTTP/1.1\r\n";

        if(!_body.empty() && _method != GET) {
            _headers["Content-Length"] = std::to_string(_body.size());
        }

        if(!_headers.isEmpty()) {
            for(const auto& p : _headers)
                temp += p.first + ": " + p.second + "\r\n";
        }

        temp += "\r\n\r\n";

        if(!_body.empty() && _method != GET)
            temp += _body + "\r\n\r\n";

        return temp;
    }
}
