#include "response.h"
#include "errors.h"
#include <vector>
#include <iostream>

namespace Network {

    Response::Response(const std::string& response) {
        parseResponse(response);
    }

    void Response::parseResponse(const std::string& response) {
        const size_t headerPosition = response.find("\r\n\r\n");
        if(headerPosition == std::string::npos)
            throw NetworkError("Response was malformed");

        std::string header = response.substr(0, headerPosition + 4);
        _content = response.substr(headerPosition + 4);
        std::vector<std::string> headers;
        headers.reserve(20);

        const std::string delimiter = "\r\n";
        size_t pos = 0;
        size_t prev = 0;

        pos = header.find(delimiter, prev);
        int protocolStart = header.find("HTTP/") + 5;
        int protocolStop = header.find(' ');
        _httpVersion = header.substr(protocolStart, protocolStop - protocolStart);
        int statusCode = std::stoi(header.substr(header.find(' ') + 1, header.find(' ')));
        statusCode &= 0xFFFF;
        _status = static_cast<short>(statusCode);
        prev = pos + delimiter.length();

        do {
            headers.push_back(header.substr(prev, pos - prev));
            prev = pos + delimiter.length();
        } while((pos = header.find(delimiter, prev)) != std::string::npos);

        while (_content.find(delimiter) != std::string::npos)
            _content.replace(_content.find(delimiter), delimiter.length(), "");

        for(const auto& item : headers) {
            const size_t pos = item.find(':');
            const std::string key = item.substr(0, pos);
            const std::string value = item.substr(pos + 1);

            _headers[key] = value;
        }
    }
}
