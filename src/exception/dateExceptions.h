//
// Created by laimi on 22/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H
#define FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H

#include <stdexcept>
#include "../model/date.h"

class InvalidDate : std::logic_error{
public:
    explicit InvalidDate(const std::string &message="This date is invalid");
    std::ostream & operator<<(std::ostream &out);
private:
    std::string _message;
};


#endif //FEUP_AEDA_PROJECT_DATEEXCEPTIONS_H
