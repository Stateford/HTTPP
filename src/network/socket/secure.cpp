#include "secure.h"
#include "../errors.h"
#include <openssl/bio.h>
#include <vector>
#include <algorithm>
#include <cstring>


namespace Network {

    SecureSocket::SecureSocket() {
        SSL_load_error_strings();
        ERR_load_crypto_strings();
        _ctx = SSL_CTX_new(SSLv23_client_method());
    }

    SecureSocket::SecureSocket(const SecureSocket& other) {
        this->_ssl = other._ssl;
        this->_ctx = other._ctx;
        if(this->_bio != nullptr || this->_bio != NULL)
            BIO_free_all(this->_bio);

        std::memcpy(this->_bio, &other._bio, sizeof(&this->_bio));
    }

    SecureSocket::SecureSocket(SecureSocket&& other) {
        this->_ssl = other._ssl;
        this->_ctx = other._ctx;

        if(this->_bio != nullptr || this->_bio != NULL)
            BIO_free_all(this->_bio);

        this->_bio = other._bio;
        other._bio = nullptr;
    }

    SecureSocket& SecureSocket::operator=(const SecureSocket& other) {
        if(&other == this)
            return *this;

        this->_ssl = other._ssl;
        this->_ctx = other._ctx;

        if(this->_bio != nullptr || this->_bio != NULL)
            BIO_free_all(this->_bio);

        std::memcpy(this->_bio, &other._bio, sizeof(&this->_bio));

        return *this;
    }

    SecureSocket& SecureSocket::operator=(SecureSocket&& other) {
        if(&other == this)
            return *this;

        this->_ssl = other._ssl;
        this->_ctx = other._ctx;

        if(this->_bio != nullptr || this->_bio != NULL)
            BIO_free_all(this->_bio);

        this->_bio = other._bio;
        other._bio = nullptr;

        return *this;
    }

    SecureSocket::~SecureSocket() {
        BIO_free_all(_bio);
    }

    void SecureSocket::connectSocket(const std::string& hostname, const std::string& port) {
        _socketOpen = true;
        _bio = BIO_new_ssl_connect(_ctx);

        BIO_get_ssl(_bio, &_ssl);
        SSL_set_mode(_ssl, SSL_MODE_AUTO_RETRY);

        const std::string HOST = hostname + ":" + port;

        BIO_set_conn_hostname(_bio, HOST.c_str());

        if(BIO_do_connect(_bio) <= 0) {
            const std::string errorMessage = getErrorMessage();
            throw NetworkError(errorMessage);
        }
    }

    void SecureSocket::closeSocket() {
        // TODO: set close socket
    }

    void SecureSocket::send(const std::string& message) const {
        if(BIO_puts(_bio, &message[0]) <= 0) {
            const std::string errorMessage = getErrorMessage();
            throw NetworkError(errorMessage);
        }
    }

    std::string SecureSocket::recv() const {
        std::string response;
        response.reserve(5000);
        int recvBytes = 0;

        do {
            std::vector<char> buffer(2048);

            recvBytes = BIO_read(_bio, &buffer[0], buffer.capacity());

            if(recvBytes > 0)
                response += std::string(buffer.begin(), buffer.begin() + recvBytes);
            else if(recvBytes < 0) {
                if(!BIO_should_retry(_bio)) {
                    const std::string errorMessage = getErrorMessage();
                    throw NetworkError(errorMessage);
                }
            }
        } while(recvBytes >0);

        return response;
    }

    const std::string SecureSocket::getErrorMessage() const {
        const unsigned long err = ERR_get_error();
        std::string errorMessage;
        errorMessage.reserve(256);
        ERR_error_string_n(err, &errorMessage[0], errorMessage.capacity());
        return errorMessage;
    }
}
