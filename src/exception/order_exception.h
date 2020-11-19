
#ifndef FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H
#define FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H

#include <stdexcept>

#include "model/person/person.h"
#include "model/date/date.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

/**
 * Class relative to the exception of an order that was already delivered.
 */
class OrderWasAlreadyDelivered : public std::logic_error{
public:
    /**
     * Creates a new OrderWasAlreadyDelivered exception object.
     *
     * @param client the client
     * @param worker the worker
     * @param date the date
     */
    OrderWasAlreadyDelivered(const Client& client, const Worker& worker, const Date& date);
};

/**
 * Class relative to the exception of an order that was not delivered yet.
 */
class OrderWasNotDeliveredYet: public std::logic_error{
public:
    /**
     * Creates a new OrderWasNotDeliveredYet exception objet.
     *
     * @param client the client
     * @param worker the worker
     * @param date the date
     */
    OrderWasNotDeliveredYet(const Client& client, const Worker& worker, const Date& date);
};

/**
 * Class relative to the exception of a nonexistent order.
 */
class OrderDoesNotExist : public std::invalid_argument{
public:
    /**
     * Creates a new OrderDoesNotExist exception object.
     */
    OrderDoesNotExist();
};

/**
 * Class relative to the exception of an invalid order evaluation.
 */
class InvalidOrderEvaluation : public std::invalid_argument{
public:
    /**
     * Creates a new InvalidOrderEvaluation exception object.
     *
     * @param evaluation the evaluation
     * @param client the client
     */
    InvalidOrderEvaluation(int evaluation, const Client& client);
};

/**
 * Class relative to the exception of an invalid order position on some list.
 */
class InvalidOrderPosition : public std::invalid_argument{
public:
    /**
     * Creates a new InvalidOrderPosition exception object.
     *
     * @param position the position
     * @param size the size of the orders list
     */
    InvalidOrderPosition(unsigned long position, unsigned long size);
};

#endif //FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H
