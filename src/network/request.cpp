#include "request.h"
#include "errors.h"


namespace Network {

    Request::Request(const std::string& url) {
        _url = std::make_shared<URL>(url);
        _socket = std::make_shared<Socket>(SOCK_TYPE::TCP);
        _secureSocket = std::make_shared<SecureSocket>(SOCK_TYPE::TCP);
        _headers["Host"] = _url->getHost();
        _method = GET;
    }

    // copy constructor
    Request::Request(const Request& other) {
        this->_socket = other._socket;
        this->_secureSocket = other._secureSocket;
        this->_url = other._url;
        this->_headers = other._headers;
        this->_method = other._method;
        this->_response = other._response;
        this->_body = other._body;
    }

    // move constructor
    Request::Request(Request&& other) {
        this->_socket = std::move(other._socket);
        this->_secureSocket = std::move(other._secureSocket);
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
        this->_secureSocket = other._secureSocket;
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
        this->_secureSocket = std::move(other._secureSocket);
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

    const std::string Request::getMethod() const {
        switch(_method) {
            case GET:
                return "GET";
            case POST:
                return "POST";
            case PUT:
                return "PUT";
            case DELETE:
                return "DELETE";
            case HEAD:
                return "HEAD";
            case CONNECT:
                return "CONNECT";
            case OPTIONS:
                return "OPTIONS";
            case TRACE:
                return "TRACE";
            case PATCH:
                return "PATCH";
            default:
                throw NetworkError("Invalid Method");
        }
    }

    void Request::request() {
        std::shared_ptr<BaseSocket> sock;
        if(_url->getProtocol() == HTTPS)
            sock = _secureSocket;
        else
            sock = _socket;
        sock->connectSocket(_url->getHost(), _url->getPortString());
        std::string responseBuffer;
        responseBuffer.reserve(10'000);

        const std::string httpPacket = createPacket();
        _socket->send(httpPacket);

        const std::string response = _socket->recv();
        
        if(sock->isOpen() && (!_headers.contains("Connection") || _headers["Connection"] == "Close"))
            sock->closeSocket();

        _response.parseResponse(response);
    }

    const std::string Request::createPacket() { 
        std::string temp;
        temp.reserve(400);

        temp += getMethod();

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

    void Request::setMethod(Method method) {
        _method = method;
    }

    Response Request::get(const std::string& hostname) {
        auto req = Request(hostname);
        req.request();

        return req.getResponse();
    }
}
