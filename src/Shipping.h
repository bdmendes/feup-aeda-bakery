//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_SHIPPING_H
#define SRC_SHIPPING_H

#include <utility>
#include <vector>

#include "Person.h"
#include "Product.h"

class Shipping {
public:
    Shipping(const std::vector<std::pair<const Product&, unsigned>> &products,
             Client& client, Worker& worker);
private:
    std::vector<std::pair<const Product&, unsigned>> _products;
    float _totalPrice;
    Client& _client;
    Worker& _worker;
    float clientEvaluation;
};


#endif //SRC_SHIPPING_H
