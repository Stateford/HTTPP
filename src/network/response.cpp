#include "response.h"
#include "errors.h"
#include <vector>
#include <iostream>

namespace Network {

    Response::Response(const std::string& response) {
        parseResponse(response);
    }

    void Response::parseResponse(const std::string& response) {
        // TODO: parse first line of header
        // HTTP/1.1 200 OK
        const size_t headerPosition = response.find("\r\n\r\n");
        if(headerPosition == std::string::npos)
            throw NetworkError("Response was malformed");

        std::string header = response.substr(0, headerPosition);
        std::cout << header << std::endl;
        _content = response.substr(headerPosition + 4);
        std::vector<std::string> headers;
        headers.reserve(20);

        const std::string delimiter = "\r\n";
        size_t pos = 0;
        size_t prev = 0;

        while ((pos = header.find(delimiter, prev)) != std::string::npos)
        {
            headers.push_back(header.substr(prev, pos - prev));
            prev = pos + delimiter.length();
        }

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
