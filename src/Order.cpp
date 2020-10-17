//
// Created by laimi on 15/10/2020.
//

#include "Order.h"


Order::Order(const std::vector<std::pair<const Product&, unsigned>> &elements) :
    _elements{elements}, _totalPrice(0){

}

float Order::getTotalPrice() const {
    return _totalPrice;
}

std::vector<std::pair<const Product&, unsigned>> Order::getElements() const {
    return _elements;
}



