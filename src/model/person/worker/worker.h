
#ifndef FEUP_AEDA_PROJECT_WORKER_H
#define FEUP_AEDA_PROJECT_WORKER_H

#include "model/person/person.h"

#include <string>
#include <vector>

/**
 * Class relative to a store worker.
 */
class Worker : public Person{
public:
  
    /**
     * Creates a new Worker object.
     *
     * @param name the name
     * @param salary the salary
     * @param taxID the taxpayer identification number
     * @param credential the login credentials
     */
    explicit Worker(std::string name, unsigned long taxID = DEFAULT_TAX_ID, float salary = DEFAULT_SALARY,
                    Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD}, std::string location = DEFAULT_LOCATION);

    /**
     * Gets the worker salary.
     *
     * @return the salary
     */
    float getSalary() const;

    /**
     * Gets the number of undelivered orders.
     *
     * @return the number of undelivered orders
     */
    unsigned getUndeliveredOrders() const;

    /**
     * Sets the worker salary.
     *
     * @param salary the salary
     */
    void setSalary(float salary);

    /**
     * Increases a value to the number of undelivered orders.
     */
    void addOrderToDeliver();

    /**
     * Decreases a value to the number of undelivered orders.
     */
    void removeOrderToDeliver();

    /**
     * Gets mean evaluation, given by a client, of the orders delivered by the worker.
     *
     * @return the order's mean evaluation
     */
    float getMeanEvaluation() const;

    /**
     * Adds an evaluation to the orders evaluations list.
     *
     * @param evaluation the evaluation
     */
    void addEvaluation (unsigned int evaluation);

    /**
     * Prints the worker data.
     *
     * @param os the output stream
     * @param showData if true, prints all data: name, taxpayer identification number, salary, number of undelivered
     * orders and orders' mean evaluation; otherwise, just prints the name, the taxpayer identification and the and log
     * status
     * number and log status
     */
    void print(std::ostream& os, bool showData = true);

    /**
     * Gets the worker default login credentials.
     *
     * @return the access  credentials
     */
    Credential getDefaultCredential() override;

    std::string getLocation() const;

    /**
     * The worker default login username.
     */
    static const char* DEFAULT_USERNAME;

    /**
     * The worker default login password.
     */
    static const char* DEFAULT_PASSWORD;

    /**
     * The worker default salary.
     */
    static const float DEFAULT_SALARY;

    static const char* DEFAULT_LOCATION;
private:
    /**
     * The number of undelivered orders by the worker.
     */
    unsigned _undeliveredOrders;

    /**
     * The worker salary.
     */
    float _salary;

    /**
     * The list of evaluations given to each order delivered by the worker.
     */
    std::vector<unsigned> _evaluations;
    std::string _location;
};


#endif //FEUP_AEDA_PROJECT_WORKER_H
