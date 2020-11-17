//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_WORKER_H
#define FEUP_AEDA_PROJECT_WORKER_H

#include "model/person/person.h"

#include <string>

class Worker : public Person{
public:
    Worker(std::string name, float salary, int taxID = Person::DEFAULT_TAX_ID,
           Credential credential = {DEFAULT_USERNAME,DEFAULT_PASSWORD});

    float getSalary() const;
    unsigned getUndeliveredOrders() const;

    void setSalary(float salary);

    void addOrderToDeliver();
    void removeOrderToDeliver();

    void print(std::ostream& os, bool showData = true);

    Credential getDefaultCredential() override;
    static const char* DEFAULT_USERNAME;
    static const char* DEFAULT_PASSWORD;
private:
    unsigned _undeliveredOrders;
    float _salary;
};


#endif //FEUP_AEDA_PROJECT_WORKER_H
