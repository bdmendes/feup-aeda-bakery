#include <iostream>

#include "Order.h"
#include "Store.h"
#include "Person.h"
#include "Product.h"

#include <iostream>

#include <map>


int main() {
    Product meatCake("Bolo com molho de carne", 1.20);
    Product hugeBread("aquele pão gostoso", 0.15);
    std::map<Product,unsigned> products;
    //products[meatCake] = 2;
    //products[hugeBread] = 3;
    //Order order(products);

    std::cout << "ta a tchober tchouricas";

    return 0;
}

