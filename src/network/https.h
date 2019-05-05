#pragma once
#include "request.h"
#include <memory>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>


namespace Network {


    class Https : public Request {
        private:
            SSL_CTX* _ctx;
            SSL* _ssl;
            BIO* _bio;

            const std::string getErrorMessage() const;

        public:
            Https(const std::string& url) : Request(url) {
                SSL_load_error_strings();
                ERR_load_crypto_strings();
                _ctx = SSL_CTX_new(SSLv23_client_method());
            };

            ~Https() {
                BIO_free_all(_bio);
            };

            void request() override;
    };
}
