//
// Created by bdmendes on 27/10/20.
//

#ifndef FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H
#define FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H

#include <stdexcept>

#include "model/person/person.h"
#include "model/date/date.h"
#include "model/person/client/client.h"
#include "model/person/worker/worker.h"

class OrderWasAlreadyDelivered : public std::logic_error{
public:
    OrderWasAlreadyDelivered(const Client& client, const Worker& worker, const Date& date);
};

class OrderWasNotDeliveredYet: public std::logic_error{
public:
    OrderWasNotDeliveredYet(const Client& client, const Worker& worker, const Date& date);
};

class OrderDoesNotExist : public std::invalid_argument{
public:
    OrderDoesNotExist();
};

class InvalidOrderEvaluation : public std::invalid_argument{
public:
    InvalidOrderEvaluation(int evaluation, const Client& client);
};

class InvalidOrderPosition : public std::invalid_argument{
public:
    InvalidOrderPosition(unsigned position, unsigned long size);
};

#endif //FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H
