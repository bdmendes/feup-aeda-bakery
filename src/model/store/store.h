//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "model/person/person.h"
#include "model/person/boss/boss.h"
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

    void setName(const std::string& name);
    std::string getName() const;
    int getEvaluation() const;
    float getProfit() const;

    std::string read(const std::string& dataFolderPath, bool doReset);
    std::string write(const std::string& dataFolderPath);

    void reset();

    ProductManager productManager;
    ClientManager clientManager;
    WorkerManager workerManager;
    OrderManager orderManager;
    Boss boss;
private:
    std::string _name;
};

#endif //SRC_STORE_H