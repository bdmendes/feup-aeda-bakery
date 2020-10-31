//
// Created by bdmendes on 21/10/20.
//

#ifndef FEUP_AEDA_PROJECT_DATE_H
#define FEUP_AEDA_PROJECT_DATE_H

#include <iostream>
#include <string>

#include "exception/date_exception.h"

class Date{
public:
    Date();
    Date(unsigned day, unsigned month, unsigned year, unsigned hour = 0, unsigned minute = 0);

    static bool isLeapYear(unsigned year);

    std::string getCalendarDay() const;
    std::string getClockTime() const;
    std::string getCompleteDate() const;

    bool operator==(const Date& d2) const;
private:
    bool isValid() const;
    std::string _str;
    unsigned _minute, _hour, _day, _month, _year;
};

#endif //FEUP_AEDA_PROJECT_DATE_H
