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
    std::string getLocation() const;
    float getMeanEvaluation() const;
    void hireWorker(Worker* worker);
    void fireWorker(const Worker* worker);
    void newOrder(const Order* order);
    void deliveredOrder(const Order* order);
    const Worker& assignWorker();
    void changeWorkerSalary(Worker *worker, float salary);
    static bool compareNumOrders(Worker* worker1, Worker* worker2);
private:
    const std::string _location;
    const Boss& _boss;
    std::vector<const Client*> _clients;
    std::vector<Worker*> _workers; //Workers are not const because the number of orders is going to change
    std::vector<const Order*> _orders;
    std::vector<float> _clientEvaluations;
};

class ClientDoesNotExist{
public:
    std::string _name;
    int _tributaryNumber;
    ClientDoesNotExist(std::string name, int tributaryNumber) :
            _name(name), _tributaryNumber(tributaryNumber){

    }
    std::ostream & operator<<(std::ostream &out)
    { out << "Client does not exist: " << _name << ", " << _tributaryNumber << std::endl; return out;}

};


class WorkerDoesNotExist{
public:
    std::string _name;
    int _tributaryNumber;
    WorkerDoesNotExist(std::string name, int tributaryNumber):
            _name(name), _tributaryNumber(tributaryNumber){

    }
    std::ostream & operator<<(std::ostream &out)
    { out << "Client does not exist: " << _name << ", " << _tributaryNumber << std::endl; return out;}
};


#endif //SRC_STORE_H
