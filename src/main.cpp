#include <iostream>
#include "network/errors.h"
#include "network/http.h"


int main()
{
    try {
        Network::Http request("winamp.com");
        request.request();
        auto response = request.getResponse();
        std::cout << response.getContent() << std::endl;
        for(const auto& p : response.getHeader()) {
            std::cout << p.first << ": " << p.second << "\n";
        }
    } catch(Network::NetworkError e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
