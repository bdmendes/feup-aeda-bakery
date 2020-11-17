//
// Created by bdmendes on 27/10/20.
//

#include "order_exception.h"

OrderWasAlreadyDelivered::OrderWasAlreadyDelivered(const Client &client, const Worker &worker, const Date &date):
    std::logic_error("The order, requested by " + client.getName() + " on " + date.getCalendarDay() + ", was already delivered by " + worker.getName() + "!"){
}

OrderWasNotDeliveredYet::OrderWasNotDeliveredYet(const Client &client, const Worker &worker, const Date &date) :
    std::logic_error("The order, requested by " + client.getName() + " on " + date.getCalendarDay() + ", was not yet delivered by " + worker.getName() + "!"){
}

OrderDoesNotExist::OrderDoesNotExist() :
    std::invalid_argument("Order does not exist!"){
}

InvalidOrderEvaluation::InvalidOrderEvaluation(int evaluation, const Client &client):
        std::invalid_argument(client.getName() + " gave an invalid evaluation of " + std::to_string(evaluation) + " to this order; should be between 0 and 5!"){
}

InvalidOrderPosition::InvalidOrderPosition(unsigned int position, unsigned size) :
    std::invalid_argument(std::to_string(++position) + " is an invalid position; should be between 1 and " + std::to_string(size) + "!"){}

