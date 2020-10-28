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
class Order;

class ClientManager {
public:
    ClientManager();
    bool has(Client* client) const;
    Client* get(unsigned position);
    std::vector<Client*> getAll();
    void add(Client* client);
    void remove(Client* client);
    void remove(unsigned position);
    void read(std::ifstream& file);
    void write(std::ofstream& file);
private:
    std::vector<Client*> _clients;
};

class WorkerManager {
public:
    WorkerManager();
    bool has(Worker* client) const;
    Worker* get(unsigned position);
    Worker* getAvailable();
    std::vector<Worker*> getAll();
    void changeSalary(unsigned position, float salary);
    void add(Worker* worker);
    void remove(Worker* worker);
    void remove(unsigned position);
    void read(std::ifstream& file);
    void write(std::ofstream& file);
private:
    std::vector<Worker*> _workers;
};

class ProductManager {
public:
    ProductManager();
    bool has(Product* product) const;
    Product* get(unsigned position);
    void add(Product* product);
    void remove(Product* product);
    void read(std::ifstream& file);
    void write(std::ofstream& file) const;
private:
    std::vector<Product*> _stock;
};

class OrderManager {
public:
    OrderManager(ProductManager& pm, ClientManager& cm, WorkerManager& wm);
    bool has(Order* order) const;
    Order* add(Client* client);
    Order* get(unsigned position);
    std::vector<Order*> getAll() const;
    std::vector<Order*> get(Client* client);
    std::vector<Order*> get(Worker* worker);
    void remove(Order* order);

    void addProduct(Order* order, Product* product, unsigned quantity = 1);
    void removeProduct(Order* order, Product* product, unsigned quantity);
    void removeProduct(Order* order, Product* product);
    void removeProduct(Order* order, unsigned position, unsigned quantity);
    void removeProduct(Order* order, unsigned position);
    void deliver(Order* order, float clientEvaluation);

    void read(std::ifstream& file);
    void write(std::ofstream& file) const;
private:
    ProductManager& _productManager;
    ClientManager& _clientManager;
    WorkerManager& _workerManager;
    std::vector<Order*> _orders;
};

class Store {
public:
    explicit Store(std::string name);
    std::string getName() const;
    std::string setName(std::string name);
    float getEvaluation() const;

    ProductManager productManager;
    ClientManager clientManager;
    WorkerManager workerManager;
    OrderManager orderManager;
private:
    std::string _name;
};

#endif //SRC_STORE_H