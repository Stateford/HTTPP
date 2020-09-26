#pragma once
#include <iostream>
#include <vector>
#include <string>


namespace Network {
    namespace Utils {

        struct KeyValuePair
        {
            std::string key;
            std::string value;
        };

        KeyValuePair splitKeyValue(const std::string& source, const std::string& delimiter = "=")
        {
            size_t position = 0;
            KeyValuePair data;

            if((position = source.find(delimiter)) != std::string::npos)
            {
                data.key = source.substr(0, position);
                data.value = source.substr(position + 1);
            }

            return data;
        }

        std::vector<std::string> splitString(std::string source, const std::string& delimiter)
        {
            std::vector<std::string> data;

            size_t pos = 0;

            while((pos = source.find(delimiter)) != std::string::npos)
            {
                std::string token = source.substr(0, pos);
                data.push_back(token);
                source.erase(0, pos + delimiter.length());
            }

            data.push_back(source);

            return data;
        }

        std::string toLower(std::string value)
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c){ return std::tolower(c); });
            return value;
        }
    }
}
