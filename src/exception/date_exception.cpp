//
// Created by laimi on 22/10/2020.
//

#include "date_exception.h"

InvalidDate::InvalidDate(const std::string& completeDate) :
    std::logic_error(completeDate + " is not a valid date!\n"){
}
