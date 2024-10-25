#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

class HttpClient {
public:
    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& data);
};

#endif // HTTP_CLIENT_H
