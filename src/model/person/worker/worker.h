//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_WORKER_H
#define FEUP_AEDA_PROJECT_WORKER_H

#include "model/person/person.h"

#include <string>

/**
 *
 */
class Worker : public Person{
public:
  
    /**
     * Creates a new worker.
     *
     * @param name the name
     * @param salary the salary
     * @param taxID the taxpayer identification number
     * @param credential the access credentials
     */
    Worker(std::string name, int taxID = DEFAULT_TAX_ID, float salary = DEFAULT_SALARY,
           Credential credential = {DEFAULT_USERNAME,DEFAULT_PASSWORD});

    /**
     * Gets the worker's salary.
     *
     * @return the salary
     */
    float getSalary() const;

    /**
     * Gets the list of undelivered orders.
     *
     * @return the list of undelivered orders
     */
    unsigned getUndeliveredOrders() const;

    /**
     * Sets the worker salary.
     *
     * @param salary the salary
     */
    void setSalary(float salary);

    /**
     * Adds order to the list of undelivered orders.
     */
    void addOrderToDeliver();

    /**
     *Removes order from the list of undelivered orders.
     */
    void removeOrderToDeliver();

    /**
     *Prints worker data.
     *
     * @param os the output stream
     * @param showData if true, prints all data: name, taxpayer identification number, subscription type and accumulated
     * points; otherwise, just prints the name and the taxpayer identification number.
     */
    void print(std::ostream& os, bool showData = true);

    /**
     * Gets the worker default access credentials.
     *
     * @return the access  credentials
     */
    Credential getDefaultCredential() override;

    /**
     * The default ac
     */
    static const char* DEFAULT_USERNAME;
    static const char* DEFAULT_PASSWORD;
    static const float DEFAULT_SALARY;
private:
    unsigned _undeliveredOrders;
    float _salary;
};


#endif //FEUP_AEDA_PROJECT_WORKER_H
