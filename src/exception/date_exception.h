//
// Created by laimi on 22/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H
#define FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H

#include <stdexcept>
#include "../model/date.h"

class InvalidDate : std::logic_error{
public:
    InvalidDate(const std::string& completeDate);
    virtual const char* what() const noexcept;
private:
    std::string _message;
};


#endif //FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H
