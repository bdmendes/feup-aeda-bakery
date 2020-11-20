
#ifndef FEUP_AEDA_PROJECT_DATE_H
#define FEUP_AEDA_PROJECT_DATE_H

#include <string>
#include <ctime>

#include "exception/date_exception.h"

/**
 * Class that provides the date to order request and its delivery.
 */
class Date{
public:
    /**
     * Creates a new Date object which is the current calendar time.
     */
    Date();

    /**
     * Creates a new customized Date object.
     *
     * @param day the day
     * @param month the month
     * @param year the year
     * @param hour the hour
     * @param minute the minute
     */
    Date(int day, int month, int year, int hour = 0, int minute = 0);

    /**
     * Checks if a year is leap.
     *
     * @param year the year
     * @return true, if it is a leap year; false, otherwise
     */
    static bool isLeapYear(unsigned year);

    /**
     * Gets the day.
     *
     * @return the day
     */
    unsigned getDay() const;

    /**
     * Gets the month.
     *
     * @return the month
     */
    unsigned getMonth() const;

    /**
     * Gets the year.
     *
     * @return the year
     */
    unsigned getYear() const;

    /**
     * Gets the hour.
     *
     * @return the hour
     */
    unsigned getHour() const;

    /**
     * Gets the minute
     *
     * @return the minute
     */
    unsigned getMinute() const;

    /**
     * Gets the calender day in DD/MM/YYYY format.
     *
     * @return the calender day
     */
    std::string getCalendarDay() const;

    /**
     * Gets the clock time in HH:MM format.
     *
     * @return the clock time
     */
    std::string getClockTime() const;

    /**
     * Gets the complete date in DD/MM/YYYY HH:MM format.
     *
     * @return the complete date
     */
    std::string getCompleteDate() const;

    /**
     * Adds days to the date.
     *
     * @param days the days to add
     */
    void addDays(int days);

    /**
     * Adds minutes to the date.
     *
     * @param minutes the minutes to add
     */
    void addMinutes(int minutes);

    /**
     * One date is equal to other when their complete dates are equal.
     *
     * @param d2 the date to compare with
     * @return true, if the dates are equal; false, otherwise
     */
    bool operator==(const Date& d2) const;

    /**
     * One date is less than the other if it corresponds to an earlier date.
     *
     * @param d2 the date to compare with
     * @return true, if the date is less than d2; false, otherwise
     */
    bool operator<(const Date& d2) const;
private:
    /**
     * Checks if the date is valid.
     *
     * @return true, if it is a valid date; false, otherwise
     */
    bool isValid() const;

    /**
     * Struct to get the current calendar date and time.
     */
    tm _time;
};

#endif //FEUP_AEDA_PROJECT_DATE_H
