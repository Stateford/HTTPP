// cookie.cpp
#include "cookie.h"
#include "../../utils/split.h"
#include <algorithm>


namespace Network {

    const std::string Cookie::_cookieInfo[Cookie::COOKIE_INFO_COUNT] = {
        "expires",
        "max-age",
        "domain",
        "path",
        "secure",
        "httponly",
        "secure",
        "samesite"
    };

    bool Cookie::isCookieInfo(const std::string& headerValue)
    {
        auto data = Utils::splitKeyValue(headerValue);

        if(data.key.empty())
            data.key = headerValue;

        std::transform(data.key.begin(), data.key.end(), data.key.begin(), [](unsigned char c){ return std::tolower(c); });

        for(size_t i = 0; i < Cookie::COOKIE_INFO_COUNT; i++)
        {
            if(data.key == Cookie::_cookieInfo[i]) {
                return true;
            }
        }
        return false;
    }

    std::string Cookie::getKey() const
    {
        return _key;
    }

    std::string Cookie::getValue() const
    {
        return _value;
    }

    std::string Cookie::getExpires() const
    {
        return _expires;
    }

    std::string Cookie::getMaxAge() const
    {
        return _maxAge;
    }

    std::string Cookie::getDomain() const
    {
        return _domain;
    }

    std::string Cookie::getPath() const
    {
        return _path;
    }

    bool Cookie::getSecure() const
    {
        return _secure;
    }

    bool Cookie::getHttpOnly() const
    {
        return _httpOnly;
    }

    SAMESITE Cookie::getSameSite() const
    {
        return _sameSite;
    }

    void Cookie::setDomain(const std::string& domain)
    {
        _domain = domain;
    }

    void Cookie::setPath(const std::string& path)
    {
        _path = path;
    }

    void Cookie::setSameSite(const SAMESITE& value) 
    {
        _sameSite = value;
    }

    void Cookie::setSameSite(const std::string& value) 
    {
        std::string lowerValue = Utils::toLower(value);
        
        if(lowerValue == "strict")
            _sameSite = SAMESITE::STRICT;
        else if(lowerValue == "lax")
            _sameSite = SAMESITE::LAX;
        else
            _sameSite = SAMESITE::NONE;
    }

    std::string Cookie::toString() const
    {
        return _key + "=" + _value;
    }

    Cookie Cookie::fromHeader(const std::string& header, const std::string& domain)
    {
        Cookie cookie;

        std::vector<std::string> cookieData = Utils::splitString(header, "; ");

        cookie._domain = domain;

        for(const std::string& data : cookieData)
        {
            if(Cookie::isCookieInfo(data))
            {
                const std::string lowerData = Utils::toLower(data);
                if(data == "secure")
                    cookie._secure = true;
                else if(data == "httponly")
                    cookie._httpOnly = true;
                else
                {
                    auto valuePair = Utils::splitKeyValue(data);
                    std::string lowerKey = Utils::toLower(valuePair.key);

                    if(lowerKey == "expires")
                        cookie._expires = valuePair.value;
                    else if(lowerKey == "max-age")
                        cookie._maxAge = valuePair.value;
                    else if(lowerKey == "domain")
                        cookie._domain = valuePair.value;
                    else if(lowerKey == "path")
                        cookie._path = valuePair.value;
                    else if(lowerKey == "samesite")
                        cookie.setSameSite(valuePair.value);
                }
            }
            else
            {
                auto valuePair = Utils::splitKeyValue(data);
                cookie._key = valuePair.key;
                cookie._value = valuePair.value;
            }
        }

        return cookie;
    }
}
