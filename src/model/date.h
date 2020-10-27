//
// Created by bdmendes on 21/10/20.
//

#ifndef FEUP_AEDA_PROJECT_DATE_H
#define FEUP_AEDA_PROJECT_DATE_H

#include <iostream>
#include <string>

#include "../exception/date_exception.h"

class Date{
public:
    Date();
    Date(unsigned day, unsigned month, unsigned year, unsigned hour = 0, unsigned minute = 0);
    bool operator==(const Date& d2) const;
    std::string getCompleteDate() const;
    std::string getCalendarDay() const;
    std::string getClockTime() const;
    static bool isLeapYear(unsigned year);
private:
    unsigned _minute, _hour, _day, _month, _year;
};

#endif //FEUP_AEDA_PROJECT_DATE_H
