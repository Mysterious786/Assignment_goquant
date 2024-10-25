#ifndef DERIBIT_API_H
#define DERIBIT_API_H

#include <string>
#include "http_client.h"

class DeribitAPI {
public:
    DeribitAPI();
    bool authenticate();
    std::string placeOrder(const std::string& instrument_name, const std::string& side, int amount, double price);
    std::string getOrderBook(const std::string& instrument_name);
    bool cancelOrder(const std::string& order_id);

private:
    std::string client_id;
    std::string client_secret;
    std::string access_token;
    HttpClient http_client;

    void loadCredentials();
};

#endif // DERIBIT_API_H
