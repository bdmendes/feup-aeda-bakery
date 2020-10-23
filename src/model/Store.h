//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "Person.h"
#include "Order.h"

class Store {
public:
    Store(std::string name);
    std::string getName() const;
    float getMeanEvaluation() const;

    void hireWorker(Worker* worker);
    void fireWorker(const Worker* worker);

    void addOrder(const std::map<Product, unsigned>& _products, Client& client);

    Worker* getAvailableWorker();
    void changeWorkerSalary(Worker *worker, float salary);

    bool operator== (const std::string& name){
        return getName() == name;
    }
private:
    const std::string _name;
    std::vector<const Client*> _clients;
    std::vector<Worker*> _workers; //Workers are not const because the number of orders is going to change
    std::vector<Order> _orders;
    std::vector<float> _clientEvaluations;
};

struct StoreComp {
    bool operator() (const Store* s1, const Store* s2) const {
        return s1->getName() < s2->getName();
    }
};

#endif //SRC_STORE_H