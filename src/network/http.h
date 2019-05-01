#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "socket.h"
#include "header.h"
#include "url.h"
#include "response.h"
#include "request.h"

namespace Network {

    class Http : public Request
    {
        public:
            Http(const std::string& url) : Request(url) {};
            ~Http() {};

            void request() override;
    };

}
