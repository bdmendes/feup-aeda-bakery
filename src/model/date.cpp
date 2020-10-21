//
// Created by bdmendes on 21/10/20.
//

#include "date.h"
#include <ctime>

Date::Date(){
    std::time_t t = std::time(nullptr);
    std::tm currentTime{};
    localtime_r(&t, &currentTime);
    _minute = currentTime.tm_min;
    _hour = currentTime.tm_hour;
    _day = currentTime.tm_mday;
    _month = currentTime.tm_mon;
    _year = currentTime.tm_year+1900;
}

std::ostream& Date::operator<<(std::ostream& out) const{
    out << _hour << ":" << _minute << " " << _day << "/" << _month << "/" << _year << std::endl;
    return out;
}
