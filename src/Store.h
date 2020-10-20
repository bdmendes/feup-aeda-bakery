//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>
#include <algorithm>

#include "Person.h"
#include "Order.h"

class Client;
class Worker;
class Boss;

class Store {
public:
    Store(const std::string &location, const Boss& boss);
    float getMeanEvaluation() const;
    void hireWorker(Worker* worker);
    void fireWorker(const Worker* worker);
    void newOrder(const Order* order);
    void deliveredOrder(const Order* order);
    const Worker& assignWorker();
    void changeWorkerSalary(Worker *worker, float salary);
private:
    const std::string _location;
    const Boss& _boss;
    std::vector<const Client*> _clients;
    std::vector<Worker*> _workers; //Workers are not const because the number of orders is going to change
    std::vector<const Order*> _orders;
    std::vector<float> _clientEvaluations;
};


#endif //SRC_STORE_H
