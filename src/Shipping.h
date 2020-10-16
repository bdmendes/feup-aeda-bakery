//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_SHIPPING_H
#define SRC_SHIPPING_H

#include <utility>
#include <vector>

#include "Product.h"

class Shipping {
public:
    Shipping(const std::vector<std::pair<const Product&, unsigned>> &elements);
private:
    std::vector<std::pair<const Product&, unsigned>> _elements;
    float _totalPrice;
    //date
    //worker
};


#endif //SRC_SHIPPING_H
