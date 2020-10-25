//
// Created by bdmendes on 21/10/20.
//

#include "date.h"
#include "../exception/dateExceptions.h"
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
    bool valid=testDate();
}

std::ostream& Date::operator<<(std::ostream& out) const{
    out << _hour << ":" << _minute << " " << _day << "/" << _month << "/" << _year << std::endl;
    return out;
}

bool Date::isLeapYear(unsigned year) {
    return ((year%4==0 && year%100!=0) || (year%400==0));
}

void Date::testMonth() {
    if(_month<1 || _month>12) throw InvalidDate(std::to_string(_month)+" is not a valid month.");
}

void Date::testDay() {
    if(_day>31) throw InvalidDate(std::to_string(_day)+" is not a valid day.");
    switch(_month){
        case 4:
        case 6:
        case 9:
        case 11:
            if(_day>30) throw InvalidDate(std::to_string(_day)+" is an invalid day for "+std::to_string(_month)+".");
            break;
        case 2:
            if((isLeapYear(_year)&&_day>29 || (!isLeapYear(_year))&&_day>28))
                throw InvalidDate(std::to_string(_day)+" is an invalid day for "+std::to_string(_month)+".");
    }
}

void Date::testHour() {
    if(_hour>23) throw InvalidDate(std::to_string(_hour)+" is an invalid hour.");
}

void Date::testMinute() {
    if(_minute>59) throw InvalidDate(std::to_string(_minute)+" is an invalid minute.");
}

bool Date::testDate() {
    try{
        testMonth();
        testDay();
        testHour();
        testMinute();
        return true;
    }
    catch (InvalidDate &ex){
        ex<<std::cout;
        return false;
    }
}


