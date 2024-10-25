#include "deribit_api.h"
#include <iostream>

int main() {
    try {
        DeribitAPI api;

        // Authenticate
        if (api.authenticate()) {
            std::cout << "Authenticated successfully." << std::endl;
        } else {
            std::cerr << "Failed to authenticate." << std::endl;
            return 1;
        }

        // Example: Place an order
        std::string order_id = api.placeOrder("BTC-PERPETUAL", "buy", 1, 10000);
        std::cout << "Placed Order ID: " << order_id << std::endl;

        // Example: Get orderbook
        std::string orderbook = api.getOrderBook("BTC-PERPETUAL");
        std::cout << "Orderbook: " << orderbook << std::endl;

        // Example: Cancel the order
        api.cancelOrder(order_id);
        std::cout << "Canceled Order ID: " << order_id << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
