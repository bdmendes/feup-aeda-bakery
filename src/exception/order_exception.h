//
// Created by bdmendes on 27/10/20.
//

#ifndef FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H
#define FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H

#include <stdexcept>

#include "model/person/person/person.h"
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

class InvalidOrderEvaluation : public std::invalid_argument{
public:
    InvalidOrderEvaluation(float evaluation, const Client& client);
};

#endif //FEUP_AEDA_PROJECT_ORDER_EXCEPTION_H
