//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>

#include "Person.h"

class Client;
class Worker;

class Store {
public:
    Store(const std::string &location);
    std::string getLocation() const;
    std::vector<const Client*> getClients() const;
    float getEvaluation() const;
    std::vector<const Worker*> getWorkers() const;
    //void newOrder(const Client* client, const Product* product, const Order* order);
private:
    const std::string _location;
    std::vector<const Client*> _clients;
    float _evaluation;
    std::vector<const Worker*> _workers;
};


#endif //SRC_STORE_H
