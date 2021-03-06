#pragma once
#include <string>


namespace Network {
    
    enum SOCK_TYPE {
        TCP,
        UDP
    };

    class BaseSocket {
        protected:
            bool _socketOpen = false;

        public:
            BaseSocket() = default;
            BaseSocket(const BaseSocket&) = default;
            BaseSocket(BaseSocket&&) = default;

            BaseSocket& operator=(const BaseSocket&) = default;
            BaseSocket& operator=(BaseSocket&&) = default;

            bool isOpen() const { return _socketOpen; }

            virtual ~BaseSocket() {};

            virtual void connectSocket(const std::string&, const std::string&) = 0;
            virtual void closeSocket() = 0;

            virtual void send(const std::string&) const = 0;
            virtual std::string recv() const = 0;
    };

}
