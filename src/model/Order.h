//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_ORDER_H
#define SRC_ORDER_H

#include <utility>
#include <vector>
#include <ctime>
#include <iostream>
#include <map>

#include "Person.h"
#include "Product.h"

class Order {
public:
    Order(const std::map<Product, unsigned int> &products, Client& client, Worker& worker);
    bool hasDiscount() const;
    Worker* getWorker() const;
    const Client* getClient() const;
    float getClientEvaluation() const ;
    float getTotalPrice() const;
    float calculateFinalPrice();
    void deliverOrder(float clientEvaluation);
    void obtainClientEvaluation(float evaluation);
private:
    std::map<Product, unsigned int> _products;
    float _totalPrice;
    Client& _client;
    Worker& _worker;
    float _clientEvaluation;
    bool _discount;
    bool _delivered;
};

#endif //SRC_ORDER_H
