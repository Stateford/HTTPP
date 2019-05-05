#pragma once
#include <string>
#include <memory>
#include "url.h"
#include "socket.h"
#include "header.h"
#include "response.h"

namespace Network {

    class Request {
        protected:
            std::shared_ptr<Socket> _socket;
            std::shared_ptr<URL> _url;
            enum Method {
                GET,
                POST,
                PUT,
                DELETE
            };
            Header _headers;
            Response _response;
            Method _method;

            virtual const std::string createPacket() const;

        public:
            Request(const std::string&);
            Request(const Request&); // copy constructor
            Request(Request&&); // move constructor

            Request& operator=(const Request&); // copy assignment
            Request& operator=(Request&&); // move assignment

            virtual ~Request() = 0;
            virtual void request() = 0;
            const Response getResponse() const { return _response; };
    };
}
