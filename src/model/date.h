//
// Created by bdmendes on 21/10/20.
//

#ifndef FEUP_AEDA_PROJECT_DATE_H
#define FEUP_AEDA_PROJECT_DATE_H

#include <iostream>

#include "../exception/date_exception.h"

class Date{
public:
    Date();
    Date(unsigned hour, unsigned minute, unsigned day, unsigned month, unsigned year);
    std::ostream& operator<<(std::ostream & out) const;
private:
    bool isLeapYear() const;
    unsigned _minute, _hour, _day, _month, _year;
};


#endif //FEUP_AEDA_PROJECT_DATE_H
