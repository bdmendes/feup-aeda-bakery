//
// Created by laimi on 22/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H
#define FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H

#include <stdexcept>
#include "model/date/date.h"

class InvalidDate : public std::logic_error{
public:
    InvalidDate(const std::string& completeDate);
};

#endif //FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H
