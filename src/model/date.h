//
// Created by bdmendes on 21/10/20.
//

#ifndef FEUP_AEDA_PROJECT_DATE_H
#define FEUP_AEDA_PROJECT_DATE_H

#include <iostream>

class Date{
public:
    Date();
    std::ostream & operator<<(std::ostream & out) const;
private:
    unsigned _minute, _hour, _day, _month, _year;
};


#endif //FEUP_AEDA_PROJECT_DATE_H
