//
// Created by laimi on 25/10/2020.
//

#include <gtest/gtest.h>
#include "model/date/date.h"

using testing::Eq;

TEST(Date, create_date){
    EXPECT_THROW(Date d1(29,02,2019,23,53),InvalidDate);
    EXPECT_THROW(Date d2(29,05,2020,23,60), InvalidDate);
}

TEST(Date, is_leap_year){
    EXPECT_EQ(true, Date::isLeapYear(2008));
    EXPECT_EQ(true, Date::isLeapYear(2020));

    EXPECT_EQ(false, Date::isLeapYear(2003));
    EXPECT_EQ(false, Date::isLeapYear(2017));
}

TEST(Date, get_Calendar_Day){
    Date d1(12, 3,1998);
    Date d2 (28, 12, 2006);

    EXPECT_EQ("12/03/1998", d1.getCalendarDay());
    EXPECT_EQ("28/12/2006", d2.getCalendarDay());
}

TEST(Date, get_Clock_Time){
    Date d1(29,9,2001, 13, 57);
    Date d2 (24, 4, 2001, 2, 34);

    EXPECT_EQ("13:57", d1.getClockTime());
    EXPECT_EQ("02:34", d2.getClockTime());
}

TEST(Date, get_complete_date){
    Date d1(21, 10, 1976, 18, 21);
    Date d2(21, 6, 1972, 9, 39);

    EXPECT_EQ("21/10/1976 18:21", d1.getCompleteDate());
    EXPECT_EQ("21/06/1972 09:39", d2.getCompleteDate());
}

TEST(Date, add_days){
    Date d1(28, 12, 2012, 13, 24);
    Date d2(28, 2, 2001, 9, 47);

    EXPECT_EQ(28, d1.getDay());
    d1.addDays(4);
    EXPECT_EQ("01/01/2013 13:24", d1.getCompleteDate());

    EXPECT_EQ(28, d2.getDay());
    d2.addDays(7);
    EXPECT_EQ("07/03/2001 09:47", d2.getCompleteDate());
}

TEST(Date, add_minutes){
    Date d1(17, 3, 1986, 14, 54);
    Date d2(24, 7, 1989,  23, 43);

    EXPECT_EQ(54, d1.getMinute());
    d1.addMinutes(26);
    EXPECT_EQ("17/03/1986 15:20", d1.getCompleteDate());

    EXPECT_EQ(43, d2.getMinute());
    d2.addMinutes(77);
    EXPECT_EQ("25/07/1989 01:00", d2.getCompleteDate());
}

TEST(Date, equal_dates){
    Date d1(9, 6, 2001, 10, 51);
    Date d2(9, 6, 2001, 10, 51);
    Date d3(9, 10, 2001, 10, 51);

    EXPECT_TRUE(d1==d2);
    EXPECT_TRUE(d2==d1);

    EXPECT_FALSE(d1==d3);
    EXPECT_FALSE(d2==d3);
}

TEST(Date, earlier_date){
    Date d1(14, 5, 1874, 11, 23);
    Date d2(14, 5, 1874, 11, 24);
    Date d3(14, 5, 1873, 23, 45);
    Date d4(14, 5, 1873, 0, 0);

    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d3 < d1);
    EXPECT_TRUE(d4 < d3);
    EXPECT_FALSE(d2 < d3);
}