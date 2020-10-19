//
// Created by laimi on 15/10/2020.
//

#include "Order.h"


Order::Order(std::map<Product, unsigned int>& elements) :
    _elements{elements}, _totalPrice(0){

}

float Order::getTotalPrice() const {
    return _totalPrice;
}

std::map<Product, unsigned int> Order::getElements() const {
    return _elements;
}



