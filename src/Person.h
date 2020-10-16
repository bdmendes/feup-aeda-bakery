//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PERSON_H
#define SRC_PERSON_H

#include <string>
#include <vector>
#include <map>

#include "Shipping.h"
#include "Store.h"

class Person {
public:
    Person(std::string name, int tributaryNumber);
    std::string getName() const;
    int getTributaryNumber() const;
    std::vector<const Shipping*> getOrders();
    virtual void addOrder(const Shipping* order);
    bool removeOrder(const Shipping* order);
private:
    std::string _name;
    int _tributaryNumber;
protected:
    std::vector<const Shipping*> _orders;
};

class Store;

class Client : public Person {
public:
    Client(std::string name, int tributaryNumber, bool premium);
    bool isPremium() const;
    unsigned getPoints() const;
    void addOrder(const Shipping* order) override;
    float getMeanEvaluation() const;
    std::vector<float> getEvaluations() const;
private:
    bool _premium;
    unsigned _points;
    std::vector<float> _evaluations;
};

class Worker : public Person{
public:
    Worker(std::string name, int tributaryNumber, float salary);
private:
    float _salary;
};

#endif //SRC_PERSON_H
