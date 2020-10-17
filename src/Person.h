//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PERSON_H
#define SRC_PERSON_H

#include <string>
#include <vector>
#include <map>

#include "Order.h"
#include "Store.h"

class Person {
public:
    Person(const std::string &name, int tributaryNumber);
    Person()=default;
    std::string getName() const;
    int getTributaryNumber() const;
<<<<<<< Updated upstream
private:
    std::string _name;
    int _tributaryNumber;
=======
    std::vector<const Order*> getOrders();
    virtual void addOrder(const Order* order);
    bool removeOrder(const Order* order);
private:
    std::string _name;
    int _tributaryNumber;
protected:
    std::vector<const Order*> _orders;
>>>>>>> Stashed changes
};

class Store;

class Client : public Person {
public:
    Client(const std::string &name, int tributaryNumber, bool premium);
    Client()=default;
    std::string getName() const;
    int getTributaryName() const;
    bool isPremium() const;
    unsigned getPoints() const;
<<<<<<< Updated upstream
=======
    void addOrder(const Order* order) override;
    float getMeanEvaluation() const;
    std::vector<float> getEvaluations() const;
>>>>>>> Stashed changes
private:
    bool _premium;
    unsigned _points;
    std::map<const Store*, float> _evaluation;
    std::map<const Store*, std::vector<const Shipping*>> _orders;
};

class Worker : public Person{
public:
    Worker(const std::string &name, int tributaryNumber, float salary);
    Worker()=default;
private:
    float _salary;
    std::vector<const Shipping*> _shippings;
};

#endif //SRC_PERSON_H
