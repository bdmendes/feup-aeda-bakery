//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_ORDER_MANAGER_H
#define FEUP_AEDA_PROJECT_ORDER_MANAGER_H

#include "order.h"

#include <model/product/product_manager.h>
#include <model/person/client/client_manager.h>
#include <model/person/worker/worker_manager.h>

#include <exception/person_exception.h>

#include <algorithm>

struct OrderSmaller{
    bool operator()(const Order* o1, const Order* o2) const{
        return o1 < o2;
    }
};

class OrderManager {
public:
    OrderManager(ProductManager& pm, ClientManager& cm, WorkerManager& wm);
    bool has(Order* order) const;

    Order* get(unsigned position);
    std::set<Order*, OrderSmaller> getAll() const;
    std::set<Order*, OrderSmaller> get(Client* client);
    std::set<Order*, OrderSmaller> get(Worker* worker);

    Order* add(Client* client);
    Order* remove(Order* order);

    void read(std::ifstream& file);
    void write(std::ofstream& file) const;

private:
    ProductManager& _productManager;
    ClientManager& _clientManager;
    WorkerManager& _workerManager;
    std::set<Order*, OrderSmaller> _orders;
};

#endif //FEUP_AEDA_PROJECT_ORDER_MANAGER_H
