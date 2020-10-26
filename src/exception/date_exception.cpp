//
// Created by laimi on 22/10/2020.
//

#include "date_exception.h"

InvalidDate::InvalidDate(const std::string &message) : std::logic_error(message), _message(message){}

std::ostream &InvalidDate::operator<<(std::ostream &out) {
    out<<_message<<'\n';
    return out;
}
