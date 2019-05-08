#include "http.h"
#include "errors.h"
#include <map>

extern "C" {
#include <errno.h>
}


namespace Network {

    void Http::request() {
        _socket->connectSocket(_url->getHost(), _url->getPortString());
        std::string responseBuffer;
        responseBuffer.reserve(10'000);

        const std::string httpPacket = createPacket();
        _socket->send(httpPacket);

        const std::string response = _socket->recv();
        _response.parseResponse(response);
    }
}
