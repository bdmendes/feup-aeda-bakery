//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "person.h"
#include "order.h"
#include <exception/person_exception.h>
#include <exception/store_exception.h>
#include <exception/product_exception.h>

#include "product.h"

class Person;
class Client;
class Worker;

class StoreHasNoWorkers;
class Order;

class Store {
public:
    explicit Store(std::string name);
    std::string getName() const;
    float getMeanEvaluation() const;
    std::vector<Order> getOrders() const;
    std::vector<Order*> getClientOrders(const Client& client);
    std::vector<Order*> getWorkerOrders(const Worker& worker);
    bool hasWorker(const std::string& name) const;
    bool hasWorker(int tributaryNumber) const;
    bool hasWorker(const Worker* worker) const;
    bool hasClient(const std::string& name) const;
    bool hasClient(int tributaryNumber) const;
    bool hasClient(const Client* client) const;
    void addClient(const Client* client);
    void removeClient(const Client* client);
    bool hasProduct(const Product* product) const;
    void hireWorker(Worker* worker);
    void fireWorker(const Worker* worker);
    void addOrder(const std::map<Product*, unsigned>& _products, Client& client);
    void changeWorkerSalary(Worker* worker, float salary) const;
    bool operator== (const std::string& name) const;
    void addProduct(const Product* product);
    void removeProduct(const Product* product);

private:
    Worker* getAvailableWorker();
    const std::string _name;
    std::vector<const Client*> _clients;
    std::vector<Worker*> _workers;
    std::vector<Order> _orders;
    std::vector<float> _clientEvaluations;
    std::vector<const Product*> _allProducts;
};

#endif //SRC_STORE_H