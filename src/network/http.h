#pragma once
#include "socket/socket.h"
#include "header.h"
#include "url.h"
#include "response.h"
#include "request.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

namespace Network {

    class Http : public Request {
        public:
            Http(const std::string& url) : Request(url) {};

            ~Http() = default;

            void request() override;
    };
}
