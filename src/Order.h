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
    Order(const std::vector<std::pair<const Product&, unsigned>> &elements);
    float getTotalPrice() const;
    std::vector<std::pair<const Product&, unsigned>> getElements() const;
private:
    std::vector<std::pair<const Product&, unsigned>> _elements;
    float _totalPrice;
    //date
    //worker
};


#endif //SRC_ORDER_H
