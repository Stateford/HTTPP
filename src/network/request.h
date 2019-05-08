#pragma once
#include "url.h"
#include "socket/socket.h"
#include "header.h"
#include "response.h"
#include <string>
#include <memory>

namespace Network {

    class Request {
        protected:
            std::shared_ptr<Socket> _socket;
            std::shared_ptr<URL> _url;
            enum Method {
                GET,
                POST,
                PUT,
                DELETE,
                HEAD,
                CONNECT,
                OPTIONS,
                TRACE,
                PATCH
            };
            Header _headers;
            Response _response;
            Method _method;
            std::string _body;

            const std::string createPacket();
            const std::string getMethod() const;

        public:
            Request(const std::string&);
            Request(const Request&); // copy constructor
            Request(Request&&); // move constructor

            Request& operator=(const Request&); // copy assignment
            Request& operator=(Request&&); // move assignment

            virtual ~Request() = 0;
            virtual void request() = 0;

            void setBody(const std::string&);

            const Response getResponse() const { return _response; };
    };
}
