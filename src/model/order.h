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

#include "person.h"
#include "product.h"

class Person;
class Client;
class Worker;

class Order {
public:
    Order(const std::map<Product*, unsigned int> &products, Client& client, Worker& worker);
    bool hasDiscount() const;
    Worker* getWorker() const;
    const Client* getClient() const;
    double getClientEvaluation() const;
    double getTotalPrice() const;
    void deliver(float clientEvaluation);
private:
    void calculateFinalPrice();
    void calculateDiscount();
    std::map<Product*, unsigned int> _products;
    double _totalPrice;
    Client& _client;
    Worker& _worker;
    double _clientEvaluation;
    bool _discount;
    bool _delivered;
};

#endif //SRC_ORDER_H
