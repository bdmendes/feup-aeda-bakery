//
// Created by laimi on 22/10/2020.
//

#include "date_exception.h"

InvalidDate::InvalidDate(const std::string &completeDate) : _message(completeDate + " is not a valid date"),
    std::logic_error(_message){
}

const char *InvalidDate::what() const noexcept{
    return _message.c_str();
}
