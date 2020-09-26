#include "network/errors.h"
#include "network/request.h"
#include "network/cookies//cookie.h"
#include <iostream>
#include <string>


int main()
{
    try {
        Network::Request request("winamp.com");
        request.request();
        auto response = request.getResponse();
        std::cout << response.getContent() << std::endl;
    } catch(Network::NetworkError e) {
        std::cout << "ERROR" << std::endl;
        std::cout << e.what() << std::endl;
    }
    return 0;
}
