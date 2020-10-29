//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_WORKER_H
#define FEUP_AEDA_PROJECT_WORKER_H

#include "../person/person.h"

#include <string>

class Worker : public Person{
public:
    Worker(std::string name, float salary, int tributaryNumber = 999999999,
           Credential credential = {"worker", "worker"});
    unsigned getOrders() const;
    void addOrder();
    void removeOrder();
    void setSalary(float salary);
    float getSalary() const;
private:
    float _salary;
    unsigned _orders;
};


#endif //FEUP_AEDA_PROJECT_WORKER_H
