//
// Created by bdmendes on 21/10/20.
//

#ifndef FEUP_AEDA_PROJECT_DATE_H
#define FEUP_AEDA_PROJECT_DATE_H

#include <iostream>
#include <string>
#include <ctime>

#include "exception/date_exception.h"

class Date{
public:
    Date();
    Date(int day, int month, int year, int hour = 0, int minute = 0);

    static bool isLeapYear(unsigned year);

    unsigned getDay() const;
    unsigned getMonth() const;
    unsigned getYear() const;
    unsigned getHour() const;
    unsigned getMinute() const;

    std::string getCalendarDay() const;
    std::string getClockTime() const;
    std::string getCompleteDate() const;

    void addDays(int days);
    void addMinutes(int minutes);

    bool operator==(const Date& d2) const;
    bool operator<(const Date& d2) const;

private:
    bool isValid() const;
    std::tm _time;
};

#endif //FEUP_AEDA_PROJECT_DATE_H
