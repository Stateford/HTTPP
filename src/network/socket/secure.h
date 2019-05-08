#pragma once
#include "baseSocket.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>


namespace Network {

    class SecureSocket : public BaseSocket {
        private:
            BIO* _bio;
            SSL* _ssl;
            SSL_CTX* _ctx;

            const std::string getErrorMessage() const;

        public:
            SecureSocket();
            SecureSocket(const SecureSocket&);
            SecureSocket(SecureSocket&&);

            ~SecureSocket();

            SecureSocket& operator=(const SecureSocket&);
            SecureSocket& operator=(SecureSocket&&);

            void connectSocket(const std::string&, const std::string&) override;
            void closeSocket() override;

            void send(const std::string&) const override;
            std::string recv() const override;
    };

}
