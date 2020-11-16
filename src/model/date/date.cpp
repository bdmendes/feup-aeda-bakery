//
// Created by bdmendes on 21/10/20.
//

#include "date.h"
#include <iomanip>
#include <sstream>

Date::Date() : _time(){
    std::time_t t = std::time(nullptr);
    localtime_r(&t, &_time);
}

Date::Date(int day, int month, int year, int hour, int minute) :
    _time(){
    _time.tm_hour = hour;
    _time.tm_min = minute;
    _time.tm_year = year - 1900;
    _time.tm_mon = month - 1;
    _time.tm_mday = day;
    _time.tm_isdst = -1; // determine daylight saving flag
    if (!isValid()) throw InvalidDate(getCompleteDate());
}

bool Date::isLeapYear(unsigned year) {
    return ((year%4==0 && year%100!=0) || (year%400==0));
}

std::string Date::getCalendarDay() const {
    std::ostringstream os;
    os << std::right << std::setfill('0') << std::setw(2) << getDay()
    << '/' << std::setw(2) << getMonth() <<
    '/' << std::setw(4) << getYear();
    return os.str();
}

std::string Date::getClockTime() const {
    std::ostringstream os;
    os << std::right << std::setfill('0') << std::setw(2) << getHour()
       << ':' << std::setw(2) << getMinute();
    return os.str();
}

std::string Date::getCompleteDate() const {
    return getCalendarDay() + " " + getClockTime();
}

bool Date::operator==(const Date &d2) const {
    return getCompleteDate() == d2.getCompleteDate();
}

bool Date::operator<(const Date &d2) const {
    return getCompleteDate() < d2.getCompleteDate();
}


bool Date::isValid() const {
    if (getHour()>=24 || getMinute()>=60 || getDay()>31 || getMonth() > 12) return false;
    switch(getMonth()){
        case 4: case 6: case 9: case 11:
            return getDay()<=30;
        case 2:
            return isLeapYear(getYear()) ? getDay()<=29 : getDay()<=28;
    }
    return true;
}

void Date::addDays(int days) {
    _time.tm_mday += days;
    std::time_t ntime = mktime(&_time);
    localtime_r(&ntime,&_time);
}

unsigned Date::getMonth() const {
    return _time.tm_mon + 1;
}

unsigned Date::getDay() const {
    return _time.tm_mday;
}

unsigned Date::getYear() const {
    return _time.tm_year + 1900;
}

unsigned Date::getHour() const {
    return _time.tm_hour;
}

unsigned Date::getMinute() const {
    return _time.tm_min;
}

void Date::addMinutes(int minutes) {
    _time.tm_min += minutes;
    std::time_t ntime = mktime(&_time);
    localtime_r(&ntime,&_time);
}

