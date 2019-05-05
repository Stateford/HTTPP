#include <iostream>
#include "network/errors.h"
#include "network/http.h"


int main()
{
    try {
        Network::Http request("winamp.com");
        request.request();
        auto response = request.getResponse();
    } catch(Network::NetworkError e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
