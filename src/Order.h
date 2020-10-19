//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_ORDER_H
#define SRC_ORDER_H

#include <utility>
#include <vector>

#include "Product.h"

class Order {
public:
    Order(std::map<Product, unsigned int>& elements);
    float getTotalPrice() const;
    std::map<Product, unsigned int> getElements() const;
private:
    std::map<Product, unsigned int> _elements;
    float _totalPrice;
    //date
    //worker
};


#endif //SRC_ORDER_H
