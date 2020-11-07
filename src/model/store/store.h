//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "model/person/person/person.h"
#include "model/order/order.h"
#include <exception/person_exception.h>
#include <exception/store_exception.h>
#include <exception/product_exception.h>

#include "model/product/product.h"

#include "../person/client/client_manager.h"
#include "../product/product_manager.h"
#include "../person/worker/worker_manager.h"
#include "../order/order_manager.h"

class Order;

class Store {
public:
    Store(std::string name = "Bakery Store");

    std::string getName() const;
    float getEvaluation() const;

    void setName(std::string name);

    ProductManager productManager;
    ClientManager clientManager;
    WorkerManager workerManager;
    OrderManager orderManager;
private:
    std::string _name;
};

#endif //SRC_STORE_H