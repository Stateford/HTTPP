#include "header.h"

namespace Network {

    Header::Header() {
        _setDefault();
    }

    Header::Header(const std::string& hostname) {
        _headers["Host"] = hostname;
        _setDefault();
    }
    
    void Header::_setDefault() {
        _headers["Connection"] = "Close";
    }

    void Header::setContentType(MimeType type) {
        switch(type) {
            case PLAIN:
                _headers["Content-Type"] = "text/plain";
                break;
            case CSV:
                _headers["Content-Type"] = "text/csv";
                break;
            case HTML:
                _headers["Content-Type"] = "text/html";
                break;
            case JSON:
                _headers["Content-Type"] = "text/json";
                break;
            default:
                break;
        }
    }

    bool Header::contains(const std::string& key) const {
        return _headers.find(key) != _headers.end();
    }

    std::string& Header::operator[](const std::string& key) {
        return _headers[key];
    }

    void Header::insert(const std::string& key, const std::string& value) {
        _headers[key] = value;
    }
}
