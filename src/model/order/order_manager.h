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
#include <vector>

class OrderManager {
public:
    OrderManager(ProductManager& pm, ClientManager& cm, WorkerManager& wm);
    bool has(Order* order) const;

    Order* get(unsigned position, Client* client = nullptr, Worker* worker = nullptr);
    std::vector<Order*> getAll() const;
    std::vector<Order*> get(Client* client) const;
    std::vector<Order*> get(Worker* worker) const;

    void sort();
    Order* add(Client* client, Date date = {});
    void remove(Order* order);
    void remove(unsigned position);

    void read(std::ifstream& file);
    bool print(std::ostream& os, Client* client = nullptr, Worker* worker = nullptr) const;

private:

    ProductManager& _productManager;
    ClientManager& _clientManager;
    WorkerManager& _workerManager;
    std::vector<Order*> _orders;
};

#endif //FEUP_AEDA_PROJECT_ORDER_MANAGER_H
