#include "https.h"
#include "errors.h"
#include <vector>


namespace Network {

    void Https::request() {
        _bio = BIO_new_ssl_connect(_ctx);

        BIO_get_ssl(_bio, &_ssl);
        SSL_set_mode(_ssl, SSL_MODE_AUTO_RETRY);

        const std::string hostname = _url->getHost() + ":443";
        std::cout << hostname << std::endl;

        BIO_set_conn_hostname(_bio, hostname.c_str());

        if(BIO_do_connect(_bio) <= 0) {
            std::string errorMessage = getErrorMessage();
            throw NetworkError(errorMessage);
        }

        const std::string httpPacket = createPacket();

        if(BIO_puts(_bio, &httpPacket[0]) <= 0) {
            std::string errorMessage = getErrorMessage();
            throw NetworkError(errorMessage);
        }
        
        std::string serverResponse;
        serverResponse.reserve(2048);
        int recvBytes = 0;
        do {
            std::vector<char> responseBuffer(2048);
            responseBuffer.reserve(2048);
            recvBytes = BIO_read(_bio, &responseBuffer[0], responseBuffer.capacity());

            if(recvBytes > 0)
                serverResponse += std::string(responseBuffer.begin(), responseBuffer.begin() + recvBytes);
            else if(recvBytes < 0) {
                if(!BIO_should_retry(_bio)) {
                    std::string errorMessage = getErrorMessage();
                    throw NetworkError(errorMessage);
                }
            }
        } while(recvBytes > 0);

        std::cout << serverResponse << std::endl;
        _response.parseResponse(serverResponse);
    }

    const std::string Https::getErrorMessage() const {
        const unsigned long err = ERR_get_error();
        std::string errorMessage;
        errorMessage.reserve(256);
        ERR_error_string_n(err, &errorMessage[0], errorMessage.capacity());
        return errorMessage;
    }
}
