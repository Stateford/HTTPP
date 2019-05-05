#include <iostream>
#include "network/errors.h"
#include "network/http.h"
#include "network/https.h"


int main()
{
    try {
        std::cout << "creating request object" << std::endl;
        Network::Https request("drudgereport.com");
        std::cout << "starting request" << std::endl;
        request.request();
        auto response = request.getResponse();
        std::cout << "REQUEST MADE SUCCESS: \n";
        std::cout << response.getContent() << std::endl;
    } catch(Network::NetworkError e) {
        std::cout << "ERROR" << std::endl;
        std::cout << e.what() << std::endl;
    }
    return 0;
}
