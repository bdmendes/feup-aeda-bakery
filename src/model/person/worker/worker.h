//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_WORKER_H
#define FEUP_AEDA_PROJECT_WORKER_H

#include "../person/person.h"

#include <string>

class Worker : public Person{
public:
    Worker(std::string name, int tributaryNumber = DEFAULT_TAXID, float salary=0,
           Credential credential = {"worker", "worker"});

    float getSalary() const;
    unsigned getOrders() const;

    void setSalary(float salary);

    void addOrder();
    void removeOrder();

    void write(std::ostream& os);

    //bool operator==(const Worker& w2) const;
private:
    float _salary;
    unsigned _orders;
};


#endif //FEUP_AEDA_PROJECT_WORKER_H
