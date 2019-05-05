#include "http.h"
#include "errors.h"
#include <map>

extern "C" {
#include <errno.h>
}


namespace Network {

    void Http::request() {
        _socket->connectSocket();
        std::string responseBuffer;
        responseBuffer.reserve(10'000);

        const std::string httpPacket = createPacket();
        int status = send(_socket->getSocket(), httpPacket.c_str(), httpPacket.size(), 0);

        if(status == -1)
            throw NetworkError("Error sending data: " + std::to_string(errno));

        int result = 100;

        do {
            std::vector<char> buffer(2048);

            result = recv(_socket->getSocket(), &buffer[0], 2048, 0);
            if (result > 0)
            {
                if (result != 0 && buffer[result - 1] == '\0')
                    std::cout << "got zero" << std::endl;
                responseBuffer += std::string(buffer.begin(), buffer.begin() + result);
            }
            else if (result == 0)
                break;
            else
                throw NetworkError("error: " + std::to_string(errno));
        } while(result > 0);
        _response.parseResponse(responseBuffer);
    }
}
