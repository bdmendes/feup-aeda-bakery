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
    bool testDate();
private:
    bool isLeapYear(unsigned year);
    void testMonth();
    void testDay();
    void testHour();
    void testMinute();
    unsigned _minute, _hour, _day, _month, _year;
};


#endif //FEUP_AEDA_PROJECT_DATE_H
