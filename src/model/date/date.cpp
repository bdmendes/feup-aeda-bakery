//
// Created by bdmendes on 21/10/20.
//

#include "date.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Date::Date(){
    std::time_t t = std::time(nullptr);
    std::tm currentTime{};
    localtime_r(&t, &currentTime);
    _minute = currentTime.tm_min;
    _hour = currentTime.tm_hour;
    _day = currentTime.tm_mday;
    _month = currentTime.tm_mon + 1;
    _year = currentTime.tm_year + 1900;
}

Date::Date(unsigned day, unsigned month, unsigned year, unsigned hour, unsigned minute) :
    _hour(hour), _minute(minute), _day(day), _month(month), _year(year){
    _str = getCompleteDate();
    if (!isValid()) throw InvalidDate(_str);
}

bool Date::isLeapYear(unsigned year) {
    return ((year%4==0 && year%100!=0) || (year%400==0));
}

std::string Date::getCalendarDay() const {
    std::ostringstream os;
    os << std::right << std::setfill('0') << std::setw(2) << _day
    << '/' << std::setw(2) << _month <<
    '/' << std::setw(4) << _year;
    return os.str();
}

std::string Date::getClockTime() const {
    std::ostringstream os;
    os << std::right << std::setfill('0') << std::setw(2) << _hour
       << ':' << std::setw(2) << _minute;
    return os.str();
}

std::string Date::getCompleteDate() const {
    return getCalendarDay() + " " + getClockTime();
}

bool Date::operator==(const Date &d2) const {
    return getCalendarDay() == d2.getCalendarDay();
}

bool Date::operator<(const Date &d2) const {
    return getCompleteDate() < d2.getCompleteDate();
}


bool Date::isValid() const {
    if (_hour>=24 || _minute>=60 || _day>31 || _month > 12) return false;
    switch(_month){
        case 4: case 6: case 9: case 11:
            return _day<=30;
        case 2:
            return isLeapYear(_year) ? _day<=29 : _day<=28;
    }
    return true;
}

