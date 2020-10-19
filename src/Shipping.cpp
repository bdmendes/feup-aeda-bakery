//
// Created by laimi on 15/10/2020.
//

#include "Shipping.h"

Shipping::Shipping(const std::vector<std::pair<const Product &, unsigned int>> &products, Client &client, Worker &worker) :
    _products{std::vector<std::pair<const Product &, unsigned int>>()},
    _client{client}, _worker(worker) {

}
