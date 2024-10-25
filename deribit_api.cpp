#include "deribit_api.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

using json = nlohmann::json;

DeribitAPI::DeribitAPI() {
    loadCredentials();
}

void DeribitAPI::loadCredentials() {
    // Load credentials from environment variables or config file
    const char* env_client_id = std::getenv("DERIBIT_CLIENT_ID");
    const char* env_client_secret = std::getenv("DERIBIT_CLIENT_SECRET");

    if (env_client_id && env_client_secret) {
        client_id = std::string(env_client_id);
        client_secret = std::string(env_client_secret);
    } else {
        std::ifstream config_file("config.json");
        if (config_file.is_open()) {
            json config;
            config_file >> config;
            client_id = config["client_id"].get<std::string>();
            client_secret = config["client_secret"].get<std::string>();
        }
    }
}

bool DeribitAPI::authenticate() {
    std::string url = "https://test.deribit.com/api/v2/public/auth";
    std::string data = "grant_type=client_credentials&client_id=" + client_id + "&client_secret=" + client_secret;

    std::string response = http_client.post(url, data);
    auto response_json = json::parse(response);

    if (response_json.contains("result")) {
        access_token = response_json["result"]["access_token"];
        return true;
    }
    return false;
}

std::string DeribitAPI::placeOrder(const std::string& instrument_name, const std::string& side, int amount, double price) {
    std::string url = "https://test.deribit.com/api/v2/private/buy";
    std::string data = "instrument_name=" + instrument_name + "&amount=" + std::to_string(amount) + "&price=" + std::to_string(price);

    std::string response = http_client.post(url + "?access_token=" + access_token, data);
    auto response_json = json::parse(response);
    return response_json["result"]["order_id"];
}

std::string DeribitAPI::getOrderBook(const std::string& instrument_name) {
    std::string url = "https://test.deribit.com/api/v2/public/get_order_book?instrument_name=" + instrument_name;
    std::string response = http_client.get(url);
    return response;
}

bool DeribitAPI::cancelOrder(const std::string& order_id) {
    std::string url = "https://test.deribit.com/api/v2/private/cancel";
    std::string data = "order_id=" + order_id;
    std::string response = http_client.post(url + "?access_token=" + access_token, data);
    return true; 
}
