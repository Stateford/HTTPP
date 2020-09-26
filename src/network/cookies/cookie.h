#pragma once
#include <string>
#include <chrono>
#include <vector>


namespace Network {

    enum class SAMESITE
    {
        STRICT,
        LAX,
        NONE
    };

    class Cookie
    {
        private:
            static constexpr size_t COOKIE_INFO_COUNT = 8;
            static const std::string _cookieInfo[COOKIE_INFO_COUNT];
            static bool isCookieInfo(const std::string& headerValue);

            std::string _key;
            std::string _value;

            std::string _expires;
            std::string _maxAge;
            std::string _domain;
            std::string _path;
            bool _secure = false;
            bool _httpOnly = false;
            SAMESITE _sameSite = SAMESITE::NONE;

        public:
            Cookie() noexcept = default;

            std::string getKey() const;
            std::string getValue() const;
            std::string getExpires() const;
            std::string getMaxAge() const;
            std::string getDomain() const;
            std::string getPath() const;
            bool getSecure() const;
            bool getHttpOnly() const;
            SAMESITE getSameSite() const;

            void setDomain(const std::string& domain);
            void setPath(const std::string& path);
            void setSameSite(const SAMESITE& value);
            void setSameSite(const std::string& value);

            std::string toString() const;

            static Cookie fromHeader(const std::string& header, const std::string& domain);
    };
}
