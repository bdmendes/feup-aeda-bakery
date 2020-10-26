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

bool Date::isLeapYear() const {
    return ((_year%4==0 && _year%100!=0) || (_year%400==0));
}

Date::Date(unsigned hour, unsigned minute, unsigned day, unsigned month, unsigned year) :
    _hour(hour), _minute(minute), _day(day), _month(month), _year(year){

    if(_hour>=24) throw InvalidDate(std::to_string(_hour)+" is an invalid hour.");
    if(_minute>=60) throw InvalidDate(std::to_string(_minute)+" is an invalid minute.");

    if(_day>31) throw InvalidDate(std::to_string(_day)+" is not a valid day.");
    switch(_month){
        case 4: case 6: case 9: case 11:
            if(_day>30) throw InvalidDate(std::to_string(_day)+" is an invalid day for "+std::to_string(_month)+".");
            break;
        case 2:
            if((isLeapYear()&&_day>29) || (!isLeapYear()&&_day>28))
                throw InvalidDate(std::to_string(_day)+" is an invalid day for "+std::to_string(_month)+".");
            break;
    }
}


